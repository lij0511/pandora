/*
 * NullMeshSceneNode.h
 *
 *  Created on: 2016年8月17日
 *      Author: lijing
 */

#ifndef POLA_NULLMESHSCENENODE_H_
#define POLA_NULLMESHSCENENODE_H_

#include "pola/scene/node/SceneNode.h"
#include "pola/scene/mesh/IMesh.h"

namespace pola {
namespace scene {

/*
 *
 */
class NullMeshSceneNode: public SceneNode {
public:
	NullMeshSceneNode(IMesh* mesh);
	virtual ~NullMeshSceneNode();

private:
	IMesh* mMesh;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_NULLMESHSCENENODE_H_ */
