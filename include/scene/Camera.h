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
#include "graphic/Matrix4.h"
#include "graphic/Vector.h"
#include "scene/node/SceneNode.h"

namespace pola {
namespace scene {

class Camera : public SceneNode {
public:
	Camera(const graphic::vec3& pos = graphic::vec3(0.0f, 0.0f, 1.0f));
	virtual ~Camera();

	virtual void setSize(int32_t width, int32_t height);

	virtual void render(graphic::GraphicContext* graphic, nsecs_t timeMs);

	const graphic::mat4& matrix();

	virtual bool dispatchKeyEvent(input::KeyEvent& keyEvent);
	virtual bool dispatchMouseEvent(input::MouseEvent& mouseEvent);

protected:
	virtual void recalculateMatrix();
protected:
	graphic::mat4 mMatrix;
	int32_t mWidth;
	int32_t mHeight;
	bool mDirty;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_CAMERA_H_ */
