/*
 * SkinnedMesh.cpp
 *
 *  Created on: 2016年8月11日
 *      Author: lijing
 */

#include "pola/scene/mesh/SkinnedMesh.h"

namespace pola {
namespace scene {

SkinnedMesh::SkinnedMesh() : mLocalGeometry(new graphic::Geometry3D), mGeometry(new graphic::Geometry3D) {
}

SkinnedMesh::~SkinnedMesh() {
}

graphic::Geometry* SkinnedMesh::geometry() {
	return mGeometry;
}

graphic::Geometry3D* SkinnedMesh::localGeometry() {
	return mLocalGeometry;
}

} /* namespace scene */
} /* namespace pola */
