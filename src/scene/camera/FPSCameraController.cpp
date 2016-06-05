/*
 * FPSCameraController.cpp
 *
 *  Created on: 2016年6月5日
 *      Author: lijing
 */

#include "scene/camera/FPSCameraController.h"
#include "utils/Math.h"

namespace pola {
namespace scene {

const static int FLAG_KEYCODE_W = 0x01;
const static int FLAG_KEYCODE_S = 0x02;
const static int FLAG_KEYCODE_A = 0x04;
const static int FLAG_KEYCODE_D = 0x08;

const static int FLAG_KEYCODE_LEFT = 0x10;
const static int FLAG_KEYCODE_RIGHT = 0x20;
const static int FLAG_KEYCODE_UP = 0x40;
const static int FLAG_KEYCODE_DOWN = 0x80;

const static int FLAG_MOUSE_BUTTON_RIGHT = 0x100;

FPSCameraController::FPSCameraController(Camera* camera)
	: CameraController((camera)), mMoveSpeed(0.05f), mRotateSpeed(0.0005f), mAnimatingFlag(0), mLastAnimatingTime(0) {
}

FPSCameraController::~FPSCameraController() {
}

bool FPSCameraController::animate(nsecs_t timeMs) {
	if (mAnimatingFlag != 0) {
			if (mLastAnimatingTime == 0) {
				mLastAnimatingTime = timeMs;
			}
			nsecs_t interval = timeMs - mLastAnimatingTime;
			mLastAnimatingTime = timeMs;

			if ((mAnimatingFlag & FLAG_KEYCODE_LEFT) == FLAG_KEYCODE_LEFT) {
				mRotation.y -= interval * mRotateSpeed;
			}
			if ((mAnimatingFlag & FLAG_KEYCODE_RIGHT) == FLAG_KEYCODE_RIGHT) {
				mRotation.y += interval * mRotateSpeed;
			}
			if ((mAnimatingFlag & FLAG_KEYCODE_UP) == FLAG_KEYCODE_UP) {
				mRotation.x -= interval * mRotateSpeed;
			}
			if ((mAnimatingFlag & FLAG_KEYCODE_DOWN) == FLAG_KEYCODE_DOWN) {
				mRotation.x += interval * mRotateSpeed;
			}
			mRotation.x = utils::fclamp<float>(mRotation.x, - M_PI_2, M_PI_2);

			if ((mAnimatingFlag & FLAG_KEYCODE_W) == FLAG_KEYCODE_W) {
				mPosition.z += interval * mMoveSpeed;
			}
			if ((mAnimatingFlag & FLAG_KEYCODE_S) == FLAG_KEYCODE_S) {
				mPosition.z -= interval * mMoveSpeed;
			}
			if ((mAnimatingFlag & FLAG_KEYCODE_A) == FLAG_KEYCODE_A) {
				mPosition.x += interval * mMoveSpeed;
			}
			if ((mAnimatingFlag & FLAG_KEYCODE_D) == FLAG_KEYCODE_D) {
				mPosition.x -= interval * mMoveSpeed;
			}
			return true;
		}
	return false;
}

graphic::mat4 FPSCameraController::getTransform() {
	graphic::mat4 m;
	graphic::quat4 q;
	mRotation.getQuaternion(q);
	m.compose(mPosition, q, {1, 1, 1});
	return m;
}

bool FPSCameraController::dispatchKeyEvent(input::KeyEvent& keyEvent) {
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
			case input::KeyEvent::KEYCODE_LEFT: {
				mAnimatingFlag |= FLAG_KEYCODE_LEFT;
				handled = true;
				break;
			}
			case input::KeyEvent::KEYCODE_RIGHT: {
				mAnimatingFlag |= FLAG_KEYCODE_RIGHT;
				handled = true;
				break;
			}
			case input::KeyEvent::KEYCODE_UP: {
				mAnimatingFlag |= FLAG_KEYCODE_UP;
				handled = true;
				break;
			}
			case input::KeyEvent::KEYCODE_DOWN: {
				mAnimatingFlag |= FLAG_KEYCODE_DOWN;
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
			case input::KeyEvent::KEYCODE_LEFT: {
				mAnimatingFlag &= ~FLAG_KEYCODE_LEFT;
				handled = true;
				break;
			}
			case input::KeyEvent::KEYCODE_RIGHT: {
				mAnimatingFlag &= ~FLAG_KEYCODE_RIGHT;
				handled = true;
				break;
			}
			case input::KeyEvent::KEYCODE_UP: {
				mAnimatingFlag &= ~FLAG_KEYCODE_UP;
				handled = true;
				break;
			}
			case input::KeyEvent::KEYCODE_DOWN: {
				mAnimatingFlag &= ~FLAG_KEYCODE_DOWN;
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

bool FPSCameraController::dispatchMouseEvent(input::MouseEvent& mouseEvent) {
	bool handled = false;
	return handled;
}

} /* namespace scene */
} /* namespace pola */
