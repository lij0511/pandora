/*
 * HandlerThread.h
 *
 *  Created on: 2015年12月2日
 *      Author: lijing
 */

#ifndef POLA_HANDLERTHREAD_H_
#define POLA_HANDLERTHREAD_H_

#include "pola/utils/thread/Thread.h"
#include "pola/utils/thread/Handler.h"
#include "pola/utils/thread/Looper.h"

namespace pola {
namespace utils {

class HandlerThread : public Thread {
public:
	HandlerThread();
	HandlerThread(int priority, bool joinable);
	virtual ~HandlerThread();

	virtual void start();
	void stop();

	virtual void run() override;
	sp<Looper> getLooper();

private:
	sp<Looper> mLooper;
};
}

}

#endif /* POLA_HANDLERTHREAD_H_ */
