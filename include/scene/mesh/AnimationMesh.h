/*
 * AnimationMesh.h
 *
 *  Created on: 2016年5月21日
 *      Author: lijing
 */

#ifndef POLA_ANIMATIONMESH_H_
#define POLA_ANIMATIONMESH_H_

#include "scene/mesh/Mesh.h"
#include "scene/mesh/MeshBuffer.h"

namespace pola {
namespace scene {

class AnimationMesh: public Mesh {
public:

	AnimationMesh() : m_mesh(nullptr) {};

	virtual ~AnimationMesh() {
		if (m_mesh) {
			delete m_mesh;
		}
	};

	MeshBuffer* m_mesh;
private:
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_ANIMATIONMESH_H_ */
