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

SceneNode::SceneNode(const graphic::vec3& position) : mPosition(position) {
}

SceneNode::~SceneNode() {
}

void SceneNode::setPosition(const graphic::vec3& position) {
	mPosition = position;
}

graphic::vec3 SceneNode::getPosition() const {
	return mPosition;
}

const graphic::mat4 SceneNode::getTransform() {
	graphic::mat4 m;
	m.loadTranslate(mPosition.x, mPosition.y, mPosition.z);
	return m;
}

void SceneNode::render(graphic::GraphicContext* graphic, nsecs_t timeMs) {
}

} /* namespace scene */
} /* namespace pola */
