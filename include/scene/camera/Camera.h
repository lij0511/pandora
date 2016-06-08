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
#include "scene/node/SceneNode.h"
#include "scene/camera/CameraController.h"

namespace pola {
namespace scene {

class Camera : public SceneNode {
public:
	Camera();
	virtual ~Camera();

	virtual void setSize(int32_t width, int32_t height);

	void setCameraController(CameraController* controller);


	virtual bool dispatchKeyEvent(input::KeyEvent& keyEvent);
	virtual bool dispatchMouseEvent(input::MouseEvent& mouseEvent);

protected:
	virtual void render(graphic::GraphicContext* graphic, nsecs_t timeMs);
	virtual void updateMatrix();

	virtual void onPropertyChange();
protected:
	graphic::mat4 mMatrix;
	int32_t mWidth;
	int32_t mHeight;
	bool mCameraDirty;

	graphic::mat4 mProjection;
	graphic::mat4 mView;
	CameraController* mController;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_CAMERA_H_ */
