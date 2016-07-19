/*
 * Camera.cpp
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#include "pola/scene/camera/Camera.h"

namespace pola {
namespace scene {

Camera::Camera() : SceneObject(), mWidth(1), mHeight(1), mCameraDirty(true), mController(nullptr) {
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

bool Camera::update(graphic::GraphicContext* graphic, p_nsecs_t timeMs) {
	bool animating = false;
	if (mController != nullptr) {
		animating = mController->animate(timeMs);
	}
	if (mCameraDirty || animating) {
		mMatrixDirty = true;
		mCameraDirty = false;
		graphic->setMatrix(graphic::GraphicContext::PROJECTION, mProjection);
		graphic::mat4 viewInverse;
		viewInverse.loadInverse(getWorldTransform());
//		viewInverse.load(view);
		graphic->setMatrix(graphic::GraphicContext::VIEW, viewInverse);
		mFrustum.setFromMatrix(mProjection * viewInverse);
		return true;
	}
	return false;
}

void Camera::updateTransform() {
	if (mMatrixDirty) {
		graphic::mat4 m;
		graphic::quat4 quat;
		mRotation.getQuaternion(quat);
		m.compose(mPosition, quat, mScale);
		if (mController != nullptr) {
			mMatrix.loadMultiply(mController->getWorldTransform(), m);
		} else {
			mMatrix.load(m);
		}
		if (mParent != nullptr) {
			mWorldMatrix.loadMultiply(mParent->getWorldTransform(), mMatrix);
		} else {
			mWorldMatrix.load(mMatrix);
		}
		mMatrixDirty = false;
	}
}

const graphic::Frustum& Camera::frustum() const {
	return mFrustum;
}

void Camera::onPropertyChange() {
	SceneObject::onPropertyChange();
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
