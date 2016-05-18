/*
 * Thread.h
 *
 *  Created on: 2015年12月2日
 *      Author: lijing
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>

namespace pola {
namespace utils {

class Thread {
public:
	Thread();
	Thread(int priority, bool joinable);
	virtual ~Thread();
	virtual void start();

	virtual void run();

	bool isActive();

	pthread_t getThreadId() const {
		return mId;
	}
private:
	bool mActive;
	pthread_t mId;

	int mPriority;
	bool mJoinable;

protected:
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t  cond = PTHREAD_COND_INITIALIZER;
};

static void *threadRun(void* arg) {
	Thread* _this = static_cast<Thread*>(arg);
	if (_this) {
		_this->run();
	}
	return (void*) 0;
}

inline Thread::Thread()
	: mActive(false)
	, mId(-1)
	, mPriority(0)
	, mJoinable(false) {
}

inline Thread::Thread(int priority, bool joinable)
	: mActive(false)
	, mId(-1)
	, mPriority(priority)
	, mJoinable(joinable) {
}

inline Thread::~Thread() {
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
}

void Thread::start() {
	pthread_mutex_lock(&mutex);
	pthread_attr_t attr;
	pthread_attr_init (&attr);
	if (!mJoinable) {
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	}
	pthread_create (&mId, &attr, threadRun, this);
	pthread_attr_destroy (&attr);
	mActive = true;
	pthread_mutex_unlock(&mutex);
}

inline void Thread::run() {
	// XX do job

	pthread_mutex_lock(&mutex);
	mActive = false;
	mId = -1;
	pthread_mutex_unlock(&mutex);
}

inline bool Thread::isActive() {
	return mActive;
}
}
}

#endif /* THREAD_H_ */
