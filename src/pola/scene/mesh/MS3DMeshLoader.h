/*
 * MS3DMeshLoader.h
 *
 *  Created on: 2016年5月31日
 *      Author: lijing
 */

#ifndef POLA_MS3DMESHLOADER_H_
#define POLA_MS3DMESHLOADER_H_

#include "pola/scene/mesh/MeshLoader.h"

namespace pola {
namespace scene {

class MS3DMeshLoader: public MeshLoader {
public:
	MS3DMeshLoader();
	virtual ~MS3DMeshLoader();

	virtual bool available(io::InputStream* is);
protected:
	virtual Mesh* doLoadMesh(io::InputStream* is);
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_MS3DMESHLOADER_H_ */
