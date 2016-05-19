/*
 * MessageQueue.h
 *
 *  Created on: 2015年12月1日
 *      Author: lijing
 */

#ifndef POLA_MESSAGEQUEUE_H_
#define POLA_MESSAGEQUEUE_H_

#include "utils/thread/Message.h"
#include "utils/Times.h"

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
	bool enqueueMessage(Message* msg, nsecs_t when);

private:
	int mWakeReadPipeFd;  // immutable
	int mWakeWritePipeFd; // immutable
	int mEpollFd; // immutable

	void pollOnce(nsecs_t timeoutMillis);
	void wake();

	Message* mMessages;
	bool mBlocked;
	bool mQuitting;

	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
};
}
}

#endif /* POLA_MESSAGEQUEUE_H_  */
