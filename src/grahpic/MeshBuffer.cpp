/*
 * MeshBuffer.cpp
 *
 *  Created on: 2016年5月19日
 *      Author: lijing
 */

#include "graphic/MeshBuffer.h"

namespace pola {
namespace graphic {

template <class TYPE>
MeshBuffer<TYPE>::MeshBuffer() : mIndexBuffer(nullptr) {
}

template <class TYPE>
MeshBuffer<TYPE>::~MeshBuffer() {
	mIndexBuffer.clear();
	mVertexBuffer.clear();
}

template <class TYPE>
size_t MeshBuffer<TYPE>::getVertexCount() const {
	return mVertexBuffer.size();
}

template <class TYPE>
size_t MeshBuffer<TYPE>::getIndexCount() const {
	return mIndexBuffer.size();
}

template <class TYPE>
const TYPE* MeshBuffer<TYPE>::getVertexBuffer() const {
	return mVertexBuffer.array();
}

template <class TYPE>
const uint16_t* MeshBuffer<TYPE>::getIndexBuffer() const {
	return mIndexBuffer.array();
}

} /* namespace graphic */
} /* namespace pola */
