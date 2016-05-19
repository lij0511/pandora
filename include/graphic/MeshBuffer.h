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

namespace pola {
namespace graphic {

template <class TYPE>
class MeshBuffer {
public:
	MeshBuffer();
	virtual ~MeshBuffer();

	virtual size_t getVertexCount() const;
	virtual size_t getIndexCount() const;

	const TYPE* getVertexBuffer() const;
	const uint16_t* getIndexBuffer() const;

private:
	TYPE* mVertexBuffer;
	uint16_t* mIndexBuffer;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_MESHBUFFER_H_ */
