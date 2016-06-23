/*
 * SceneNode.cpp
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#include "scene/node/SceneNode.h"
#include "graphic/GraphicContext.h"

namespace pola {
namespace scene {

SceneNode::SceneNode() : mMatrixDirty(true) {
	mScale = {1, 1, 1};
	mParent = nullptr;
}

SceneNode::~SceneNode() {
	if (mChildren.size() > 0) {
		for (unsigned i = 0; i < mChildren.size(); i ++) {
			mChildren[i]->mParent = nullptr;
			mChildren[i]->deref();
		}
		mChildren.clear();
	}
}

void SceneNode::setPosition(const graphic::vec3& position) {
	mPosition = position;
	onPropertyChange();
}

const graphic::vec3& SceneNode::getPosition() const {
	return mPosition;
}

void SceneNode::setRotation(const graphic::Euler& rotation) {
	mRotation = rotation;
	onPropertyChange();
}

const graphic::Euler& SceneNode::getRotation() const {
	return mRotation;
}

void SceneNode::setScale(const graphic::vec3& scale) {
	mScale = scale;
	onPropertyChange();
}

const graphic::vec3& SceneNode::getScale() const {
	return mScale;
}

void SceneNode::updateTransform() {
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

const graphic::mat4 SceneNode::getTransform() {
	updateTransform();
	return mMatrix;
}

const graphic::mat4 SceneNode::getWorldTransform() {
	updateTransform();
	return mWorldMatrix;
}

void SceneNode::addChild(SceneNode* child) {
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

void SceneNode::removeChild(SceneNode* child) {
	for (unsigned i = 0; i < mChildren.size(); i ++) {
		if (mChildren[i] == child) {
			mChildren.removeAt(i);
			child->deref();
			child->mParent = nullptr;
			return;
		}
	}
}

void SceneNode::dispatchRender(graphic::GraphicContext* graphic, nsecs_t timeMs) {
	render(graphic, timeMs);
	for (unsigned i = 0; i < mChildren.size(); i ++) {
		mChildren[i]->dispatchRender(graphic, timeMs);
	}
}

void SceneNode::render(graphic::GraphicContext* graphic, nsecs_t timeMs) {
}

void SceneNode::onPropertyChange() {
	mMatrixDirty = true;
	for (unsigned i = 0; i < mChildren.size(); i ++) {
		mChildren[i]->onPropertyChange();
	}
}

} /* namespace scene */
} /* namespace pola */
