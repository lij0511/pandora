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

#include <sys/epoll.h>
#include <pthread.h>

namespace pola {
namespace utils {

class MessageQueue {

public:
	MessageQueue();
	~MessageQueue();

	Message* next();

	void quit(bool safe);

	void removeMessages(Handler* h, int what);
	void removeMessages(Handler* h, Task* task);
	void removeMessages(Handler* h);
	bool enqueueMessage(Message* msg, p_nsecs_t when);

private:
	int mWakeReadPipeFd;  // immutable
	int mWakeWritePipeFd; // immutable
	int mEpollFd; // immutable

	void pollOnce(p_nsecs_t timeoutMillis);
	void wake();

	Message* mMessages;
	bool mBlocked;
	bool mQuitting;

	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
};
}
}

#endif /* POLA_MESSAGEQUEUE_H_  */
