/*
 * Looper.h
 *
 *  Created on: 2015年11月30日
 *      Author: lijing
 */

#ifndef POLA_LOOPER_H_
#define POLA_LOOPER_H_

#include "pola/utils/thread/MessageQueue.h"

#include "pola/utils/Times.h"
#include "pola/utils/RefBase.h"


#include <pthread.h>

namespace pola {
namespace utils {

class Looper : public RefBase {
public:
	~Looper();

	static void prepare();
	static sp<Looper> myLooper();

	void loop();

	void quit(bool safe);

	MessageQueue mQueue;
protected:

private:

	Looper(bool quitAllowed);

	static void initTLSKey();
	static void threadDestructor(void *st);
};
}
}

#endif /* POLA_LOOPER_H_ */
