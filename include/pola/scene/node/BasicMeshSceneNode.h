/*
 * BasicMeshSceneNode.h
 *
 *  Created on: 2016年6月13日
 *      Author: lijing
 */

#ifndef POLA_BASICMESHSCENENODE_H_
#define POLA_BASICMESHSCENENODE_H_

#include "pola/scene/node/MeshSceneNode.h"
#include "pola/scene/mesh/Mesh.h"

namespace pola {
namespace scene {

class BasicMeshSceneNode: public MeshSceneNode {
public:
	BasicMeshSceneNode(Mesh* mesh);
	virtual ~BasicMeshSceneNode();

	virtual Mesh* mesh();

private:
	Mesh* mMesh;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_BASICMESHSCENENODE_H_ */
