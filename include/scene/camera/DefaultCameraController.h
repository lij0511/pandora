/*
 * DefaultCameraController.h
 *
 *  Created on: 2016年6月24日
 *      Author: lijing
 */

#ifndef DEFAULTCAMERACONTROLLER_H_
#define DEFAULTCAMERACONTROLLER_H_

#include "scene/camera/CameraController.h"
#include "scene/camera/Camera.h"

namespace pola {
namespace scene {

/*
 *
 */
class DefaultCameraController: public CameraController {
public:
	DefaultCameraController(Camera* camera);
	virtual ~DefaultCameraController();

	virtual bool animate(nsecs_t timeMs);
	virtual bool dispatchKeyEvent(input::KeyEvent& keyEvent);
	virtual bool dispatchMouseEvent(input::MouseEvent& mouseEvent);

protected:
	virtual void updateTransform();

private:
	float mMoveSpeed;
	float mRotateSpeed;

	int32_t mAnimatingFlag;
	nsecs_t mLastAnimatingTime;

	utils::sp<SceneObject> mPitch;
	utils::sp<SceneObject> mYaw;
};

} /* namespace scene */
} /* namespace pola */

#endif /* DEFAULTCAMERACONTROLLER_H_ */
