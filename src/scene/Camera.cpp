/*
 * Camera.cpp
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#include "scene/Camera.h"
#include "scene/Scene.h"

namespace pola {
namespace scene {

Camera::Camera(Scene* scene, const graphic::vec3& pos, const graphic::vec3& lookAt) : m_position(pos),
		m_target(lookAt), m_upper (0.0f, 1.0f, 0.0f),
		m_znear(0.0f), m_zfar(3000.0f) {
	m_fovy = M_PI / 2.5f;
	m_aspect = (float) scene->getWidth() / (float) scene->getHeight();
	recalculateVPMatrix();
}

Camera::~Camera() {
}

const graphic::mat4& Camera::vpmatrix() const {
	return m_VPMatrix;
}

const graphic::mat4& Camera::projection() const {
	return m_projection;
}

const graphic::mat4& Camera::view() const {
	return m_view;
}

void Camera::recalculateVPMatrix() {
	m_projection.loadPerspective(m_fovy, m_aspect, m_znear, m_zfar);
	m_view.loadLookAt(m_position, m_target, m_upper);
	m_VPMatrix.loadMultiply(m_projection, m_view);
//	m_projection.loadOrtho(0, 500, 0, 500, -100, 100);
}

} /* namespace scene */
} /* namespace pola */
