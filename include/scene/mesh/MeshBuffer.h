/*
 * MeshBuffer.h
 *
 *  Created on: 2016年5月19日
 *      Author: lijing
 */

#ifndef POLA_MESHBUFFER_H_
#define POLA_MESHBUFFER_H_

#include <stddef.h>
#include <stdint.h>
#include <typeinfo>

#include "graphic/Vertex.h"
#include "utils/Vector.h"

namespace pola {
namespace scene {

class MeshBuffer {

public:
	MeshBuffer(graphic::VertexType type);
	virtual ~MeshBuffer();

	void* alloc(size_t vertexCount) {
		if (vertexCount > 0 && vertexCount != m_vertexCount) {
			if (m_vertexCount < vertexCount) {
				if (m_buffer) {
					free(m_buffer);
				}
				m_buffer = malloc(m_vertexInfo.item_size * vertexCount);
			}
			m_vertexCount = vertexCount;
		}
		return m_buffer;
	};

	void pushIndex(uint16_t index);
	void setIndices(const uint16_t* indices, size_t indexCount);

	size_t getIndexCount() const;
	size_t getVertexCount() const;

	const void* getVertexBuffer() const;
	const uint16_t* getIndexBuffer() const;

public:
	graphic::VertexType m_type;
	graphic::VertexInfo m_vertexInfo;
private:
	void* m_buffer;
	pola::utils::Vector<uint16_t> m_indexBuffer;
	size_t m_vertexCount;

};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_MESHBUFFER_H_ */
