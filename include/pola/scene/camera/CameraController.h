/*
 * CameraController.h
 *
 *  Created on: 2016年6月3日
 *      Author: lijing
 */

#ifndef CAMERACONTROLLER_H_
#define CAMERACONTROLLER_H_

#include "pola/input/KeyEvent.h"
#include "pola/input/MouseEvent.h"
#include "pola/utils/Times.h"
#include "pola/graphic/math/Math.h"
#include "pola/scene/node/SceneNode.h"

namespace pola {
namespace scene {

class Camera;

/*
 *
 */
class CameraController : public SceneNode  {
public:
	CameraController(Camera* camera);
	virtual ~CameraController();

	virtual bool animate(p_nsecs_t timeMs);
	virtual bool dispatchKeyEvent(input::KeyEvent& keyEvent);
	virtual bool dispatchMouseEvent(input::MouseEvent& mouseEvent);

protected:
	Camera* mCamera;

};

} /* namespace scene */
} /* namespace pola */

#endif /* CAMERACONTROLLER_H_ */
