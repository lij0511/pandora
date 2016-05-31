/*
 * BasicMesh.cpp
 *
 *  Created on: 2016年5月31日
 *      Author: lijing
 */

#include "scene/mesh/BasicMesh.h"

namespace pola {
namespace scene {

BasicMesh::BasicMesh(graphic::VertexType vertexType) : mMeshBuffer(vertexType) {
}

BasicMesh::~BasicMesh() {
}

size_t BasicMesh::getMeshBufferCount() const {
	return 1;
}

graphic::MeshBuffer* BasicMesh::getMeshBuffer(uint16_t index) {
	return &mMeshBuffer;
}

} /* namespace scene */
} /* namespace pola */
