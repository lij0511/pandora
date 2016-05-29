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

SceneNode::SceneNode(const graphic::vec3& position) : m_position(position) {
}

SceneNode::~SceneNode() {
}

void SceneNode::render(graphic::GraphicContext* graphic, nsecs_t timeMs) {
}

} /* namespace scene */
} /* namespace pola */
