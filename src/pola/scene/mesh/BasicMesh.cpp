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
}

BasicMesh::BasicMesh(graphic::Geometry* geometry) : mGeometry(geometry) {
}

BasicMesh::~BasicMesh() {
	delete mGeometry;
}

graphic::Geometry* BasicMesh::geometry() {
	return mGeometry;
}

} /* namespace scene */
} /* namespace pola */
