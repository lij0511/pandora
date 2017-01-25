/*
 * test.cpp
 *
 *  Created on: 2016年1月14日
 *      Author: lijing
 */

#include "pola/utils/thread/Handler.h"
#include "pola/utils/thread/FunctionalTask.h"

class MyHandler : public pola::utils::Handler {
public:
	MyHandler() : pola::utils::Handler(pola::utils::Looper::myLooper()) {}
	virtual void handleMessage(pola::utils::Message* msg) {
		printf("haha msg=%d, arg1=%d, arg2=%d \n", msg->what, msg->arg1, msg->arg2);
	}
};

pola::utils::Handler* handler() {
	static pola::utils::Handler* handler = new MyHandler;
	return handler;
}

void test() {
	printf("in test\n");
	handler()->postDelayed(new pola::utils::FunctionalTask(pola::utils::bind(test)), 16);
}

int main(int argc, char *argv[]) {
	pola::utils::Looper::prepare();
	handler()->sendMessage(5);
	handler()->sendMessageDelayed(6, 1, 2, NULL, 4000);

	handler()->postDelayed(new pola::utils::FunctionalTask(pola::utils::bind(test)), 2000);

	pola::utils::Looper::myLooper()->loop();


}
