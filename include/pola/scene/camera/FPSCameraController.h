/*
 * FPSCameraController.h
 *
 *  Created on: 2016年6月5日
 *      Author: lijing
 */

#ifndef POLA_FPSCAMERACONTROLLER_H_
#define POLA_FPSCAMERACONTROLLER_H_

#include "pola/scene/camera/CameraController.h"
#include "pola/scene/camera/Camera.h"

namespace pola {
namespace scene {

class FPSCameraController: public CameraController {
public:
	FPSCameraController(Camera* camera);
	virtual ~FPSCameraController();

	virtual bool animate(nsecs_t timeMs);
	virtual bool dispatchKeyEvent(input::KeyEvent& keyEvent);
	virtual bool dispatchMouseEvent(input::MouseEvent& mouseEvent);

private:
	float mMoveSpeed;
	float mRotateSpeed;

	int32_t mAnimatingFlag;
	nsecs_t mLastAnimatingTime;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_FPSCAMERACONTROLLER_H_ */
