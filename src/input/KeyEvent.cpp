/*
 * KeyEvent.cpp
 *
 *  Created on: 2016年5月30日
 *      Author: lijing
 */

#include "input/KeyEvent.h"

namespace pola {
namespace input {

KeyEvent::KeyEvent(const KeyCode& keyCode, const Action& action) : mKeyCode(keyCode), mAction(action) {
}

KeyEvent::~KeyEvent() {
}

} /* namespace input */
} /* namespace pola */
