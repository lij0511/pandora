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

PerspectiveCameraFPS::PerspectiveCameraFPS(const graphic::vec3& pos, const graphic::vec3& lookAt) :
	PerspectiveCamera(pos, lookAt), mKeyFlag(0), mAnimating(false), mLastAnimatingTime(0) {
}

PerspectiveCameraFPS::~PerspectiveCameraFPS() {
}

void PerspectiveCameraFPS::render(graphic::GraphicContext* graphic, nsecs_t timeMs) {
	if (mAnimating) {
		if (mLastAnimatingTime == 0) {
			mLastAnimatingTime = timeMs;
		}
		nsecs_t interval = timeMs - mLastAnimatingTime;
		mLastAnimatingTime = timeMs;
		graphic::vec3 dir = (mTarget - mPosition).copyNormalized();
		graphic::vec3 t = {0, 0, 0};
		if ((mKeyFlag & FLAG_KEYCODE_W) == FLAG_KEYCODE_W) {
			t += dir * interval * 0.05;
		}
		if ((mKeyFlag & FLAG_KEYCODE_S) == FLAG_KEYCODE_S) {
			t -= dir * interval * 0.05;
		}
		dir = dir.copyCross(mUpper);
		if ((mKeyFlag & FLAG_KEYCODE_A) == FLAG_KEYCODE_A) {
			t -= dir * interval * 0.05;
		}
		if ((mKeyFlag & FLAG_KEYCODE_D) == FLAG_KEYCODE_D) {
			t += dir * interval * 0.05;
		}

		setPosition(mPosition + t);
		setTarget(mTarget + t);
	}
	PerspectiveCamera::render(graphic, timeMs);
}

bool PerspectiveCameraFPS::dispatchKeyEvent(input::KeyEvent& keyEvent) {
	bool handled = false;
	if (keyEvent.getAction() == input::KeyEvent::ACTION_DOWN) {
		switch (keyEvent.getKeyCode()) {
			case input::KeyEvent::KEYCODE_W: {
				mKeyFlag |= FLAG_KEYCODE_W;
				handled = true;
				break;
			}
			case input::KeyEvent::KEYCODE_S: {
				mKeyFlag |= FLAG_KEYCODE_S;
				handled = true;
				break;
			}
			case input::KeyEvent::KEYCODE_A: {
				mKeyFlag |= FLAG_KEYCODE_A;
				handled = true;
				break;
			}
			case input::KeyEvent::KEYCODE_D: {
				mKeyFlag |= FLAG_KEYCODE_D;
				handled = true;
				break;
			}
			default:
				break;
		}
	} else {
		switch (keyEvent.getKeyCode()) {
			case input::KeyEvent::KEYCODE_W: {
				mKeyFlag &= ~FLAG_KEYCODE_W;
				handled = true;
				break;
			}
			case input::KeyEvent::KEYCODE_S: {
				mKeyFlag &= ~FLAG_KEYCODE_S;
				handled = true;
				break;
			}
			case input::KeyEvent::KEYCODE_A: {
				mKeyFlag &= ~FLAG_KEYCODE_A;
				handled = true;
				break;
			}
			case input::KeyEvent::KEYCODE_D: {
				mKeyFlag &= ~FLAG_KEYCODE_D;
				handled = true;
				break;
			}
			default:
				break;
		}
	}
	mAnimating = mKeyFlag != 0;
	if (!mAnimating) {
		mLastAnimatingTime = 0;
	}
	return handled;
}

bool PerspectiveCameraFPS::dispatchMouseEvent(input::MouseEvent& mouseEvent) {
	LOGI("mouseEvent: action=%d, buttonState=%d\n", mouseEvent.getAction(), mouseEvent.getButtonState());
	return false;
}

} /* namespace scene */
} /* namespace pola */
