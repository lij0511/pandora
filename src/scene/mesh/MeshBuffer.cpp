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
	int float_size = sizeof(float);
	offset_position = 0;
	switch (type) {
	case TYPE_VERTEX2:
		count_position = 2;
		offset_texcoord = -1;
		offset_color = -1;
		item_size = sizeof(Vertex2);
		break;
	case TYPE_VERTEX3:
		count_position = 3;
		offset_texcoord = -1;
		offset_color = -1;
		item_size = sizeof(Vertex3);
		break;
	case TYPE_VERTEX2_TEXTURE:
		count_position = 2;
		offset_texcoord = 2 * float_size;
		offset_color = -1;
		item_size = sizeof(TextureVertex2);
		break;
	case TYPE_VERTEX3_TEXTURE:
		count_position = 3;
		offset_texcoord = 3 * float_size;
		offset_color = -1;
		item_size = sizeof(TextureVertex2);
		break;
	case TYPE_VERTEX2_TEXTURE_COLOR:
		count_position = 2;
		offset_texcoord = 2 * float_size;
		offset_color = 4 * float_size;
		item_size = sizeof(ColorTextureVertex2);
		break;
	case TYPE_VERTEX3_TEXTURE_COLOR:
		count_position = 3;
		offset_texcoord = 3 * float_size;
		offset_color = 5 * float_size;
		item_size = sizeof(ColorTextureVertex3);
		break;
	case TYPE_VERTEX2_COLOR:
		count_position = 2;
		offset_texcoord = -1;
		offset_color = 2 * float_size;
		count_color = 4;
		item_size = sizeof(ColorVertex2);
		break;
	case TYPE_VERTEX3_COLOR:
		count_position = 3;
		offset_texcoord = -1;
		offset_color = 3 * float_size;
		count_color = 4;
		item_size = sizeof(ColorVertex3);
		break;
	case TYPE_VERTEX2_ALPHA:
		count_position = 2;
		offset_texcoord = -1;
		offset_color = 2 * float_size;
		count_color = 1;
		item_size = sizeof(AlphaVertex2);
		break;
	case TYPE_VERTEX3_ALPHA:
		count_position = 3;
		offset_texcoord = -1;
		offset_color = 3 * float_size;
		count_color = 1;
		item_size = sizeof(AlphaVertex3);
		break;
	default:
		LOG_ALWAYS_FATAL("MeshBuffer type error [%d]\n", type);
		break;
	}
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
