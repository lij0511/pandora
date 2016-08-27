/*
 * MeshLoader.cpp
 *
 *  Created on: 2016年5月24日
 *      Author: lijing
 */

#include "pola/scene/mesh/MeshLoader.h"
#include "pola/scene/mesh/MD2MeshLoader.h"
#include "pola/scene/mesh/MS3DMeshLoader.h"
#include "pola/scene/mesh/OBJMeshLoader.h"
#ifdef MESH_LOADER_FBX
#include "pola/scene/mesh/FBXMeshLoader.h"
#endif
#include "pola/io/FileInputStream.h"
#include "pola/utils/String.h"

#include <map>
#include <vector>

namespace pola {
namespace scene {

static MeshLoader* getMeshLoader(io::InputStream* is, const utils::String& type) {
	static std::map<utils::String, MeshLoader*> meshLoaders;
	static bool initialed = false;
	if (!initialed) {
		initialed = true;
		meshLoaders[utils::String("md2")] = new MD2MeshLoader;
		meshLoaders[utils::String("ms3d")] = new MS3DMeshLoader;
		meshLoaders[utils::String("obj")] = new OBJMeshLoader;
#ifdef MESH_LOADER_FBX
		meshLoaders[utils::String("fbx")] = new FBXMeshLoader;
#endif
	}

	std::map<utils::String, MeshLoader*>::iterator iter = meshLoaders.find(type);
	if (iter != meshLoaders.end()) {
		return iter->second;
	}

	MeshLoader* meshLoader = nullptr;
	for (std::map<utils::String, MeshLoader*>::iterator iter = meshLoaders.begin(); iter != meshLoaders.end(); iter ++) {
		meshLoader = iter->second;
		if (meshLoader->available(is)) {
			is->rewind();
			return meshLoader;
		}
		is->rewind();
	}
	return nullptr;
}

pola::utils::sp<MeshLoader::Result> MeshLoader::loadMesh(const char* meshFile) {
	io::FileInputStream is(meshFile);
	utils::String type;
	utils::String s(meshFile);
	ssize_t index = s.lastIndexOf('.');
	if (index >= 0 && size_t(index + 1) < s.length()) {
		type = s.substring(index + 1).lower();
	}
	return loadMesh(&is, type);
}
pola::utils::sp<MeshLoader::Result> MeshLoader::loadMesh(io::InputStream* is, const utils::String& type) {

	MeshLoader* meshLoader = getMeshLoader(is, type);
	if (meshLoader != nullptr) {
		return meshLoader->doLoadMesh(is);
	}
	return nullptr;
}

}
}

