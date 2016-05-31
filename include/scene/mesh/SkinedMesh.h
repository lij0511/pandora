/*
 * SkinedMesh.h
 *
 *  Created on: 2016年5月31日
 *      Author: lijing
 */

#ifndef POLA_SKINEDMESH_H_
#define POLA_SKINEDMESH_H_

#include "scene/mesh/AnimatedMesh.h"

namespace pola {
namespace scene {

class SkinedMesh: public AnimatedMesh {
public:
	SkinedMesh();
	virtual ~SkinedMesh();
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_SKINEDMESH_H_ */
