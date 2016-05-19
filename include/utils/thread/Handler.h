/*
 * Handler.h
 *
 *  Created on: 2015年12月2日
 *      Author: lijing
 */

#ifndef HANDLER_H_
#define HANDLER_H_

#include "utils/thread/Task.h"
#include "utils/thread/Looper.h"
#include "utils/Times.h"

namespace pola {
namespace utils {

class Handler {

public:

	Handler(sp<Looper> looper);

	virtual ~Handler() {};

	bool post(Task* task) {
		return postDelayed(task, 0);
	}
	bool postDelayed(Task* task, nsecs_t delayMillis);

	bool postAndWait(Task* task);

	bool sendMessage(int what, int arg1 = 0, int arg2 = 0) {
		return sendMessageDelayed(what, arg1, arg2, 0);
	}
	bool sendMessageDelayed(int what, int arg1 = 0, int arg2 = 0, nsecs_t delayMillis = 0);

	void removeTask(Task* task);
	void removeMessages(int what);
	void removeTasksAndMessages();

	void dispatchMessage(Message* msg);

	virtual void handleMessage(Message* msg);

private:
	sp<Looper> mLooper;

	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
};
}
}

#endif /* HANDLER_H_ */
