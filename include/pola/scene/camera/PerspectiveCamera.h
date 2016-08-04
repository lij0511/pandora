/*
 * Camera3D.h
 *
 *  Created on: 2016年5月25日
 *      Author: lijing
 */

#ifndef PERSPECTIVECAMERA_H_
#define PERSPECTIVECAMERA_H_

#include "pola/scene/camera/Camera.h"

namespace pola {
namespace scene {

/*
 *
 */
class PerspectiveCamera: public Camera {
public:
	PerspectiveCamera(float fovy = M_PI / 2.5f, float aspect = 1.f, float near = 1.f, float far = 1000.f);
	virtual ~PerspectiveCamera();

	virtual void setSize(int32_t width, int32_t height);

protected:
	float mFovy;	// Field of view, in radians.
	float mAspect;	// Aspect ratio.
	float mZnear;	// value of the near view-plane.
	float mZfar;	// Z-value of the far view-plane.

};

} /* namespace scene */
} /* namespace pola */

#endif /* PERSPECTIVECAMERA_H_ */
