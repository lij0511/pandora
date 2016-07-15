/*
 * Handler.cpp
 *
 *  Created on: 2016年5月18日
 *      Author: lijing
 */

#include "pola/utils/thread/Handler.h"

namespace pola {
namespace utils {

Handler::Handler(sp<Looper> looper)  : mLooper(looper) {
}

bool Handler::postDelayed(Task* task, nsecs_t delayMillis) {
	return mLooper->mQueue.enqueueMessage(new Message(this, task), uptimeMillis() + delayMillis);
}

bool Handler::postAndWait(Task* task) {
	if (Looper::myLooper() == mLooper) {
		task->run();
		task->tryCleanup();
		return true;
	} else {
		BlockingTask* blockingTask = new BlockingTask(task, &mutex, &cond);
		bool r = post(blockingTask);

		if (r) {
			pthread_mutex_lock(&mutex);
			while (!blockingTask->done) {
				pthread_cond_wait(&cond, & mutex);
			}
			pthread_mutex_unlock(&mutex);
		}
		delete blockingTask;
		return r;
	}
}

bool Handler::sendMessageDelayed(int what, int arg1, int arg2, nsecs_t delayMillis) {
	return mLooper->mQueue.enqueueMessage(new Message(this, what, arg1, arg2), uptimeMillis() + delayMillis);
}

void Handler::removeTask(Task* task) {
}

void Handler::removeMessages(int what) {
	mLooper->mQueue.removeMessages(this, what);
}

void Handler::removeTasksAndMessages() {
	mLooper->mQueue.removeMessages(this);
}

void Handler::dispatchMessage(Message* msg) {
	if (msg->task != nullptr) {
		msg->task->run();
	} else {
		handleMessage(msg);
	}
}

void Handler::handleMessage(Message* msg) {
}

}
}


