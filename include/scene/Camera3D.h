/*
 * Camera3D.h
 *
 *  Created on: 2016年5月25日
 *      Author: lijing
 */

#ifndef CAMERA3D_H_
#define CAMERA3D_H_

#include "scene/Camera.h"

namespace pola {
namespace scene {

/*
 *
 */
class Camera3D: public Camera {
public:
	Camera3D(const graphic::vec3& pos = graphic::vec3(0.0f, 0.0f, 1.0f), const graphic::vec3& lookAt = graphic::vec3(0.0f, 0.0f, 0.0f));
	virtual ~Camera3D();

	virtual void setSize(int32_t width, int32_t height);

	void pitch(float angle);
	void yaw(float angle);
	void roll(float angle);
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

#endif /* CAMERA3D_H_ */
