/*
 * MessageQueue.h
 *
 *  Created on: 2015年12月1日
 *      Author: lijing
 */

#ifndef POLA_MESSAGEQUEUE_H_
#define POLA_MESSAGEQUEUE_H_

#include "pola/utils/thread/Message.h"
#include "pola/utils/Times.h"
#include "pola/utils/Mutex.h"

#include <sys/epoll.h>
#include <pthread.h>
#include <vector>
#include <map>

namespace pola {
namespace utils {

/**
 * Flags for file descriptor events that a looper can monitor.
 *
 * These flag bits can be combined to monitor multiple events at once.
 */
enum {
    /**
     * The file descriptor is available for read operations.
     */
    LOOPER_EVENT_INPUT = 1 << 0,

    /**
     * The file descriptor is available for write operations.
     */
    LOOPER_EVENT_OUTPUT = 1 << 1,

    /**
     * The file descriptor has encountered an error condition.
     *
     * The looper always sends notifications about errors; it is not necessary
     * to specify this event flag in the requested event set.
     */
    LOOPER_EVENT_ERROR = 1 << 2,

    /**
     * The file descriptor was hung up.
     * For example, indicates that the remote end of a pipe or socket was closed.
     *
     * The looper always sends notifications about hangups; it is not necessary
     * to specify this event flag in the requested event set.
     */
    LOOPER_EVENT_HANGUP = 1 << 3,

    /**
     * The file descriptor is invalid.
     * For example, the file descriptor was closed prematurely.
     *
     * The looper always sends notifications about invalid file descriptors; it is not necessary
     * to specify this event flag in the requested event set.
     */
    LOOPER_EVENT_INVALID = 1 << 4,
};

enum {
    /**
     * Result from ALooper_pollOnce() and ALooper_pollAll():
     * The poll was awoken using wake() before the timeout expired
     * and no callbacks were executed and no other file descriptors were ready.
     */
    LOOPER_POLL_WAKE = -1,

    /**
     * Result from ALooper_pollOnce() and ALooper_pollAll():
     * One or more callbacks were executed.
     */
    LOOPER_POLL_CALLBACK = -2,

    /**
     * Result from ALooper_pollOnce() and ALooper_pollAll():
     * The timeout expired.
     */
    LOOPER_POLL_TIMEOUT = -3,

    /**
     * Result from ALooper_pollOnce() and ALooper_pollAll():
     * An error occurred.
     */
    LOOPER_POLL_ERROR = -4,
};

/**
 * For callback-based event loops, this is the prototype of the function
 * that is called when a file descriptor event occurs.
 * It is given the file descriptor it is associated with,
 * a bitmask of the poll events that were triggered (typically ALOOPER_EVENT_INPUT),
 * and the data pointer that was originally supplied.
 *
 * Implementations should return 1 to continue receiving callbacks, or 0
 * to have this file descriptor and callback unregistered from the looper.
 */
typedef int (*Looper_callbackFunc)(int fd, int events, void* data);

/**
 * A looper callback.
 */
class LooperCallback : public RefBase {
public:
    virtual ~LooperCallback() { }

public:
    /**
     * Handles a poll event for the given file descriptor.
     * It is given the file descriptor it is associated with,
     * a bitmask of the poll events that were triggered (typically ALOOPER_EVENT_INPUT),
     * and the data pointer that was originally supplied.
     *
     * Implementations should return 1 to continue receiving callbacks, or 0
     * to have this file descriptor and callback unregistered from the looper.
     */
    virtual int handleEvent(int fd, int events, void* data) = 0;
};

/**
 * Wraps a ALooper_callbackFunc function pointer.
 */
class SimpleLooperCallback : public LooperCallback {
protected:
    virtual ~SimpleLooperCallback();

public:
    SimpleLooperCallback(Looper_callbackFunc callback);
    virtual int handleEvent(int fd, int events, void* data);

private:
    Looper_callbackFunc mCallback;
};

class MessageQueue {

public:
	MessageQueue(bool quitAllowed);
	~MessageQueue();

	/**
	 * Adds a new file descriptor to be polled by the looper.
	 * If the same file descriptor was previously added, it is replaced.
	 *
	 * "fd" is the file descriptor to be added.
	 * "ident" is an identifier for this event, which is returned from pollOnce().
	 * The identifier must be >= 0, or ALOOPER_POLL_CALLBACK if providing a non-NULL callback.
	 * "events" are the poll events to wake up on.  Typically this is ALOOPER_EVENT_INPUT.
	 * "callback" is the function to call when there is an event on the file descriptor.
	 * "data" is a private data pointer to supply to the callback.
	 *
	 * There are two main uses of this function:
	 *
	 * (1) If "callback" is non-NULL, then this function will be called when there is
	 * data on the file descriptor.  It should execute any events it has pending,
	 * appropriately reading from the file descriptor.  The 'ident' is ignored in this case.
	 *
	 * (2) If "callback" is NULL, the 'ident' will be returned by ALooper_pollOnce
	 * when its file descriptor has data available, requiring the caller to take
	 * care of processing it.
	 *
	 * Returns 1 if the file descriptor was added, 0 if the arguments were invalid.
	 *
	 * This method can be called on any thread.
	 * This method may block briefly if it needs to wake the poll.
	 *
	 * The callback may either be specified as a bare function pointer or as a smart
	 * pointer callback object.  The smart pointer should be preferred because it is
	 * easier to avoid races when the callback is removed from a different thread.
	 * See removeFd() for details.
	 */
	int addFd(int fd, int ident, int events, Looper_callbackFunc callback, void* data);
	int addFd(int fd, int ident, int events, const sp<LooperCallback>& callback, void* data);

	/**
	 * Removes a previously added file descriptor from the looper.
	 *
	 * When this method returns, it is safe to close the file descriptor since the looper
	 * will no longer have a reference to it.  However, it is possible for the callback to
	 * already be running or for it to run one last time if the file descriptor was already
	 * signalled.  Calling code is responsible for ensuring that this case is safely handled.
	 * For example, if the callback takes care of removing itself during its own execution either
	 * by returning 0 or by calling this method, then it can be guaranteed to not be invoked
	 * again at any later time unless registered anew.
	 *
	 * A simple way to avoid this problem is to use the version of addFd() that takes
	 * a sp<LooperCallback> instead of a bare function pointer.  The LooperCallback will
	 * be released at the appropriate time by the Looper.
	 *
	 * Returns 1 if the file descriptor was removed, 0 if none was previously registered.
	 *
	 * This method can be called on any thread.
	 * This method may block briefly if it needs to wake the poll.
	 */
	int removeFd(int fd);

	Message* next();

	void quit(bool safe);

	void removeMessages(sp<AbsMessageHandler> h, int what);
	void removeMessages(sp<AbsMessageHandler> h, Task* task);
	void removeMessages(sp<AbsMessageHandler> h);
	bool enqueueMessage(Message* msg, p_nsecs_t when);

	bool isIdling() const;

private:
	struct Request {
		int fd;
		int ident;
		sp<LooperCallback> callback;
		void* data;
	};

	struct Response {
		int events;
		Request request;
	};

private:
	int mWakeReadPipeFd;  // immutable
	int mWakeWritePipeFd; // immutable
	Mutex mLock;

	int mEpollFd; // immutable

	// Locked list of file descriptor monitoring requests.
	std::map<int, Request> mRequests;  // guarded by mLock
	std::vector<Response> mResponses;
	unsigned mResponseIndex;

	int pollOnce(p_nsecs_t timeoutMillis);
	void wake();

	void awoken();
	void pushResponse(int events, const Request& request);

	Message* mMessages;
	bool mQuitAllowed;
	bool mBlocked;
	bool mQuitting;

	bool mIdling;
	Mutex mMessageLock;
};
}
}

#endif /* POLA_MESSAGEQUEUE_H_  */
