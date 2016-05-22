/*
 * MeshLoader.h
 *
 *  Created on: 2016年5月21日
 *      Author: lijing
 */

#ifndef POLA_MESHLOADER_H_
#define POLA_MESHLOADER_H_

#include "io/InputStream.h"
#include "scene/mesh/AnimationMesh.h"

namespace pola {
namespace scene {

class MeshLoader {
public:
	virtual ~MeshLoader() {};

	virtual AnimationMesh* loadMesh(io::InputStream* is) = 0;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_MESHLOADER_H_ */
