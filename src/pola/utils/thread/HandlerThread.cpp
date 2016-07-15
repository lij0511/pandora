/*
 * HandlerThread.cpp
 *
 *  Created on: 2015年12月2日
 *      Author: lijing
 */

#include "pola/utils/thread/HandlerThread.h"

namespace pola {
namespace utils {

HandlerThread::HandlerThread()
	: Thread() {
}

HandlerThread::HandlerThread(int priority, bool joinable)
	: Thread(priority, joinable) {
}

HandlerThread::~HandlerThread() {
}

void HandlerThread::run() {
	Looper::prepare();
	mLooper = Looper::myLooper();
	pthread_mutex_lock(&mutex);
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mutex);
	mLooper->loop();
	Thread::run();
}

void HandlerThread::start() {
	Thread::start();
	getLooper();
}

void HandlerThread::stop() {
	if (mLooper.get()) {
		mLooper->quit(false);
	}
}

sp<Looper> HandlerThread::getLooper() {
	if (!isActive()) {
		return nullptr;
	}
	pthread_mutex_lock(&mutex);
	while (isActive() && mLooper == NULL) {
		pthread_cond_wait(&cond, &mutex);
	}
	pthread_mutex_unlock(&mutex);
	return mLooper;
}

}
}
