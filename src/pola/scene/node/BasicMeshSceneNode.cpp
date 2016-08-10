/*
 * BasicMeshSceneNode.cpp
 *
 *  Created on: 2016年6月13日
 *      Author: lijing
 */

#include "pola/scene/node/BasicMeshSceneNode.h"

namespace pola {
namespace scene {

BasicMeshSceneNode::BasicMeshSceneNode(BasicMesh* mesh) : mMesh(mesh) {
}

BasicMeshSceneNode::~BasicMeshSceneNode() {
}

Mesh* BasicMeshSceneNode::mesh(uint32_t index) {
	return mMesh;
}

} /* namespace scene */
} /* namespace pola */
