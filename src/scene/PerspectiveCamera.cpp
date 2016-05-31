/*
 * Camera3D.cpp
 *
 *  Created on: 2016年5月25日
 *      Author: lijing
 */

#include "scene/PerspectiveCamera.h"

namespace pola {
namespace scene {

PerspectiveCamera::PerspectiveCamera(const graphic::vec3& pos, const graphic::vec3& lookAt) :
		m_position(pos), m_target(lookAt), m_upper(0.0f, 1.0f, 0.0f), m_znear(
				0.1f), m_zfar(3000.0f) {
	m_fovy = M_PI / 2.5f;
	m_aspect = 1.0f;
	m_projection.loadPerspectiveLH(m_fovy, m_aspect, m_znear, m_zfar);
	recalculateMatrix();
}

PerspectiveCamera::~PerspectiveCamera() {
}

void PerspectiveCamera::setSize(int32_t width, int32_t height) {
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

void PerspectiveCamera::recalculateMatrix() {
	m_view.loadLookAt(m_position, m_target, m_upper);
	graphic::mat4 m;
	m.loadMultiply(m_projection, m_view);
	m_matrix.load(m);
}

bool PerspectiveCamera::dispatchKeyEvent(input::KeyEvent& keyEvent) {
	bool handled = false;
	if (keyEvent.getAction() == input::KeyEvent::ACTION_DOWN) {
		switch (keyEvent.getKeyCode()) {
			case input::KeyEvent::KEYCODE_W: {
				graphic::vec3 t = m_target - m_position;
				t.normalize();
				m_position += t;
				m_target += t;
				recalculateMatrix();
				handled = true;
				break;
			}
			case input::KeyEvent::KEYCODE_S: {
				graphic::vec3 t = m_target - m_position;
				t.normalize();
				m_position -= t;
				m_target -= t;
				recalculateMatrix();
				handled = true;
				break;
			}
			case input::KeyEvent::KEYCODE_A: {
				graphic::vec3 t = m_target;
				t = t.copyCross(m_upper);
				t.normalize();
				m_position += t;
				m_target += t;
				recalculateMatrix();
				handled = true;
				break;
			}
			case input::KeyEvent::KEYCODE_D: {
				graphic::vec3 t = m_target;
				t = t.copyCross(m_upper);
				t.normalize();
				m_position -= t;
				m_target -= t;
				recalculateMatrix();
				handled = true;
				break;
			}
			default:
				break;
		}
	}
	return handled;
}

} /* namespace scene */
} /* namespace pola */
