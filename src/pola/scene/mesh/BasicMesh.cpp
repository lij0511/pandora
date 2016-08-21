/*
 * BasicMesh.cpp
 *
 *  Created on: 2016年5月31日
 *      Author: lijing
 */

#include "pola/scene/mesh/BasicMesh.h"

namespace pola {
namespace scene {

BasicMesh::BasicMesh() : mGeometry(new graphic::Geometry3D) {
	mGeometry->ref();
}

BasicMesh::BasicMesh(graphic::Geometry* geometry) : mGeometry(geometry) {
	mGeometry->ref();
}

BasicMesh::~BasicMesh() {
	mGeometry->deref();
}

graphic::Geometry* BasicMesh::geometry() {
	return mGeometry;
}

} /* namespace scene */
} /* namespace pola */
