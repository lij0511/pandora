/*
 * rptest.cpp
 *
 *  Created on: 2015年12月5日
 *      Author: lijing
 */

#define DEBUG 1

#include <stdio.h>
#include <stdlib.h>

#include "pola/utils/RefBase.h"

#include "pola/utils/thread/Handler.h"
#include "pola/utils/thread/HandlerThread.h"
#include "pola/utils/thread/FunctionalTask.h"

#include <functional>

using namespace pola;
using namespace pola::utils;

class RpTest : public RefBase<RpTest> {
public:
	RpTest() { c = 100;};
	~RpTest() {
		printf("heihei=%d\n", c);
	};
private:
	int c;
};

sp<RpTest> ssss = new RpTest;

sp<RpTest> getSp() {
	sp<RpTest> tmp = ssss;
	return tmp;
}

void test1(int hehe) {
	sp<RpTest> tmp;
	for (unsigned i = 0; i < 1000; i ++) {
		tmp = ssss;
	}
	printf("test1 %d\n", hehe);
}

void test2() {
	sp<RpTest> wwww;
	for (unsigned i = 0; i < 1000; i ++) {
		wwww = getSp();
	}
	printf("haha\n");
}

int main() {
	Looper::prepare();

	HandlerThread* t1 = new HandlerThread();
	t1->start();
	HandlerThread* t2 = new HandlerThread();
	t2->start();

	sp<Handler> h1 = new Handler(t1->getLooper());
	sp<Handler> h2 = new Handler(Looper::myLooper());

	h1->postDelayed(new pola::utils::FunctionalTask(pola::utils::bind(test1, 30)), 1000);
	h2->post(new pola::utils::FunctionalTask(pola::utils::bind(test2)));
	h2->postDelayed(new pola::utils::FunctionalTask(pola::utils::bind(test2)), 3000);
	h2->postDelayed(new pola::utils::FunctionalTask(pola::utils::bind(test2)), 5000);

	Looper::myLooper()->loop();
}
