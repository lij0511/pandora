/*
 * MouseEvent.h
 *
 *  Created on: 2016年6月1日
 *      Author: lijing
 */

#ifndef POLA_MOUSEEVENT_H_
#define POLA_MOUSEEVENT_H_

#include <stdint.h>

namespace pola {
namespace input {

class MouseEvent {
public:

	enum Action {
		ACTION_DOWN									= 0x01,
		ACTION_UP											= 0x02,
		ACTION_MOVE									= 0x04,
	};

	enum Button {
		BUTTON_LEFT										= 0x01,
		BUTTON_RIGHT									= 0x02,
		BUTTON_MIDDLE								= 0x04,
		BUTTON_WHEEL_FORWARD			= 0x08,
		BUTTON_WHEEL_BACKWARD		= 0x10,

		BUTTON_NONE									= 0xFF,

		BUTTON_STATE_MASK						= BUTTON_LEFT | BUTTON_RIGHT | BUTTON_MIDDLE
				| BUTTON_WHEEL_FORWARD | BUTTON_WHEEL_BACKWARD,
	};

	MouseEvent(float x, float y, Action action, Button button, int buttonState);
	virtual ~MouseEvent();

	float getX() const;
	float getY() const;

	Action getAction() const;
	Button getButton() const;
	int32_t getButtonState() const;

private:
	float mX;
	float mY;

	Action mAction;
	Button mButton;
	int32_t mButtonState;
};

} /* namespace input */
} /* namespace pola */

#endif /* POLA_MOUSEEVENT_H_ */
