/*
 * BasicMesh.h
 *
 *  Created on: 2016年5月31日
 *      Author: lijing
 */

#ifndef BASICMESH_H_
#define BASICMESH_H_

#include "scene/mesh/Mesh.h"
#include "graphic/geometries/Geometry3D.h"
#include "graphic/geometries/Geometry2D.h"

namespace pola {
namespace scene {

/*
 *
 */
class BasicMesh: public Mesh {
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
