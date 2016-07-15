/*
 * FunctionalTask.h
 *
 *  Created on: 2015年12月1日
 *      Author: lijing
 */

#ifndef POLA_FUNCTIONALTASK_H_
#define POLA_FUNCTIONALTASK_H_

#include "pola/utils/thread/Task.h"
#include "pola/utils/Functional.h"

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

#endif /* POLA_FUNCTIONALTASK_H_ */
