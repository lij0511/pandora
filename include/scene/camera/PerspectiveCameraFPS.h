/*
 * PerspectiveCameraFPS.h
 *
 *  Created on: 2016年6月1日
 *      Author: lijing
 */

#ifndef POLA_PERSPECTIVECAMERAFPS_H_
#define POLA_PERSPECTIVECAMERAFPS_H_

#include "scene/camera/PerspectiveCamera.h"

namespace pola {
namespace scene {

class PerspectiveCameraFPS: public PerspectiveCamera {
public:
	PerspectiveCameraFPS();
	virtual ~PerspectiveCameraFPS();

	virtual void render(graphic::GraphicContext* graphic, nsecs_t timeMs);

	virtual bool dispatchKeyEvent(input::KeyEvent& keyEvent);
	virtual bool dispatchMouseEvent(input::MouseEvent& mouseEvent);

private:
	float mMoveSpeed;
	float mRotateSpeed;

	int32_t mAnimatingFlag;
	graphic::vec2 mMousePosition;
	graphic::vec2 mMouseMovePosition;
	bool mRotating;
	nsecs_t mLastAnimatingTime;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_PERSPECTIVECAMERAFPS_H_ */
