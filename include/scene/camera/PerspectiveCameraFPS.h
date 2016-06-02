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
	PerspectiveCameraFPS(const graphic::vec3& pos = graphic::vec3(0.0f, 0.0f, 1.0f), const graphic::vec3& lookAt = graphic::vec3(0.0f, 0.0f, 0.0f));
	virtual ~PerspectiveCameraFPS();

	virtual void render(graphic::GraphicContext* graphic, nsecs_t timeMs);

	virtual bool dispatchKeyEvent(input::KeyEvent& keyEvent);
	virtual bool dispatchMouseEvent(input::MouseEvent& mouseEvent);

private:
	float mMoveSpeed;
	float mRotateSpeed;

	int32_t mAnimatingFlag;
	graphic::vec2 mMousePosition;
	graphic::vec2 mRotateStart;
	bool mRotating;
	nsecs_t mLastAnimatingTime;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_PERSPECTIVECAMERAFPS_H_ */
