/*
 * OBJMeshLoader.cpp
 *
 *  Created on: 2016年5月31日
 *      Author: lijing
 */

#include "scene/mesh/OBJMeshLoader.h"

namespace pola {
namespace scene {

OBJMeshLoader::OBJMeshLoader() {
}

OBJMeshLoader::~OBJMeshLoader() {
}

bool OBJMeshLoader::available(io::InputStream* is) {
	return false;
}

Mesh* OBJMeshLoader::doLoadMesh(io::InputStream* is) {
	return nullptr;
}

} /* namespace scene */
} /* namespace pola */
