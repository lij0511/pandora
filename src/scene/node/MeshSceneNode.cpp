/*
 * MeshSceneNode.cpp
 *
 *  Created on: 2016年5月23日
 *      Author: lijing
 */

#include "scene/node/MeshSceneNode.h"

namespace pola {
namespace scene {

MeshSceneNode::MeshSceneNode() {
}

MeshSceneNode::~MeshSceneNode() {
}

uint32_t MeshSceneNode::getMaterialCount() const {
	return 0;
}

void MeshSceneNode::render(graphic::GraphicContext* graphic) {
}

} /* namespace scene */
} /* namespace pola */
