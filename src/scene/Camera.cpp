/*
 * Camera.cpp
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#include "scene/Camera.h"

namespace pola {
namespace scene {

Camera::Camera() : m_width(1), m_height(1) {
}

Camera::~Camera() {
}

void Camera::setSize(int32_t width, int32_t height) {
	if (width > 0 && height > 0) {
		m_width = width;
		m_height = height;
	}
}

const graphic::mat4& Camera::matrix() const {
	return m_matrix;
}

} /* namespace scene */
} /* namespace pola */
