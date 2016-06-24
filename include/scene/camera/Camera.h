/*
 * Camera.h
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#ifndef POLA_CAMERA_H_
#define POLA_CAMERA_H_

#include "input/KeyEvent.h"
#include "input/MouseEvent.h"
#include "graphic/math/Matrix4.h"
#include "graphic/math/Vector.h"
#include "scene/SceneObject.h"
#include "scene/camera/CameraController.h"

namespace pola {
namespace scene {

class Camera : public SceneObject {
public:
	Camera();
	virtual ~Camera();

	virtual void setSize(int32_t width, int32_t height);

	void setCameraController(CameraController* controller);

	virtual bool dispatchKeyEvent(input::KeyEvent& keyEvent);
	virtual bool dispatchMouseEvent(input::MouseEvent& mouseEvent);

	virtual void update(graphic::GraphicContext* graphic, nsecs_t timeMs);

protected:

	virtual void updateTransform();

	virtual void onPropertyChange();
protected:
	int32_t mWidth;
	int32_t mHeight;
	bool mCameraDirty;

	graphic::mat4 mProjection;
	CameraController* mController;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_CAMERA_H_ */
