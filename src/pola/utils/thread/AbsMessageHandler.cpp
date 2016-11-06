/*
 * AbsMessageHandler.cpp
 *
 *  Created on: 2016年10月7日
 *      Author: lijing
 */

#include "pola/utils/thread/AbsMessageHandler.h"
#include "pola/utils/thread/Message.h"

namespace pola {
namespace utils {

AbsMessageHandler::AbsMessageHandler() {
}

AbsMessageHandler::~AbsMessageHandler() {
}

void AbsMessageHandler::dispatchMessage(Message* msg) {
	if (msg->task != NULL) {
		msg->task->run();
	} else {
		handleMessage(msg);
	}
}

} /* namespace utils */
} /* namespace pola */
