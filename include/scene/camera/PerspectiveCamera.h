/*
 * Camera3D.h
 *
 *  Created on: 2016年5月25日
 *      Author: lijing
 */

#ifndef PERSPECTIVECAMERA_H_
#define PERSPECTIVECAMERA_H_

#include "scene/Camera.h"

namespace pola {
namespace scene {

/*
 *
 */
class PerspectiveCamera: public Camera {
public:
	PerspectiveCamera(const graphic::vec3& pos = graphic::vec3(0.0f, 0.0f, 1.0f), const graphic::vec3& lookAt = graphic::vec3(0.0f, 0.0f, 0.0f));
	virtual ~PerspectiveCamera();

	virtual void setSize(int32_t width, int32_t height);

	void setTarget(const graphic::vec3& target);
	void setUpper(const graphic::vec3& upper);

protected:
	virtual void recalculateMatrix();
protected:
	graphic::vec3 mTarget;
	graphic::vec3 mUpper;

	float mFovy;	// Field of view, in radians.
	float mAspect;	// Aspect ratio.
	float mZnear;	// value of the near view-plane.
	float mZfar;	// Z-value of the far view-plane.

	graphic::mat4 mProjection;
	graphic::mat4 mView;

};

} /* namespace scene */
} /* namespace pola */

#endif /* PERSPECTIVECAMERA_H_ */
