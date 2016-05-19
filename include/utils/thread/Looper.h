/*
 * Looper.h
 *
 *  Created on: 2015年11月30日
 *      Author: lijing
 */

#ifndef POLA_LOOPER_H_
#define POLA_LOOPER_H_

#include "utils/thread/MessageQueue.h"

#include "utils/Times.h"
#include "utils/RefBase.h"


#include <pthread.h>

namespace pola {
namespace utils {

class Looper : public RefBase<Looper> {
public:
	~Looper();

	static void prepare();
	static sp<Looper> myLooper();

	void loop();

	void quit(bool safe);

	MessageQueue mQueue;
protected:

private:

	Looper();

	static void initTLSKey();
	static void threadDestructor(void *st);
};
}
}

#endif /* POLA_LOOPER_H_ */
