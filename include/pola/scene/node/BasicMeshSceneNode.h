/*
 * BasicMeshSceneNode.h
 *
 *  Created on: 2016年6月13日
 *      Author: lijing
 */

#ifndef POLA_BASICMESHSCENENODE_H_
#define POLA_BASICMESHSCENENODE_H_

#include "pola/scene/node/MeshSceneNode.h"
#include "pola/scene/mesh/BasicMesh.h"

namespace pola {
namespace scene {

class BasicMeshSceneNode: public MeshSceneNode {
public:
	BasicMeshSceneNode(BasicMesh* mesh);
	virtual ~BasicMeshSceneNode();

	virtual Mesh* mesh();

protected:
	virtual void render(graphic::GraphicContext* graphic, nsecs_t timeMs);

private:
	BasicMesh* mMesh;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_BASICMESHSCENENODE_H_ */
