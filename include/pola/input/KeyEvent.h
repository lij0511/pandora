/*
 * KeyEvent.h
 *
 *  Created on: 2016年5月30日
 *      Author: lijing
 */

#ifndef KEYEVENT_H_
#define KEYEVENT_H_

namespace pola {
namespace input {

/*
 *
 */
class KeyEvent {
public:

	enum Action {
		ACTION_DOWN,
		ACTION_UP,
	};

	enum KeyCode {
		KEYCODE_0,
		KEYCODE_1,
		KEYCODE_2,
		KEYCODE_3,
		KEYCODE_4,
		KEYCODE_5,
		KEYCODE_6,
		KEYCODE_7,
		KEYCODE_8,
		KEYCODE_9,

		KEYCODE_NUMPAD_0,
		KEYCODE_NUMPAD_1,
		KEYCODE_NUMPAD_2,
		KEYCODE_NUMPAD_3,
		KEYCODE_NUMPAD_4,
		KEYCODE_NUMPAD_5,
		KEYCODE_NUMPAD_6,
		KEYCODE_NUMPAD_7,
		KEYCODE_NUMPAD_8,
		KEYCODE_NUMPAD_9,

		KEYCODE_A,
		KEYCODE_B,
		KEYCODE_C,
		KEYCODE_D,
		KEYCODE_E,
		KEYCODE_F,
		KEYCODE_G,
		KEYCODE_H,
		KEYCODE_I,
		KEYCODE_J,
		KEYCODE_K,
		KEYCODE_L,
		KEYCODE_M,
		KEYCODE_N,
		KEYCODE_O,
		KEYCODE_P,
		KEYCODE_Q,
		KEYCODE_R,
		KEYCODE_S,
		KEYCODE_T,
		KEYCODE_U,
		KEYCODE_V,
		KEYCODE_W,
		KEYCODE_X,
		KEYCODE_Y,
		KEYCODE_Z,

		KEYCODE_LEFT,
		KEYCODE_RIGHT,
		KEYCODE_UP,
		KEYCODE_DOWN,
	};

	KeyEvent(const KeyCode& keyCode, const Action& action);
	virtual ~KeyEvent();

	KeyCode getKeyCode() const;
	Action getAction() const;

private:
	KeyCode mKeyCode;
	Action mAction;
};

} /* namespace input */
} /* namespace pola */

#endif /* KEYEVENT_H_ */
