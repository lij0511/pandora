/*
 * SceneNode.cpp
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#include "scene/node/SceneNode.h"

namespace pola {
namespace scene {

SceneNode::SceneNode(const graphic::vec3& position) : m_translation(position) {
}

SceneNode::~SceneNode() {
}

} /* namespace scene */
} /* namespace pola */
