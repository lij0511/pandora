/*
 * HandlerThread.h
 *
 *  Created on: 2015年12月2日
 *      Author: lijing
 */

#ifndef HANDLERTHREAD_H_
#define HANDLERTHREAD_H_

#include "utils/thread/Thread.h"
#include "utils/thread/Looper.h"

namespace pola {
namespace utils {

class HandlerThread : public Thread {
public:
	HandlerThread();
	HandlerThread(int priority, bool joinable);
	virtual ~HandlerThread();

	void start() override;
	void stop();

	void run() override;
	sp<Looper> getLooper();

private:
	sp<Looper> mLooper;
};
}

}

#endif /* HANDLERTHREAD_H_ */
