/*
 * MeshLoader.h
 *
 *  Created on: 2016年5月21日
 *      Author: lijing
 */

#ifndef POLA_MESHLOADER_H_
#define POLA_MESHLOADER_H_

#include "io/InputStream.h"
#include "scene/mesh/AnimatedMesh.h"

namespace pola {
namespace scene {

class MeshLoader {
public:
	virtual ~MeshLoader() {};

	static AnimatedMesh* loadMesh(const char* meshFile);
	static AnimatedMesh* loadMesh(io::InputStream* is);

protected:
	virtual AnimatedMesh* doLoadMesh(io::InputStream* is) = 0;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_MESHLOADER_H_ */
