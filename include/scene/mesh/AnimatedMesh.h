/*
 * AnimatedMesh.h
 *
 *  Created on: 2016年5月21日
 *      Author: lijing
 */

#ifndef POLA_ANIMATEDMESH_H_
#define POLA_ANIMATEDMESH_H_

#include "scene/mesh/Mesh.h"
#include "scene/mesh/MeshBuffer.h"

namespace pola {
namespace scene {

class AnimatedMesh: public Mesh {
public:

	virtual ~AnimatedMesh() {};

};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_ANIMATEDMESH_H_ */