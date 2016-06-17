/*
 * MeshSceneNode.cpp
 *
 *  Created on: 2016年5月23日
 *      Author: lijing
 */

#include "scene/node/MeshSceneNode.h"

namespace pola {
namespace scene {

MeshSceneNode::MeshSceneNode() : mMaterial(nullptr) {
}

MeshSceneNode::~MeshSceneNode() {
}

uint32_t MeshSceneNode::getMaterialCount() const {
	return 0;
}

} /* namespace scene */
} /* namespace pola */
