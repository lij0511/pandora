/*
 * MeshLoader.cpp
 *
 *  Created on: 2016年5月24日
 *      Author: lijing
 */

#include "scene/mesh/MeshLoader.h"
#include "scene/mesh/MD2MeshLoader.h"
#include "scene/mesh/MS3DMeshLoader.h"
#include "scene/mesh/OBJMeshLoader.h"
#include "io/FileInputStream.h"
#include "utils/LruCache.h"
#include "utils/String.h"

namespace pola {
namespace scene {


static MeshLoader* getMeshLoader(io::InputStream* is, const utils::String& type) {
	static utils::LruCache<utils::String, MeshLoader*> meshLoaders(utils::LruCache<utils::String, MeshLoader*>::kUnlimitedCapacity);
	static bool initialed = false;
	if (!initialed) {
		initialed = true;
		meshLoaders.put(utils::String("md2"), new MD2MeshLoader);
		meshLoaders.put(utils::String("ms3d"), new MS3DMeshLoader);
		meshLoaders.put(utils::String("obj"), new OBJMeshLoader);
	}

	MeshLoader* meshLoader = meshLoaders.get(type);
	if (meshLoader != nullptr) {
		return meshLoader;
	}

	utils::LruCache<utils::String, MeshLoader*>::Iterator iter(meshLoaders);
	while (iter.next()) {
		meshLoader = iter.value();
		if (meshLoader->available(is)) {
			is->rewind();
			return meshLoader;
		}
		is->rewind();
	}
	return nullptr;
}

Mesh* MeshLoader::loadMesh(const char* meshFile) {
	io::FileInputStream is(meshFile);
	utils::String type(true);
	utils::String s(meshFile);
	ssize_t index = s.lastIndexOf('.');
	if (index >= 0 && size_t(index + 1) < s.length()) {
		type = s.substring(index + 1);
	}
	return loadMesh(&is, type);
}
Mesh* MeshLoader::loadMesh(io::InputStream* is, const utils::String& type) {
	MeshLoader* meshLoader = getMeshLoader(is, type);
	if (meshLoader != nullptr) {
		return meshLoader->doLoadMesh(is);
	}
	return nullptr;
}

}
}

