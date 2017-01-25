/*
 * AbsMessageHandler.h
 *
 *  Created on: 2016年10月7日
 *      Author: lijing
 */

#ifndef POLA_UTILS_ABSMESSAGEHANDLER_H_
#define POLA_UTILS_ABSMESSAGEHANDLER_H_

#include "pola/utils/RefBase.h"

namespace pola {
namespace utils {

class Message;

/*
 *
 */
class AbsMessageHandler: public RefBase {
public:
	AbsMessageHandler();
	virtual ~AbsMessageHandler();

	void dispatchMessage(Message* msg);

	virtual void handleMessage(Message* msg) = 0;
	/**
	 * Called when recycle the Message.
	 */
	virtual void handleRecycleMessage(Message* msg) = 0;
};

} /* namespace utils */
} /* namespace pola */

#endif /* POLA_UTILS_ABSMESSAGEHANDLER_H_ */
