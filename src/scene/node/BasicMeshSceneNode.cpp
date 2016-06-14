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

void BasicMeshSceneNode::setMaterialTexture(uint32_t i, graphic::Texture* texture) {
	mMaterial.setTexture(i, texture);
}

void BasicMeshSceneNode::render(graphic::GraphicContext* graphic, nsecs_t timeMs) {
	graphic->setMaterial(mMaterial);
	graphic->renderMeshBuffer(*mMesh->getMeshBuffer(0));
}

} /* namespace scene */
} /* namespace pola */
