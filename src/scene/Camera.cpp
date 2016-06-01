/*
 * Camera.cpp
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#include "scene/Camera.h"

namespace pola {
namespace scene {

Camera::Camera(const graphic::vec3& pos) : SceneNode(pos), mWidth(1), mHeight(1), mDirty(true) {
}

Camera::~Camera() {
}

void Camera::setSize(int32_t width, int32_t height) {
	if (width > 0 && height > 0) {
		mWidth = width;
		mHeight = height;
	}
}

void Camera::render(graphic::GraphicContext* graphic, nsecs_t timeMs) {
	if (mDirty) {
		recalculateMatrix();
		graphic->setMatrix(graphic::GraphicContext::PROJECTION, mMatrix);
		mDirty = false;
	}
}

const graphic::mat4& Camera::matrix() {
	if (mDirty) {
		recalculateMatrix();
	}
	return mMatrix;
}

void Camera::recalculateMatrix() {
}

bool Camera::dispatchKeyEvent(input::KeyEvent& keyEvent) {
	return false;
}

bool Camera::dispatchMouseEvent(input::MouseEvent& mouseEvent) {
	return false;
}

} /* namespace scene */
} /* namespace pola */
