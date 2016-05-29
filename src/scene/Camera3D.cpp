/*
 * Camera3D.cpp
 *
 *  Created on: 2016年5月25日
 *      Author: lijing
 */

#include "scene/Camera3D.h"

namespace pola {
namespace scene {

Camera3D::Camera3D(const graphic::vec3& pos, const graphic::vec3& lookAt) :
		m_position(pos), m_target(lookAt), m_upper(0.0f, 1.0f, 0.0f), m_znear(
				0.1f), m_zfar(3000.0f) {
	m_fovy = M_PI / 2.5f;
	m_aspect = 1.0f;
	m_projection.loadPerspective(m_fovy, m_aspect, m_znear, m_zfar);
	recalculateMatrix();
}

Camera3D::~Camera3D() {
}

void Camera3D::setSize(int32_t width, int32_t height) {
	Camera::setSize(width, height);
	if (width > 0 && height > 0) {
		m_aspect = (float) width / height;
		m_projection.loadPerspective(m_fovy, m_aspect, m_znear, m_zfar);
//		const double DEG2RAD = 3.1415926 / 180;
//		double tangent = tan(m_fovy / 2 * DEG2RAD);
//		double h = m_znear * tangent;
//		double w = height * m_aspect;
//		m_projection.loadFrustum(- w, w, -h, h, m_znear, m_zfar);
//		m_projection.loadFrustum(-width, width, -height, height, m_znear, m_zfar);
		recalculateMatrix();
	}
}

void Camera3D::pitch(float angle) {
	if (angle != 0.0f) {
		m_orientation.rotate(angle, 1, 0, 0);
		recalculateMatrix();
	}
}

void Camera3D::yaw(float angle) {
	if (angle != 0.0f) {
		m_orientation.rotate(angle, 0, 1, 0);
		recalculateMatrix();
	}
}

void Camera3D::roll(float angle) {
	if (angle != 0.0f) {
		m_orientation.rotate(angle, 0, 0, 1);
		recalculateMatrix();
	}
}

void Camera3D::recalculateMatrix() {
	graphic::mat4 m;
	m.loadLookAt(m_position, m_target, m_upper);
	graphic::mat4 m1 = m_orientation;
	m1.translate(0, 0, -10);
	m_view.loadMultiply(m_orientation, m);
	m_matrix.loadMultiply(m_projection, m_view);
}

} /* namespace scene */
} /* namespace pola */
