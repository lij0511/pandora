/*
 * BasicMesh.h
 *
 *  Created on: 2016年5月31日
 *      Author: lijing
 */

#ifndef BASICMESH_H_
#define BASICMESH_H_

#include "scene/mesh/Mesh.h"

namespace pola {
namespace scene {

/*
 *
 */
class BasicMesh: public Mesh {
public:
	BasicMesh(graphic::VertexType vertexType);
	virtual ~BasicMesh();

	virtual size_t getMeshBufferCount() const;
	virtual graphic::MeshBuffer* getMeshBuffer(uint16_t index);

private:
	graphic::MeshBuffer mMeshBuffer;
};

} /* namespace scene */
} /* namespace pola */

#endif /* BASICMESH_H_ */
