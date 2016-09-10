/*
 * Message.h
 *
 *  Created on: 2015年12月1日
 *      Author: lijing
 */

#ifndef POLA_MESSAGE_H_
#define POLA_MESSAGE_H_

#include "pola/utils/Times.h"
#include "pola/utils/thread/Task.h"
#include "pola/utils/RefBase.h"

namespace pola {
namespace utils {

class Handler;

class Message {
public:
	Message(sp<Handler> h, Task* t) : what(0), arg1(0), arg2(0), task(t), when(0), target(h), next(nullptr) {}
	Message(sp<Handler> h, int w = 0, int a1 = 0, int a2 = 0) : what(w), arg1(a1), arg2(a2), task(nullptr), when(0), target(h), next(nullptr) {}
	~Message() {
		if (task) {
			task->tryCleanup();
		}
		task = nullptr;
		next = nullptr;
		target = nullptr;
	}
	int what;
	int arg1;
	int arg2;
	Task* task;
	p_nsecs_t when;
	sp<Handler> target;

	Message* next;

};
}
}

#endif /* POLA_MESSAGE_H_ */
