/*
 * Mesh.cpp
 *
 *  Created on: 2016年8月19日
 *      Author: lijing
 */

#include "pola/scene/mesh/Mesh.h"

namespace pola {
namespace scene {

Mesh::Mesh() : mGeometry(new graphic::Geometry3D), mSkeleton(nullptr) {
	mGeometry->ref();
}

Mesh::~Mesh() {
	mGeometry->deref();
}

graphic::Geometry* Mesh::geometry() {
	return mGeometry;
}

} /* namespace scene */
} /* namespace pola */
