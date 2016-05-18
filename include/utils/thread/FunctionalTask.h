/*
 * FunctionalTask.h
 *
 *  Created on: 2015年12月1日
 *      Author: lijing
 */

#ifndef FUNCTIONALTASK_H_
#define FUNCTIONALTASK_H_

#include "utils/thread/Task.h"
#include "utils/Functional.h"

namespace pola {
namespace utils {

class FunctionalTask : public Task {
public:
	FunctionalTask(Closure func) : m_func(func) {};

	~FunctionalTask() {
	};

	void run() override {
		m_func();
	}
private:
	Closure m_func;
};
}
}

#endif /* FUNCTIONALTASK_H_ */
