/*
 * MD2AnimatedMeshSceneNode.cpp
 *
 *  Created on: 2016年5月29日
 *      Author: lijing
 */

#include "pola/scene/node/MD2AnimatedMeshSceneNode.h"

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

Mesh* MD2AnimatedMeshSceneNode::mesh() {
	return mMesh;
}

void MD2AnimatedMeshSceneNode::update(p_nsecs_t timeMs) {
	AnimatedMeshSceneNode::update(timeMs);
	mMesh->updateMeshBuffer(getCurrentFrame(), getStartFrameLoop(), getEndFrameLoop());
}

} /* namespace scene */
} /* namespace pola */
