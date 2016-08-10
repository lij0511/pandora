/*
 * OBJMeshLoader.h
 *
 *  Created on: 2016年5月31日
 *      Author: lijing
 */

#ifndef POLA_OBJMESHLOADER_H_
#define POLA_OBJMESHLOADER_H_

#include "pola/scene/mesh/MeshLoader.h"

namespace pola {
namespace scene {

class OBJMeshLoader: public MeshLoader {
public:
	OBJMeshLoader();
	virtual ~OBJMeshLoader();

protected:
	virtual bool available(io::InputStream* is);
	virtual Mesh* doLoadMesh(io::InputStream* is);
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_OBJMESHLOADER_H_ */
