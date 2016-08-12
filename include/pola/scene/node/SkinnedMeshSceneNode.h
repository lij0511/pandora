/*
 * SkinnedMeshSceneNode.h
 *
 *  Created on: 2016年8月12日
 *      Author: lijing
 */

#ifndef POLA_SKINNEDMESHSCENENODE_H_
#define POLA_SKINNEDMESHSCENENODE_H_

#include "pola/scene/node/AnimatedMeshSceneNode.h"

namespace pola {
namespace scene {

/*
 *
 */
class SkinnedMeshSceneNode: public AnimatedMeshSceneNode {
public:
	SkinnedMeshSceneNode();
	virtual ~SkinnedMeshSceneNode();
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_SKINNEDMESHSCENENODE_H_ */
