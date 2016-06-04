/*
 * FPSCameraController.cpp
 *
 *  Created on: 2016年6月5日
 *      Author: lijing
 */

#include "scene/camera/FPSCameraController.h"

namespace pola {
namespace scene {

const static int FLAG_KEYCODE_W = 0x01;
const static int FLAG_KEYCODE_S = 0x02;
const static int FLAG_KEYCODE_A = 0x04;
const static int FLAG_KEYCODE_D = 0x08;

const static int FLAG_MOUSE_BUTTON_RIGHT = 0x10;

FPSCameraController::FPSCameraController(Camera* camera)
	: CameraController((camera)), mMoveSpeed(0.05f), mRotateSpeed(0.5f), mAnimatingFlag(0), mLastAnimatingTime(0) {
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

//			mPosition.z += 0.0001;
//			graphic::vec3 position = mCamera->getPosition();
//			position.z += mMoveSpeed * interval;
//			mCamera->setPosition(position);
	//		graphic::vec3 target = mTarget - mPosition;
			mRotation.x -= 0.002;
//			graphic::quat4 rotation = mCamera->getRotation();
//			rotation.x += 0.002;
//			mCamera->setRotation(rotation);

			/*graphic::vec3 dir = target.copyNormalized();
			graphic::vec3 t;
			if ((mAnimatingFlag & FLAG_KEYCODE_W) == FLAG_KEYCODE_W) {
				t += dir * interval * mMoveSpeed;
			}
			if ((mAnimatingFlag & FLAG_KEYCODE_S) == FLAG_KEYCODE_S) {
				t -= dir * interval * mMoveSpeed;
			}
			dir = dir.copyCross(mUpper);
			if ((mAnimatingFlag & FLAG_KEYCODE_A) == FLAG_KEYCODE_A) {
				t += dir * interval * mMoveSpeed;
			}
			if ((mAnimatingFlag & FLAG_KEYCODE_D) == FLAG_KEYCODE_D) {
				t -= dir * interval * mMoveSpeed;
			}

			setPosition(position + t);
			setTarget(mPosition + target);*/
			return true;
		}
	return false;
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

bool FPSCameraController::dispatchMouseEvent(input::MouseEvent& mouseEvent) {
	return false;
}

} /* namespace scene */
} /* namespace pola */
