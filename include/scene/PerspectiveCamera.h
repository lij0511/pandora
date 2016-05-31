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

	virtual bool dispatchKeyEvent(input::KeyEvent& keyEvent);
private:
	void recalculateMatrix();
private:
	graphic::vec3 m_position;
	graphic::vec3 m_target;
	graphic::vec3 m_upper;

	float m_fovy;	// Field of view, in radians.
	float m_aspect;	// Aspect ratio.
	float m_znear;	// value of the near view-plane.
	float m_zfar;	// Z-value of the far view-plane.

	graphic::mat4 m_projection;
	graphic::mat4 m_view;
};

} /* namespace scene */
} /* namespace pola */

#endif /* PERSPECTIVECAMERA_H_ */
