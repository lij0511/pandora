/*
 * MS3DMeshLoader.cpp
 *
 *  Created on: 2016年5月31日
 *      Author: lijing
 */

#include "pola/scene/mesh/MS3DMeshLoader.h"

namespace pola {
namespace scene {

#include "pola/utils/spack.h"
// File header
struct MS3DHeader {
	char id[10];
	int32_t version;
} PACK_STRUCT;
#include "pola/utils/sunpack.h"

MS3DMeshLoader::MS3DMeshLoader() {
}

MS3DMeshLoader::~MS3DMeshLoader() {
}

bool MS3DMeshLoader::available(io::InputStream* is) {
	return false;
}

Mesh* MS3DMeshLoader::doLoadMesh(io::InputStream* is) {
	MS3DHeader header;
	is->read(&header, sizeof(MS3DHeader));

	if (strncmp(header.id, "MS3D000000", 10 ) != 0 ) {
		LOGE("MS3D Loader: Wrong file header\n");
		return nullptr;
	}
	if (header.version < 3 || header.version > 4) {
		LOGE("Only Milkshape3D version 3 and 4 (1.3 to 1.8) is supported. Loading failed. version is %d\n", header.version);
		return nullptr;
	}

	return nullptr;
}

} /* namespace scene */
} /* namespace pola */
