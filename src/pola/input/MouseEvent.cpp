/*
 * MouseEvent.cpp
 *
 *  Created on: 2016年6月1日
 *      Author: lijing
 */

#include "pola/input/MouseEvent.h"

namespace pola {
namespace input {

MouseEvent::MouseEvent(float x, float y, Action action, Button button, int buttonState) :
	mX(x), mY(y), mAction(action), mButton(button), mButtonState(buttonState & BUTTON_STATE_MASK) {
}

MouseEvent::~MouseEvent() {
}

float MouseEvent::getX() const {
	return mX;
}

float MouseEvent::getY() const {
	return mY;
}

MouseEvent::Action MouseEvent::getAction() const {
	return mAction;
}

MouseEvent::Button MouseEvent::getButton() const {
	return mButton;
}

int32_t MouseEvent::getButtonState() const {
	return mButtonState;
}

} /* namespace input */
} /* namespace pola */
