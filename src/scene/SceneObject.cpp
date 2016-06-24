/*
 * SceneObject.cpp
 *
 *  Created on: 2016年6月24日
 *      Author: lijing
 */

#include "scene/SceneObject.h"

namespace pola {
namespace scene {

SceneObject::SceneObject() : mMatrixDirty(true) {
	mScale = {1, 1, 1};
	mParent = nullptr;
}

SceneObject::~SceneObject() {
	if (mChildren.size() > 0) {
		for (unsigned i = 0; i < mChildren.size(); i ++) {
			mChildren[i]->mParent = nullptr;
			mChildren[i]->deref();
		}
		mChildren.clear();
	}
}

void SceneObject::setPosition(const graphic::vec3& position) {
	mPosition = position;
	onPropertyChange();
}

const graphic::vec3& SceneObject::getPosition() const {
	return mPosition;
}

void SceneObject::setRotation(const graphic::Euler& rotation) {
	mRotation = rotation;
	onPropertyChange();
}

const graphic::Euler& SceneObject::getRotation() const {
	return mRotation;
}

void SceneObject::setScale(const graphic::vec3& scale) {
	mScale = scale;
	onPropertyChange();
}

const graphic::vec3& SceneObject::getScale() const {
	return mScale;
}

void SceneObject::updateTransform() {
	if (mMatrixDirty) {
		graphic::quat4 quat;
		mRotation.getQuaternion(quat);
		mMatrix.compose(mPosition, quat, mScale);
		if (mParent != nullptr) {
			mWorldMatrix.loadMultiply(mParent->getWorldTransform(), mMatrix);
		} else {
			mWorldMatrix.load(mMatrix);
		}
		mMatrixDirty = false;
	}
}

const graphic::mat4 SceneObject::getTransform() {
	updateTransform();
	return mMatrix;
}

const graphic::mat4 SceneObject::getWorldTransform() {
	updateTransform();
	return mWorldMatrix;
}

void SceneObject::addChild(SceneObject* child) {
	if (child->mParent != nullptr) {
		return;
	}
	for (unsigned i = 0; i < mChildren.size(); i ++) {
		if (mChildren[i] == child) {
			return;
		}
	}
	child->ref();
	child->mParent = this;
	mChildren.push(child);
}

void SceneObject::removeChild(SceneObject* child) {
	for (unsigned i = 0; i < mChildren.size(); i ++) {
		if (mChildren[i] == child) {
			mChildren.removeAt(i);
			child->deref();
			child->mParent = nullptr;
			return;
		}
	}
}

void SceneObject::onPropertyChange() {
	mMatrixDirty = true;
	for (unsigned i = 0; i < mChildren.size(); i ++) {
		mChildren[i]->onPropertyChange();
	}
}

} /* namespace scene */
} /* namespace pola */
