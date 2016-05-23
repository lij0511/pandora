/*
 * MeshBuffer.cpp
 *
 *  Created on: 2016年5月19日
 *      Author: lijing
 */

#include "scene/mesh/MeshBuffer.h"
#include "log/Log.h"

#include <typeinfo>

using namespace std;

namespace pola {
namespace scene {
using namespace graphic;

MeshBuffer::MeshBuffer(VertexType type) :
		m_type(type), m_buffer(nullptr), m_vertexCount(0) {
	if (type == graphic::TYPE_UNKNOWN) {
		LOG_ALWAYS_FATAL("MeshBuffer type error [%d]\n", type);
	}
	m_vertexInfo = makeVertexInfo(type);
}

MeshBuffer::~MeshBuffer() {
	m_indexBuffer.clear();
	if (m_buffer) {
		free(m_buffer);
	}
}

size_t MeshBuffer::getVertexCount() const {
	return m_vertexCount;
}

void MeshBuffer::pushIndex(uint16_t index) {
	m_indexBuffer.push(index);
}

void MeshBuffer::setIndices(const uint16_t* indices, size_t indexCount) {
	m_indexBuffer.resize(indexCount);
	memcpy(m_indexBuffer.editArray(), indices, sizeof(uint16_t) * indexCount);
}

size_t MeshBuffer::getIndexCount() const {
	return m_indexBuffer.size();
}

const void* MeshBuffer::getVertexBuffer() const {
	return m_buffer;
}

const uint16_t* MeshBuffer::getIndexBuffer() const {
	return m_indexBuffer.array();
}

} /* namespace graphic */
} /* namespace pola */
