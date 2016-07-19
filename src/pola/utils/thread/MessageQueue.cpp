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

// Hint for number of file descriptors to be associated with the epoll instance.
static const int EPOLL_SIZE_HINT = 8;

// Maximum number of file descriptors for which to retrieve poll events each iteration.
static const int EPOLL_MAX_EVENTS = 5;

MessageQueue::MessageQueue() : mMessages(nullptr),
		mBlocked(true),
		mQuitting(false) {
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
	pthread_mutex_destroy(&mutex);
}

void MessageQueue::pollOnce(p_nsecs_t timeoutMillis) {
	if (timeoutMillis < 0) {
		timeoutMillis = LLONG_MAX;
	}
	static struct epoll_event eventItems[EPOLL_MAX_EVENTS];
	// Not support other event yet.
	epoll_wait(mEpollFd, eventItems, EPOLL_MAX_EVENTS, timeoutMillis);
}

void MessageQueue::wake() {
	ssize_t nWrite;
	do {
		nWrite = write(mWakeWritePipeFd, "W", 1);
	} while (nWrite == -1 && errno == EINTR);
}

void MessageQueue::removeMessages(Handler* h, int what) {
	if (h == nullptr) {
		return;
	}

	pthread_mutex_lock(&mutex);
	Message* p = mMessages;

	// Remove all messages at front.
	while (p != nullptr && p->target == h && p->what == what) {
		Message* n = p->next;
		mMessages = n;
		delete p;
		p = n;
	}

	// Remove all messages after front.
	while (p != nullptr) {
		Message* n = p->next;
		if (n != nullptr) {
			if (n->target == h && n->what == what) {
				Message* nn = n->next;
				delete n;
				p->next = nn;
				continue;
			}
		}
		p = n;
	}
	pthread_mutex_unlock(&mutex);
}

void MessageQueue::removeMessages(Handler* h, Task* task) {
	if (h == nullptr) {
		return;
	}

	pthread_mutex_lock(&mutex);
	Message* p = mMessages;

	// Remove all messages at front.
	while (p != nullptr && p->target == h && p->task == task) {
		Message* n = p->next;
		mMessages = n;
		delete p;
		p = n;
	}

	// Remove all messages after front.
	while (p != nullptr) {
		Message* n = p->next;
		if (n != nullptr) {
			if (n->target == h && p->task == task) {
				Message* nn = n->next;
				delete n;
				p->next = nn;
				continue;
			}
		}
		p = n;
	}
	pthread_mutex_unlock(&mutex);
}

void MessageQueue::removeMessages(Handler* h) {
	if (h == nullptr) {
		return;
	}

	pthread_mutex_lock(&mutex);
	Message* p = mMessages;

	// Remove all messages at front.
	while (p != nullptr && p->target == h) {
		Message* n = p->next;
		mMessages = n;
		delete p;
		p = n;
	}

	// Remove all messages after front.
	while (p != nullptr) {
		Message* n = p->next;
		if (n != nullptr) {
			if (n->target == h) {
				Message* nn = n->next;
				delete n;
				p->next = nn;
				continue;
			}
		}
		p = n;
	}
	pthread_mutex_unlock(&mutex);
}

bool MessageQueue::enqueueMessage(Message* msg, p_nsecs_t when) {
	if (!msg->target) {
		throw "Message must have a target.";
	}
	pthread_mutex_lock(&mutex);
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
	pthread_mutex_unlock(&mutex);
	return true;
}

Message* MessageQueue::next() {
	p_nsecs_t nextPollTimeoutMillis = 0;
	for (;;) {
		pollOnce(nextPollTimeoutMillis);

		Message* msg = nullptr;
		pthread_mutex_lock(&mutex);
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
					pthread_mutex_unlock(&mutex);
					return msg;
				}
			} else {
				nextPollTimeoutMillis = -1;
			}

			if (mQuitting) {
				pthread_mutex_unlock(&mutex);
				return nullptr;
			}
		}
		pthread_mutex_unlock(&mutex);
		mBlocked = true;
	}

	return nullptr;
}

void MessageQueue::quit(bool safe) {
	pthread_mutex_lock(&mutex);
	if (mQuitting) {
		pthread_mutex_unlock(&mutex);
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
			delete p;
			p = n;
		}
		mMessages = nullptr;
	}

Done:
	wake();
	pthread_mutex_unlock(&mutex);
}

}

}

