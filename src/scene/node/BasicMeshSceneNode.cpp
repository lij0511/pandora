/*
 * BasicMeshSceneNode.cpp
 *
 *  Created on: 2016年6月13日
 *      Author: lijing
 */

#include "scene/node/BasicMeshSceneNode.h"

namespace pola {
namespace scene {

BasicMeshSceneNode::BasicMeshSceneNode(BasicMesh* mesh) : mMesh(mesh) {
}

BasicMeshSceneNode::~BasicMeshSceneNode() {
}

void BasicMeshSceneNode::render(graphic::GraphicContext* graphic, nsecs_t timeMs) {
	graphic->renderMeshBuffer(*mMesh->getMeshBuffer(0));

}

} /* namespace scene */
} /* namespace pola */
