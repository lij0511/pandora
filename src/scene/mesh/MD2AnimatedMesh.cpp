/*
 * MD2AnimatedMesh.cpp
 *
 *  Created on: 2016年5月24日
 *      Author: lijing
 */

#include "scene/mesh/MD2AnimatedMesh.h"

namespace pola {
namespace scene {

MD2AnimatedMesh::MD2AnimatedMesh() : meshBuffer(graphic::TYPE_VERTEX3_TEXTURE_NORMAL), frameCount(0) {
}

MD2AnimatedMesh::~MD2AnimatedMesh() {
}

size_t MD2AnimatedMesh::getFrameCount() const {
	return frameCount;
}

size_t MD2AnimatedMesh::getMeshBufferCount() const {
	return 1;
}

MeshBuffer* MD2AnimatedMesh::getMeshBuffer(uint16_t index) {
	if (index == 0 && getFrameCount() > 0) {
		// TODO
		static uint16_t frame = 0;
		if (frame >= getFrameCount()) {
			frame = 0;
		}
		graphic::NormalTextureVertex3* vertex = (graphic::NormalTextureVertex3*) meshBuffer.getVertexBuffer();
		// interpolate both frames
		const size_t count = frameList[frame].size();
		for (uint32_t i = 0; i < count; ++i) {
			float x = frameList[frame][i].pos[0] * frameTransforms[frame].scale[0] + frameTransforms[frame].translate[0];
			float y = frameList[frame][i].pos[1] * frameTransforms[frame].scale[1] + frameTransforms[frame].translate[1];
			float z = frameList[frame][i].pos[2] * frameTransforms[frame].scale[2] + frameTransforms[frame].translate[2];
			vertex->x = x;
			vertex->y = y;
			vertex->z = z;
			vertex ++;
		}
		frame ++;
		return &meshBuffer;
	} else {
		return nullptr;
	}
}

} /* namespace scene */
} /* namespace pola */
