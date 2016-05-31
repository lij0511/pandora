/*
 * MeshLoader.cpp
 *
 *  Created on: 2016年5月24日
 *      Author: lijing
 */

#include "scene/mesh/MeshLoader.h"
#include "scene/mesh/MD2MeshLoader.h"
#include "io/FileInputStream.h"

namespace pola {
namespace scene {

Mesh* MeshLoader::loadMesh(const char* meshFile) {
	io::FileInputStream is(meshFile);
	//utils::String s(meshFile);
	return loadMesh(&is);
}
Mesh* MeshLoader::loadMesh(io::InputStream* is, const char* type) {
	// FIXME
	MD2MeshLoader loader;
	return loader.doLoadMesh(is);
}

}
}

