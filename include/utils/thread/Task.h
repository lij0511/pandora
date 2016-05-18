/*
 * Task.h
 *
 *  Created on: 2015年12月1日
 *      Author: lijing
 */

#ifndef TASK_H_
#define TASK_H_

#include <pthread.h>

namespace pola {
namespace utils {

class Task {

public:
	const bool cleanup;

	Task(bool shouldCleanup = true) : cleanup(shouldCleanup) {
	}

	virtual ~Task() {};
	virtual void run() {
	};

	virtual void tryCleanup() {
		if (cleanup) {
			delete this;
		}
	}
};

class BlockingTask : public Task {

public:

	bool done;
	pthread_mutex_t* mutex;
	pthread_cond_t* cond;

	BlockingTask(Task* task, pthread_mutex_t* m, pthread_cond_t* c) : Task(false), done(false), mutex(m), cond(c),
			real_task(task) {
	}
	virtual ~BlockingTask() {
		if (real_task) {
			real_task->tryCleanup();
			real_task = nullptr;
		}
	};

	void run() override {
		if (real_task) {
			real_task->run();
		}
	}

	virtual void tryCleanup() override {
		Task::tryCleanup();
		if (!done) {
			pthread_mutex_lock(mutex);
			done = true;
			pthread_cond_signal(cond);
			pthread_mutex_unlock(mutex);
		}
	}

private:
	Task* real_task;

};
}
}

#endif /* TASK_H_ */
