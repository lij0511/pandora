/*
 * MeshLoader.h
 *
 *  Created on: 2016年5月21日
 *      Author: lijing
 */

#ifndef POLA_MESHLOADER_H_
#define POLA_MESHLOADER_H_

#include "pola/io/InputStream.h"
#include "pola/scene/mesh/Mesh.h"
#include "pola/utils/String.h"

namespace pola {
namespace scene {

class MeshLoader {
public:
	virtual ~MeshLoader() {};

	static Mesh* loadMesh(const char* meshFile);
	static Mesh* loadMesh(io::InputStream* is, const utils::String& type);

	virtual bool available(io::InputStream* is) = 0;
protected:
	virtual Mesh* doLoadMesh(io::InputStream* is) = 0;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_MESHLOADER_H_ */
