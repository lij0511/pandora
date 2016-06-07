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
	mParent = NULL;
}

SceneNode::~SceneNode() {
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

const graphic::mat4 SceneNode::getTransform() {
	if (mMatrixDirty) {
		graphic::quat4 quat;
		mRotation.getQuaternion(quat);
		mMatrix.compose(mPosition, quat, mScale);
		mMatrixDirty = false;
	}
	return mMatrix;
}

void SceneNode::render(graphic::GraphicContext* graphic, nsecs_t timeMs) {
}

void SceneNode::onPropertyChange() {
	mMatrixDirty = true;
}

} /* namespace scene */
} /* namespace pola */
