/*
 * MD2MeshSceneNode.h
 *
 *  Created on: 2016年5月29日
 *      Author: lijing
 */

#ifndef POLA_MD2MESHSCENENODE_H_
#define POLA_MD2MESHSCENENODE_H_

#include "pola/scene/node/AnimatedMeshSceneNode.h"
#include "pola/scene/mesh/MD2AnimatedMesh.h"

namespace pola {
namespace scene {

class MD2MeshSceneNode: public AnimatedMeshSceneNode {
public:
	MD2MeshSceneNode(MD2AnimatedMesh* mesh);
	virtual ~MD2MeshSceneNode();

	void setAnimationType(MD2_ANIMATION_TYPE type);

	virtual Mesh* mesh();

	virtual void update(p_nsecs_t timeMs);

private:
	MD2AnimatedMesh* mMesh;

};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_MD2ANIMATEDMESHSCENENODE_H_ */
