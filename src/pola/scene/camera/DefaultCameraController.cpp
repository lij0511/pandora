/*
 * DefaultCameraController.cpp
 *
 *  Created on: 2016年6月24日
 *      Author: lijing
 */

#include "pola/scene/camera/DefaultCameraController.h"

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

DefaultCameraController::DefaultCameraController(Camera* camera)
	: CameraController(camera), mMoveSpeed(0.05f), mRotateSpeed(0.0005f), mAnimatingFlag(0), mLastAnimatingTime(0) {
	mPitch = new SceneObject;
	mYaw = new SceneObject;
}

DefaultCameraController::~DefaultCameraController() {
}

bool DefaultCameraController::animate(p_nsecs_t timeMs) {
	if (mAnimatingFlag != 0) {
			if (mLastAnimatingTime == 0) {
				mLastAnimatingTime = timeMs;
			}
			p_nsecs_t interval = timeMs - mLastAnimatingTime;
			mLastAnimatingTime = timeMs;
			graphic::Euler yaw = mYaw->getRotation();
			if ((mAnimatingFlag & FLAG_KEYCODE_LEFT) == FLAG_KEYCODE_LEFT) {
				yaw.y += interval * mRotateSpeed;
			}
			if ((mAnimatingFlag & FLAG_KEYCODE_RIGHT) == FLAG_KEYCODE_RIGHT) {
				yaw.y -= interval * mRotateSpeed;
			}
			graphic::Euler pitch = mPitch->getRotation();
			if ((mAnimatingFlag & FLAG_KEYCODE_UP) == FLAG_KEYCODE_UP) {
				pitch.x += interval * mRotateSpeed;
			}
			if ((mAnimatingFlag & FLAG_KEYCODE_DOWN) == FLAG_KEYCODE_DOWN) {
				pitch.x -= interval * mRotateSpeed;
			}
//			mRotation.x = utils::fclamp<float>(mRotation.x, - M_PI_2, M_PI_2);

			graphic::vec3 p = mYaw->getPosition();
			if ((mAnimatingFlag & FLAG_KEYCODE_W) == FLAG_KEYCODE_W) {
//				p.z += interval * mMoveSpeed;
				translateZ(- interval * mMoveSpeed);
			}
			if ((mAnimatingFlag & FLAG_KEYCODE_S) == FLAG_KEYCODE_S) {
//				p.z -= interval * mMoveSpeed;
				translateZ(interval * mMoveSpeed);
			}
			if ((mAnimatingFlag & FLAG_KEYCODE_A) == FLAG_KEYCODE_A) {
//				p.x += interval * mMoveSpeed;
				translateX(- interval * mMoveSpeed);
			}
			if ((mAnimatingFlag & FLAG_KEYCODE_D) == FLAG_KEYCODE_D) {
//				p.x -= interval * mMoveSpeed;
				translateX(interval * mMoveSpeed);
			}

			mYaw->setRotation(yaw);
			mPitch->setRotation(pitch);

			onPropertyChange();
			return true;
		}
	return false;
}

bool DefaultCameraController::dispatchKeyEvent(input::KeyEvent& keyEvent) {
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

bool DefaultCameraController::dispatchMouseEvent(input::MouseEvent& mouseEvent) {
	bool handled = false;
	return handled;
}

bool DefaultCameraController::updateTransform() {
	if (mMatrixDirty) {
		graphic::quat4 quat;
		mRotation.getQuaternion(quat);
		mMatrix.compose(mPosition, quat, mScale);
		mWorldMatrix.loadMultiply(mYaw->getWorldTransform() * mPitch->getWorldTransform(), mMatrix);
		mMatrixDirty = false;
		return true;
	}
	return false;
}

} /* namespace scene */
} /* namespace pola */
