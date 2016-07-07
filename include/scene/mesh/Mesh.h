/*
 * Mesh.h
 *
 *  Created on: 2016年5月19日
 *      Author: lijing
 */

#ifndef POLA_MESH_H_
#define POLA_MESH_H_

#include "utils/RefBase.h"
#include "graphic/Geometry.h"

namespace pola {
namespace scene {

class Mesh : public utils::RefBase<Mesh> {
public:
	virtual ~Mesh() {};

	virtual graphic::Geometry* geometry() = 0;

};

}
}

#endif /* POLA_MESH_H_ */
