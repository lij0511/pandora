/*
 * Mesh.h
 *
 *  Created on: 2016年5月19日
 *      Author: lijing
 */

#ifndef POLA_MESH_H_
#define POLA_MESH_H_

#include "utils/RefBase.h"
#include "scene/mesh/MeshBuffer.h"

namespace pola {
namespace scene {

class Mesh : public utils::RefBase<Mesh> {
public:
	virtual ~Mesh() {};

	virtual size_t getMeshBufferCount() const = 0;
	virtual MeshBuffer* getMeshBuffer(uint16_t index) = 0;

};

}
}

#endif /* POLA_MESH_H_ */
