/*
 * MessageQueue.cpp
 *
 *  Created on: 2015年12月1日
 *      Author: lijing
 */

#include "pola/utils/thread/MessageQueue.h"

#include "pola/log/Log.h"

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

namespace pola {
namespace utils {

// --- SimpleLooperCallback ---
SimpleLooperCallback::SimpleLooperCallback(Looper_callbackFunc callback) :
        mCallback(callback) {
}

SimpleLooperCallback::~SimpleLooperCallback() {
}

int SimpleLooperCallback::handleEvent(int fd, int events, void* data) {
    return mCallback(fd, events, data);
}

// Hint for number of file descriptors to be associated with the epoll instance.
static const int EPOLL_SIZE_HINT = 8;

// Maximum number of file descriptors for which to retrieve poll events each iteration.
static const int EPOLL_MAX_EVENTS = 5;

MessageQueue::MessageQueue(bool quitAllowed) : mResponseIndex(0), mMessages(NULL),
		mQuitAllowed(quitAllowed),
		mBlocked(true),
		mQuitting(false),
		mIdling(false) {
	int wakeFds[2];
	int result = pipe(wakeFds);
	LOG_FATAL_IF((result != 0), "Could not create wake pipe.  errno=%d\n", errno);

	mWakeReadPipeFd = wakeFds[0];
	mWakeWritePipeFd = wakeFds[1];
	result = fcntl(mWakeReadPipeFd, F_SETFL, O_NONBLOCK);
	LOG_FATAL_IF((result != 0), "Could not make wake read pipe non-blocking.  errno=%d",
			errno);

	result = fcntl(mWakeWritePipeFd, F_SETFL, O_NONBLOCK);
	LOG_FATAL_IF((result != 0), "Could not make wake write pipe non-blocking.  errno=%d",
			errno);

	// Allocate the epoll instance and register the wake pipe.
	mEpollFd = epoll_create(EPOLL_SIZE_HINT);
	LOG_FATAL_IF((mEpollFd < 0), "Could not create epoll instance.  errno=%d\n", errno);

	struct epoll_event eventItem;
	memset(& eventItem, 0, sizeof(epoll_event)); // zero out unused members of data field union
	eventItem.events = EPOLLIN;
	eventItem.data.fd = mWakeReadPipeFd;
	result = epoll_ctl(mEpollFd, EPOLL_CTL_ADD, mWakeReadPipeFd, & eventItem);
	LOG_FATAL_IF((result != 0), "Could not add wake read pipe to epoll instance.  errno=%d\n",
			errno);
}

MessageQueue::~MessageQueue() {
	quit(false);
}

int MessageQueue::addFd(int fd, int ident, int events, Looper_callbackFunc callback, void* data) {
    return addFd(fd, ident, events, callback ? new SimpleLooperCallback(callback) : NULL, data);
}

int MessageQueue::addFd(int fd, int ident, int events, const sp<LooperCallback>& callback, void* data) {
#if DEBUG_CALLBACKS
	LOGI("%p ~ addFd - fd=%d, ident=%d, events=0x%x, callback=%p, data=%p", this, fd, ident,
            events, callback.get(), data);
#endif

    if (callback == NULL) {
        /*if (!mAllowNonCallbacks) {
            ALOGE("Invalid attempt to set NULL callback but not allowed for this looper.");
            return -1;
        }*/

        if (ident < 0) {
            LOGE("Invalid attempt to set NULL callback with ident < 0.");
            return -1;
        }
    } else {
        ident = LOOPER_POLL_CALLBACK;
    }

    int epollEvents = 0;
    if (events & LOOPER_EVENT_INPUT) epollEvents |= EPOLLIN;
    if (events & LOOPER_EVENT_OUTPUT) epollEvents |= EPOLLOUT;

    { // acquire lock
        AutoMutex _l(mLock);

        Request request;
        request.fd = fd;
        request.ident = ident;
        request.callback = callback;
        request.data = data;

        struct epoll_event eventItem;
        memset(& eventItem, 0, sizeof(epoll_event)); // zero out unused members of data field union
        eventItem.events = epollEvents;
        eventItem.data.fd = fd;

        std::map<int, Request>::iterator result = mRequests.find(fd);
        if (result == mRequests.end()) {
            int epollResult = epoll_ctl(mEpollFd, EPOLL_CTL_ADD, fd, & eventItem);
            if (epollResult < 0) {
                LOGE("Error adding epoll events for fd %d, errno=%d", fd, errno);
                return -1;
            }
            mRequests[fd] = request;
        } else {
            int epollResult = epoll_ctl(mEpollFd, EPOLL_CTL_MOD, fd, & eventItem);
            if (epollResult < 0) {
                LOGE("Error modifying epoll events for fd %d, errno=%d", fd, errno);
                return -1;
            }
            mRequests[fd] = request;
        }
    } // release lock
    return 1;
}

int MessageQueue::removeFd(int fd) {
#if DEBUG_CALLBACKS
	LOGI("%p ~ removeFd - fd=%d", this, fd);
#endif

    { // acquire lock
        AutoMutex _l(mLock);
        std::map<int, Request>::iterator result = mRequests.find(fd);
		if (result == mRequests.end()) {
            return 0;
        }

        int epollResult = epoll_ctl(mEpollFd, EPOLL_CTL_DEL, fd, NULL);
        if (epollResult < 0) {
            LOGE("Error removing epoll events for fd %d, errno=%d", fd, errno);
            return -1;
        }

        mRequests.erase(result);
    } // release lock
    return 1;
}

int MessageQueue::pollOnce(p_nsecs_t timeoutMillis) {
	if (timeoutMillis < 0) {
		timeoutMillis = LLONG_MAX;
	}

	// Poll.
	int result = LOOPER_POLL_WAKE;
	mResponses.clear();
	mResponseIndex = 0;

	// We are about to idle.
	mIdling = true;

	static struct epoll_event eventItems[EPOLL_MAX_EVENTS];
	// Not support other event yet.
	int eventCount = epoll_wait(mEpollFd, eventItems, EPOLL_MAX_EVENTS, timeoutMillis);

	mIdling = false;

	// Acquire lock.
	mLock.lock();

	// Check for poll error.
	if (eventCount < 0) {
		if (errno == EINTR) {
			goto Done;
		}
		LOGW("Poll failed with an unexpected error, errno=%d", errno);
		result = LOOPER_POLL_ERROR;
		goto Done;
	}

	// Check for poll timeout.
	if (eventCount == 0) {
#if DEBUG_POLL_AND_WAKE
		LOGI("%p ~ pollOnce - timeout", this);
#endif
		result = LOOPER_POLL_TIMEOUT;
		goto Done;
	}

    // Handle all events.
#if DEBUG_POLL_AND_WAKE
	LOGI("%p ~ pollOnce - handling events from %d fds", this, eventCount);
#endif

    for (int i = 0; i < eventCount; i++) {
        int fd = eventItems[i].data.fd;
        uint32_t epollEvents = eventItems[i].events;
        if (fd == mWakeReadPipeFd) {
            if (epollEvents & EPOLLIN) {
                awoken();
            } else {
                LOGW("Ignoring unexpected epoll events 0x%x on wake read pipe.", epollEvents);
            }
        } else {
        	std::map<int, Request>::iterator requestIter = mRequests.find(fd);
            if (requestIter != mRequests.end()) {
                int events = 0;
                if (epollEvents & EPOLLIN) events |= LOOPER_EVENT_INPUT;
                if (epollEvents & EPOLLOUT) events |= LOOPER_EVENT_OUTPUT;
                if (epollEvents & EPOLLERR) events |= LOOPER_EVENT_ERROR;
                if (epollEvents & EPOLLHUP) events |= LOOPER_EVENT_HANGUP;
                pushResponse(events, requestIter->second);
            } else {
                LOGW("Ignoring unexpected epoll events 0x%x on fd %d that is "
                        "no longer registered.", epollEvents, fd);
            }
        }
    }

Done: ;

	// Release lock.
    mLock.unlock();

	// Invoke all response callbacks.
	for (size_t i = 0; i < mResponses.size(); i++) {
		Response& response = mResponses[i];
		if (response.request.ident == LOOPER_POLL_CALLBACK) {
			int fd = response.request.fd;
			int events = response.events;
			void* data = response.request.data;
#if DEBUG_POLL_AND_WAKE || DEBUG_CALLBACKS
			LOGI("%p ~ pollOnce - invoking fd event callback %p: fd=%d, events=0x%x, data=%p",
					this, response.request.callback.get(), fd, events, data);
#endif
			int callbackResult = response.request.callback->handleEvent(fd, events, data);
			if (callbackResult == 0) {
				removeFd(fd);
			}
			// Clear the callback reference in the response structure promptly because we
			// will not clear the response vector itself until the next poll.
			response.request.callback.clear();
			result = LOOPER_POLL_CALLBACK;
		}
	}

	return result;
}

void MessageQueue::awoken() {
#if DEBUG_POLL_AND_WAKE
	LOGI("%p ~ awoken", this);
#endif

    char buffer[16];
    ssize_t nRead;
    do {
        nRead = read(mWakeReadPipeFd, buffer, sizeof(buffer));
    } while ((nRead == -1 && errno == EINTR) || nRead == sizeof(buffer));
}

void MessageQueue::pushResponse(int events, const Request& request) {
    Response response;
    response.events = events;
    response.request = request;
    mResponses.push_back(response);
}

bool MessageQueue::isIdling() const {
	return mIdling;
}

void MessageQueue::wake() {
	ssize_t nWrite;
	do {
		nWrite = write(mWakeWritePipeFd, "W", 1);
	} while (nWrite == -1 && errno == EINTR);
}

void MessageQueue::removeMessages(sp<AbsMessageHandler> h, int what) {
	if (h == nullptr) {
		return;
	}

	AutoMutex _l(mMessageLock);
	Message* p = mMessages;

	// Remove all messages at front.
	while (p != nullptr && p->target == h && p->what == what) {
		Message* n = p->next;
		mMessages = n;
		if (p->target != nullptr) {
			p->target->handleRecycleMessage(p);
		}
		delete p;
		p = n;
	}

	// Remove all messages after front.
	while (p != nullptr) {
		Message* n = p->next;
		if (n != nullptr) {
			if (n->target == h && n->what == what) {
				Message* nn = n->next;
				if (n->target != nullptr) {
					n->target->handleRecycleMessage(n);
				}
				delete n;
				p->next = nn;
				continue;
			}
		}
		p = n;
	}
}

void MessageQueue::removeMessages(sp<AbsMessageHandler> h, Task* task) {
	if (h == nullptr) {
		return;
	}

	AutoMutex _l(mMessageLock);
	Message* p = mMessages;

	// Remove all messages at front.
	while (p != nullptr && p->target == h && p->task == task) {
		Message* n = p->next;
		mMessages = n;
		if (p->target != nullptr) {
			p->target->handleRecycleMessage(p);
		}
		delete p;
		p = n;
	}

	// Remove all messages after front.
	while (p != nullptr) {
		Message* n = p->next;
		if (n != nullptr) {
			if (n->target == h && p->task == task) {
				Message* nn = n->next;
				if (n->target != nullptr) {
					n->target->handleRecycleMessage(n);
				}
				delete n;
				p->next = nn;
				continue;
			}
		}
		p = n;
	}
}

void MessageQueue::removeMessages(sp<AbsMessageHandler> h) {
	if (h == nullptr) {
		return;
	}

	AutoMutex _l(mMessageLock);
	Message* p = mMessages;

	// Remove all messages at front.
	while (p != nullptr && p->target == h) {
		Message* n = p->next;
		mMessages = n;
		if (p->target != nullptr) {
			p->target->handleRecycleMessage(p);
		}
		delete p;
		p = n;
	}

	// Remove all messages after front.
	while (p != nullptr) {
		Message* n = p->next;
		if (n != nullptr) {
			if (n->target == h) {
				Message* nn = n->next;
				if (n->target != nullptr) {
					n->target->handleRecycleMessage(n);
				}
				delete n;
				p->next = nn;
				continue;
			}
		}
		p = n;
	}
}

bool MessageQueue::enqueueMessage(Message* msg, p_nsecs_t when) {
	LOG_FATAL_IF(msg->target == NULL, "Message must have a target.");
	AutoMutex _l(mMessageLock);
	{
		if (mQuitting) {
			LOGE("sending message to a Handler on a dead thread\n");
			return false;
		}
		msg->when = when;
		Message* p = mMessages;
		bool needWake;
		if (!p || when == 0 || when < p->when) {
			// New head, wake up the event queue if blocked.
			msg->next = p;
			mMessages = msg;
			needWake = mBlocked;
		} else {
            // Inserted within the middle of the queue.  Usually we don't have to wake
            // up the event queue unless there is a barrier at the head of the queue
            // and the message is the earliest asynchronous message in the queue.
            needWake = false;
            Message* prev;
            for (;;) {
                prev = p;
                p = p->next;
                if (!p || when < p->when) {
                    break;
                }
            }
            msg->next = p; // invariant: p == prev.next
            prev->next = msg;
        }
		if (needWake) {
			wake();
		}
	}
	return true;
}

Message* MessageQueue::next() {
	p_nsecs_t nextPollTimeoutMillis = 0;
	for (;;) {
		pollOnce(nextPollTimeoutMillis);

		Message* msg = nullptr;
		AutoMutex _l(mMessageLock);
		{
			// Try to retrieve the next message.  Return if found.
			const p_nsecs_t now = uptimeMillis();
			msg = mMessages;
			if (msg) {
				if (now < msg->when) {
					// Next message is not ready.  Set a timeout to wake up when it is ready.
					nextPollTimeoutMillis = msg->when - now;
					msg = nullptr;
				} else {
					// Got a message.
					mBlocked = false;
					mMessages = msg->next;
					msg->next = nullptr;
					return msg;
				}
			} else {
				nextPollTimeoutMillis = -1;
			}

			if (mQuitting) {
				return nullptr;
			}
		}
		mBlocked = true;
	}

	return nullptr;
}

void MessageQueue::quit(bool safe) {
	LOG_FATAL_IF(!mQuitAllowed, "Main thread not allowed to quit.");
	AutoMutex _l(mMessageLock);
	if (mQuitting) {
		return;
	}
	mQuitting = true;

	if (safe) {
		goto RemoveAllFutureMessagesLocked;
	} else {
		goto RemoveAllMessagesLocked;
	}

RemoveAllFutureMessagesLocked:
	{
		const long now = uptimeMillis();
		Message* p = mMessages;
		if (p) {
			if (p->when > now) {
				goto RemoveAllMessagesLocked;
			} else {
				Message* n;
				for (;;) {
					n = p->next;
					if (n) {
						return;
					}
					if (n->when > now) {
						break;
					}
					p = n;
				}
				p->next = nullptr;
				do {
					p = n;
					n = p->next;
					if (p->target != nullptr) {
						p->target->handleRecycleMessage(p);
					}
					delete p;
				} while (n);
			}
		}
	}
	goto Done;

RemoveAllMessagesLocked:
	{
		Message* p = mMessages;
		while (p) {
			Message* n = p->next;
			if (p->target != nullptr) {
				p->target->handleRecycleMessage(p);
			}
			delete p;
			p = n;
		}
		mMessages = nullptr;
	}

Done:
	wake();
}

}

}

