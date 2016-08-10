/*
 * Mesh.h
 *
 *  Created on: 2016年5月19日
 *      Author: lijing
 */

#ifndef POLA_MESH_H_
#define POLA_MESH_H_

#include "pola/utils/RefBase.h"
#include "pola/graphic/Geometry.h"

namespace pola {
namespace scene {

class Mesh : public utils::RefBase<Mesh> {
public:
	Mesh();
	virtual ~Mesh();

	virtual graphic::Geometry* geometry() = 0;

	void setMaterialId(uint32_t materialId);
	uint32_t materialId() const;

private:
	uint32_t mMaterialId;
};

}
}

#endif /* POLA_MESH_H_ */
