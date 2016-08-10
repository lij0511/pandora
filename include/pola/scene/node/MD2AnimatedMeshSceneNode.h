/*
 * MD2AnimatedMeshSceneNode.h
 *
 *  Created on: 2016年5月29日
 *      Author: lijing
 */

#ifndef POLA_MD2ANIMATEDMESHSCENENODE_H_
#define POLA_MD2ANIMATEDMESHSCENENODE_H_

#include "pola/scene/node/AnimatedMeshSceneNode.h"
#include "pola/scene/mesh/MD2AnimatedMesh.h"

namespace pola {
namespace scene {

class MD2AnimatedMeshSceneNode: public AnimatedMeshSceneNode {
public:
	MD2AnimatedMeshSceneNode(MD2AnimatedMesh* mesh);
	virtual ~MD2AnimatedMeshSceneNode();

	void setAnimationType(MD2_ANIMATION_TYPE type);

	virtual Mesh* mesh(uint32_t index);

	virtual void update(p_nsecs_t timeMs);

private:
	MD2AnimatedMesh* mMesh;

};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_MD2ANIMATEDMESHSCENENODE_H_ */
