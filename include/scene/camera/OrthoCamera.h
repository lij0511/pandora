/*
 * OrthoCamera.h
 *
 *  Created on: 2016年7月14日
 *      Author: lijing
 */

#ifndef POLA_ORTHOCAMERA_H_
#define POLA_ORTHOCAMERA_H_

#include "scene/camera/Camera.h"

namespace pola {
namespace scene {

class OrthoCamera: public Camera {
public:
	OrthoCamera(float near = 1.f, float far = 3000.f);
	virtual ~OrthoCamera();

	virtual void setSize(int32_t width, int32_t height);

private:
	float mNear;
	float mFar;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_ORTHOCAMERA_H_ */
