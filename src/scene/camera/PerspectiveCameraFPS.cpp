/*
 * PerspectiveCameraFPS.cpp
 *
 *  Created on: 2016年6月1日
 *      Author: lijing
 */

#include "log/Log.h"
#include "scene/camera/PerspectiveCameraFPS.h"

namespace pola {
namespace scene {

const static int FLAG_KEYCODE_W = 0x01;
const static int FLAG_KEYCODE_S = 0x02;
const static int FLAG_KEYCODE_A = 0x04;
const static int FLAG_KEYCODE_D = 0x08;

const static int FLAG_MOUSE_BUTTON_RIGHT = 0x10;

PerspectiveCameraFPS::PerspectiveCameraFPS(const graphic::vec3& pos, const graphic::vec3& lookAt) :
	PerspectiveCamera(pos, lookAt), mMoveSpeed(0.05f), mRotateSpeed(0.0005f), mAnimatingFlag(0), mLastAnimatingTime(0) {
}

PerspectiveCameraFPS::~PerspectiveCameraFPS() {
}

void PerspectiveCameraFPS::render(graphic::GraphicContext* graphic, nsecs_t timeMs) {
	if (mAnimatingFlag != 0) {
		if (mLastAnimatingTime == 0) {
			mLastAnimatingTime = timeMs;
		}
		nsecs_t interval = timeMs - mLastAnimatingTime;
		mLastAnimatingTime = timeMs;

		graphic::vec3 position = mPosition;
		graphic::vec3 target = mTarget;

		/*graphic::vec3 relativeRotation = (target - position).getHorizontalAngle();
		relativeRotation.x += interval * mRotateSpeed;

		graphic::vec3 t1;
		graphic::mat4 mat;
		mat.setRotationDegrees(graphic::vec3(relativeRotation.x, relativeRotation.y, 0));
		mat.transformVector(target, t1);
		t1 = (t1 - position).copyNormalized();
		t1 = t1 - position;*/
//		target += t1;


		graphic::vec3 dir = (target - position).copyNormalized();
		graphic::vec3 t;
		if ((mAnimatingFlag & FLAG_KEYCODE_W) == FLAG_KEYCODE_W) {
			t += dir * interval * 0.05;
		}
		if ((mAnimatingFlag & FLAG_KEYCODE_S) == FLAG_KEYCODE_S) {
			t -= dir * interval * 0.05;
		}
		dir = dir.copyCross(mUpper);
		if ((mAnimatingFlag & FLAG_KEYCODE_A) == FLAG_KEYCODE_A) {
			t -= dir * interval * 0.05;
		}
		if ((mAnimatingFlag & FLAG_KEYCODE_D) == FLAG_KEYCODE_D) {
			t += dir * interval * 0.05;
		}

		setPosition(position + t);
		setTarget(target + t);
	}
	PerspectiveCamera::render(graphic, timeMs);
}

bool PerspectiveCameraFPS::dispatchKeyEvent(input::KeyEvent& keyEvent) {
	bool handled = false;
	if (keyEvent.getAction() == input::KeyEvent::ACTION_DOWN) {
		switch (keyEvent.getKeyCode()) {
			case input::KeyEvent::KEYCODE_W: {
				mAnimatingFlag |= FLAG_KEYCODE_W;
				handled = true;
				break;
			}
			case input::KeyEvent::KEYCODE_S: {
				mAnimatingFlag |= FLAG_KEYCODE_S;
				handled = true;
				break;
			}
			case input::KeyEvent::KEYCODE_A: {
				mAnimatingFlag |= FLAG_KEYCODE_A;
				handled = true;
				break;
			}
			case input::KeyEvent::KEYCODE_D: {
				mAnimatingFlag |= FLAG_KEYCODE_D;
				handled = true;
				break;
			}
			default:
				break;
		}
	} else {
		switch (keyEvent.getKeyCode()) {
			case input::KeyEvent::KEYCODE_W: {
				mAnimatingFlag &= ~FLAG_KEYCODE_W;
				handled = true;
				break;
			}
			case input::KeyEvent::KEYCODE_S: {
				mAnimatingFlag &= ~FLAG_KEYCODE_S;
				handled = true;
				break;
			}
			case input::KeyEvent::KEYCODE_A: {
				mAnimatingFlag &= ~FLAG_KEYCODE_A;
				handled = true;
				break;
			}
			case input::KeyEvent::KEYCODE_D: {
				mAnimatingFlag &= ~FLAG_KEYCODE_D;
				handled = true;
				break;
			}
			default:
				break;
		}
	}
	if (mAnimatingFlag == 0) {
		mLastAnimatingTime = 0;
	}
	return handled;
}

bool PerspectiveCameraFPS::dispatchMouseEvent(input::MouseEvent& mouseEvent) {
//	LOGI("mouseEvent: action=%d, buttonState=%d\n", mouseEvent.getAction(), mouseEvent.getButtonState());
	bool handled = false;
	switch (mouseEvent.getAction()) {
		case input::MouseEvent::ACTION_DOWN:
			if (mouseEvent.getButton() == input::MouseEvent::BUTTON_RIGHT) {
				mAnimatingFlag |= FLAG_MOUSE_BUTTON_RIGHT;
				mMousePosition = graphic::vec2(mouseEvent.getX(), mouseEvent.getY());
				handled = true;
			}
			break;
		case input::MouseEvent::ACTION_UP:
			if (mouseEvent.getButton() == input::MouseEvent::BUTTON_RIGHT) {
				mAnimatingFlag &= ~FLAG_MOUSE_BUTTON_RIGHT;
				handled = true;
			}
			break;
		case input::MouseEvent::ACTION_MOVE:
			if ((mAnimatingFlag & FLAG_MOUSE_BUTTON_RIGHT) == FLAG_MOUSE_BUTTON_RIGHT) {
				mMouseMovePosition = graphic::vec2(mouseEvent.getX(), mouseEvent.getY()) - mMousePosition;
				handled = true;
			}
			break;
		default:
			break;
	}
	return handled;
}

} /* namespace scene */
} /* namespace pola */
