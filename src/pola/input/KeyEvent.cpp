/*
 * KeyEvent.cpp
 *
 *  Created on: 2016年5月30日
 *      Author: lijing
 */

#include "pola/input/KeyEvent.h"

namespace pola {
namespace input {

KeyEvent::KeyEvent(const KeyCode& keyCode, const Action& action) : mKeyCode(keyCode), mAction(action) {
}

KeyEvent::~KeyEvent() {
}

KeyEvent::KeyCode KeyEvent::getKeyCode() const {
	return mKeyCode;
}

KeyEvent::Action KeyEvent::getAction() const {
	return mAction;
}

} /* namespace input */
} /* namespace pola */
