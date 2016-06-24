/*
 * CameraController.h
 *
 *  Created on: 2016年6月3日
 *      Author: lijing
 */

#ifndef CAMERACONTROLLER_H_
#define CAMERACONTROLLER_H_

#include "input/KeyEvent.h"
#include "input/MouseEvent.h"
#include "utils/Times.h"
#include "graphic/math/Matrix4.h"
#include "graphic/math/Euler.h"
#include "graphic/math/Vector.h"
#include "scene/SceneObject.h"

namespace pola {
namespace scene {

class Camera;

/*
 *
 */
class CameraController : public SceneObject  {
public:
	CameraController(Camera* camera);
	virtual ~CameraController();

	virtual bool animate(nsecs_t timeMs);
	virtual bool dispatchKeyEvent(input::KeyEvent& keyEvent);
	virtual bool dispatchMouseEvent(input::MouseEvent& mouseEvent);

protected:
	Camera* mCamera;

};

} /* namespace scene */
} /* namespace pola */

#endif /* CAMERACONTROLLER_H_ */
