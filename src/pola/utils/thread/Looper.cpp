/*
 * Looper.cpp
 *
 *  Created on: 2015年11月30日
 *      Author: lijing
 */

#include "pola/utils/thread/Looper.h"
#include "pola/utils/thread/Handler.h"

#include <stdio.h>
#include <stdlib.h>

#include "pola/log/Log.h"

namespace pola {
namespace utils {

static pthread_once_t gTLSOnce = PTHREAD_ONCE_INIT;
static pthread_key_t gTLSKey = 0;

Looper::Looper() {
}

Looper::~Looper() {
}

void Looper::initTLSKey() {
    int result = pthread_key_create(&gTLSKey, threadDestructor);
    LOG_FATAL_IF((result != 0), "Could not allocate TLS key.");
}

void Looper::threadDestructor(void *st) {
	Looper* const self = static_cast<Looper*>(st);
	if (self != NULL) {
		self->deref();
	}
}

sp<Looper> Looper::myLooper() {
	int result = pthread_once(&gTLSOnce, initTLSKey);
	LOG_FATAL_IF((result != 0), "pthread_once failed");

	return (Looper*)pthread_getspecific(gTLSKey);
}

void Looper::prepare() {
	sp<Looper> looper = myLooper();
	if (looper != NULL) {
		throw "Only one Looper may be created per thread";
	}
	looper = new Looper();
	looper->ref();
	pthread_setspecific(gTLSKey, looper.get());
}

void Looper::loop() {
	for(;;) {
		Message* msg = mQueue.next();
		if (!msg) {
			break;
		}
		if (msg->target != nullptr) {
			msg->target->dispatchMessage(msg);
		}
		delete msg;
	}
}

void Looper::quit(bool safe) {
	mQueue.quit(safe);
}
}
}
