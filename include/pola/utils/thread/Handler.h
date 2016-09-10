/*
 * Handler.h
 *
 *  Created on: 2015年12月2日
 *      Author: lijing
 */

#ifndef POLA_HANDLER_H_
#define POLA_HANDLER_H_

#include "pola/utils/thread/Task.h"
#include "pola/utils/thread/Looper.h"
#include "pola/utils/Times.h"

namespace pola {
namespace utils {

class Handler : public RefBase<Handler> {

public:

	Handler(sp<Looper> looper);

	virtual ~Handler() {};

	bool post(Task* task) {
		return postDelayed(task, 0);
	}
	bool postDelayed(Task* task, p_nsecs_t delayMillis);

	bool postAndWait(Task* task);

	bool sendMessage(int what, int arg1 = 0, int arg2 = 0) {
		return sendMessageDelayed(what, arg1, arg2, 0);
	}
	bool sendMessageDelayed(int what, int arg1 = 0, int arg2 = 0, p_nsecs_t delayMillis = 0);

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

#endif /* POLA_HANDLER_H_ */
