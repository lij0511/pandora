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

SceneNode::SceneNode() : mEnable(true) {
}

SceneNode::~SceneNode() {
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

} /* namespace scene */
} /* namespace pola */
