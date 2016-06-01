/*
 * Camera2D.cpp
 *
 *  Created on: 2016年5月25日
 *      Author: lijing
 */

#include "scene/camera/Camera2D.h"

namespace pola {
namespace scene {

Camera2D::Camera2D() {
}

Camera2D::~Camera2D() {
}

void Camera2D::setSize(int32_t width, int32_t height) {
	Camera::setSize(width, height);
	if (width > 0 && height > 0) {
		recalculateMatrix();
	}
}

void Camera2D::recalculateMatrix() {
	mMatrix.loadOrtho(0, mWidth, 0, mHeight, -1, 1);
}

} /* namespace scene */
} /* namespace pola */
