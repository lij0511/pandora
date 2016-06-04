/*
 * Camera.cpp
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#include "scene/camera/Camera.h"

namespace pola {
namespace scene {

Camera::Camera() : SceneNode(), mWidth(1), mHeight(1), mCameraDirty(true), mController(nullptr) {
}

Camera::~Camera() {
	if (mController != nullptr) {
		delete mController;
		mController = nullptr;
	}
}

void Camera::setSize(int32_t width, int32_t height) {
	if (width > 0 && height > 0) {
		mWidth = width;
		mHeight = height;
	}
}

void Camera::setCameraController(CameraController* controller) {
	if (mController == controller) {
		return;
	}
	if (mController != nullptr) {
		delete mController;
	}
	mController = controller;
}

void Camera::render(graphic::GraphicContext* graphic, nsecs_t timeMs) {
	bool animating = false;
	if (mController != nullptr) {
		animating = mController->animate(timeMs);
	}
	if (mCameraDirty || animating) {
		if (mCameraDirty) {
			updateMatrix();
			mCameraDirty = false;
		}
		graphic->setMatrix(graphic::GraphicContext::PROJECTION, mController != nullptr ? mProjection * mController->getTransform() * mView : mMatrix);
	}
}

void Camera::updateMatrix() {
	graphic::mat4 m;
	m.compose(mPosition, mRotation, mScale);
	mMatrix.loadInverse(m);
}

void Camera::onPropertyChange() {
	mCameraDirty = true;
}

bool Camera::dispatchKeyEvent(input::KeyEvent& keyEvent) {
	if (mController != nullptr) {
		return mController->dispatchKeyEvent(keyEvent);
	}
	return false;
}

bool Camera::dispatchMouseEvent(input::MouseEvent& mouseEvent) {
	if (mController != nullptr) {
		return mController->dispatchMouseEvent(mouseEvent);
	}
	return false;
}

} /* namespace scene */
} /* namespace pola */
