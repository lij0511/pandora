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

Mesh* BasicMeshSceneNode::mesh() {
	return mMesh;
}

void BasicMeshSceneNode::render(graphic::GraphicContext* graphic, nsecs_t timeMs) {
	graphic->renderGeometry(mMesh->geometry(), mMaterial.get());
}

} /* namespace scene */
} /* namespace pola */
