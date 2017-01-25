/*
 * SceneNode.cpp
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#include "pola/scene/node/SceneNode.h"
#include "pola/graphic/GraphicContext.h"

namespace pola {
namespace scene {


SceneNode::SceneNode() : mMatrixDirty(true), mEnable(true) {
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

void SceneNode::setMaterial(uint16_t index, graphic::Material* material) {
}

void SceneNode::update(p_nsecs_t timeMs) {
}

void SceneNode::setEnable(bool enable) {
	mEnable = enable;
}
bool SceneNode::isEnable() const {
	return mEnable;
}

void SceneNode::render(graphic::GraphicContext* graphic, p_nsecs_t timeMs) {
}
void SceneNode::render(graphic::GraphicContext* graphic, graphic::Material* m, p_nsecs_t timeMs) {
}

void SceneNode::setPosition(const graphic::vec3& position) {
	Object3D::setPosition(position);
	onPropertyChange();
}

void SceneNode::setRotation(const graphic::Euler& rotation) {
	Object3D::setRotation(rotation);
	onPropertyChange();
}

void SceneNode::setScale(const graphic::vec3& scale) {
	Object3D::setScale(scale);
	onPropertyChange();
}

const graphic::mat4 SceneNode::getTransform() {
	updateTransform();
	return mMatrix;
}

const graphic::mat4 SceneNode::getWorldTransform() {
	updateTransform();
	return mWorldMatrix;
}

bool SceneNode::updateTransform() {
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
		return true;
	}
	return false;
}

void SceneNode::addChild(SceneNode* child) {
	if (child == this) {
		return;
	}
	if (child->mParent != nullptr && child->mParent != this) {
		child->mParent->removeChild(child);
	}
	for (unsigned i = 0; i < mChildren.size(); i ++) {
		if (mChildren[i] == child) {
			return;
		}
	}
	child->ref();
	child->mParent = this;
	mChildren.push_back(child);
}

void SceneNode::removeChild(SceneNode* child) {
	if (child->mParent != this) {
		return;
	}
	for (std::vector<SceneNode*>::iterator iter = mChildren.begin(); iter != mChildren.end(); iter ++) {
		if (*iter == child) {
			mChildren.erase(iter);
			child->deref();
			child->mParent = nullptr;
			return;
		}
	}
}

size_t SceneNode::getChildCount() const {
	return mChildren.size();
}

SceneNode* SceneNode::getChild(unsigned index) {
	return mChildren[index];
}

void SceneNode::translateX(float dx) {
	translateOnAxis({1.f, 0.f, 0.f}, dx);
}
void SceneNode::translateY(float dy) {
	translateOnAxis({0.f, 1.f, 0.f}, dy);
}
void SceneNode::translateZ(float dz) {
	translateOnAxis({0.f, 0.f, 1.f}, dz);
}
void SceneNode::translateOnAxis(const graphic::vec3& axis, float d) {
	graphic::vec3 v = axis;
	graphic::quat4 quat;
	mRotation.getQuaternion(quat);
	v.applyQuaternion(quat.x, quat.y, quat.z, quat.w);
	mPosition += (v * d);
	onPropertyChange();
}

bool SceneNode::viewable(const graphic::Frustum& frustum) {
	return false;
}

void SceneNode::onPropertyChange() {
	mMatrixDirty = true;
	for (unsigned i = 0; i < mChildren.size(); i ++) {
		mChildren[i]->onPropertyChange();
	}
}

void SceneNode::requestPropertyChange() {
	onPropertyChange();
}

} /* namespace scene */
} /* namespace pola */
