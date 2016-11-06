/*
 * Message.h
 *
 *  Created on: 2015年12月1日
 *      Author: lijing
 */

#ifndef POLA_MESSAGE_H_
#define POLA_MESSAGE_H_

#include "pola/utils/thread/AbsMessageHandler.h"
#include "pola/utils/Times.h"
#include "pola/utils/thread/Task.h"

namespace pola {
namespace utils {

class Message {
public:
	Message(sp<AbsMessageHandler> h, Task* t) : what(0), arg1(0), arg2(0), obj(NULL), task(t), when(0), target(h), next(NULL) {}
	Message(sp<AbsMessageHandler> h, int w = 0, int a1 = 0, int a2 = 0, void* o = NULL) : what(w), arg1(a1), arg2(a2), obj(o), task(NULL), when(0), target(h), next(NULL) {}
	~Message() {
		if (task) {
			task->tryCleanup();
		}
		task = NULL;
		next = NULL;
		target = NULL;
	}
	int what;
	int arg1;
	int arg2;
	void* obj;
	Task* task;
	p_nsecs_t when;
	sp<AbsMessageHandler> target;

	Message* next;

};
}
}

#endif /* POLA_MESSAGE_H_ */
