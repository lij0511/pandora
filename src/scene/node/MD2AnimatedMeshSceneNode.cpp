/*
 * MD2AnimatedMeshSceneNode.cpp
 *
 *  Created on: 2016年5月29日
 *      Author: lijing
 */

#include "scene/node/MD2AnimatedMeshSceneNode.h"

namespace pola {
namespace scene {

MD2AnimatedMeshSceneNode::MD2AnimatedMeshSceneNode(MD2AnimatedMesh* mesh) : mMesh(mesh) {
	setFrameLoop(0, mMesh->getFrameCount());
}

MD2AnimatedMeshSceneNode::~MD2AnimatedMeshSceneNode() {
}

void MD2AnimatedMeshSceneNode::setAnimationType(MD2_ANIMATION_TYPE type) {
	if (type < 0 || type >= MD2_AT_COUNT) {
		return;
	}
	int32_t begin, end, fps;
	mMesh->getFrameLoop(type, begin, end, fps);
	setFrameLoop(begin, end);
	setFramesPerMs((float) fps / 1000.0f);
}

void MD2AnimatedMeshSceneNode::render(graphic::GraphicContext* graphic, nsecs_t timeMs) {
	AnimatedMeshSceneNode::render(graphic, timeMs);
	mMesh->updateMeshBuffer(getCurrentFrame(), getStartFrameLoop(), getEndFrameLoop());
	graphic->renderMeshBuffer(*mMesh->getMeshBuffer(0), mMaterial.get());
}

} /* namespace scene */
} /* namespace pola */
