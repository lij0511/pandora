/*
 * BasicMesh.h
 *
 *  Created on: 2016年5月31日
 *      Author: lijing
 */

#ifndef BASICMESH_H_
#define BASICMESH_H_

#include "pola/scene/mesh/IMesh.h"
#include "pola/graphic/geometries/Geometry3D.h"
#include "pola/graphic/geometries/Geometry2D.h"

namespace pola {
namespace scene {

/*
 *
 */
class BasicMesh: public IMesh {
public:
	BasicMesh();
	BasicMesh(graphic::Geometry* geometry);
	virtual ~BasicMesh();

	virtual graphic::Geometry* geometry();

private:
	graphic::Geometry* mGeometry;
};

} /* namespace scene */
} /* namespace pola */

#endif /* BASICMESH_H_ */
