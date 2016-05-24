/*
 * Camera.h
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#ifndef POLA_CAMERA_H_
#define POLA_CAMERA_H_

#include "graphic/Matrix4.h"
#include "graphic/Vector.h"

namespace pola {
namespace scene {

class Scene;

class Camera {
public:
	Camera(Scene* scene, const graphic::vec3& pos = graphic::vec3(0.0f, 0.0f, 1.0f), const graphic::vec3& lookAt = graphic::vec3(0.0f, 0.0f, 0.0f));
	virtual ~Camera();

	const graphic::mat4& vpmatrix() const;
	const graphic::mat4& projection() const;
	const graphic::mat4& view() const;

protected:
	void recalculateVPMatrix();
protected:
	graphic::vec3 m_position;
	graphic::vec3 m_target;
	graphic::vec3 m_upper;

	float m_fovy;	// Field of view, in radians.
	float m_aspect;	// Aspect ratio.
	float m_znear;	// value of the near view-plane.
	float m_zfar;	// Z-value of the far view-plane.

	graphic::mat4 m_projection;
	graphic::mat4 m_view;
	graphic::mat4 m_VPMatrix;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_CAMERA_H_ */
