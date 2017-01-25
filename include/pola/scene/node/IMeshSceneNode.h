/*
 * IMeshSceneNode.h
 *
 *  Created on: 2016年8月24日
 *      Author: lijing
 */

#ifndef POLA_IMESHSCENENODE_H_
#define POLA_IMESHSCENENODE_H_

#include "pola/scene/node/SceneNode.h"
#include "pola/scene/mesh/IMesh.h"

namespace pola {
namespace scene {

/*
 *
 */
class IMeshSceneNode: public SceneNode {
public:
	virtual ~IMeshSceneNode() {};

	virtual IMesh* mesh() = 0;

	virtual bool viewable(const graphic::Frustum& frustum);

};

inline bool IMeshSceneNode::viewable(const graphic::Frustum& frustum) {
	IMesh* m = mesh();
	if (m != nullptr) {
		return m->intersectsBox(frustum, getWorldTransform());
	}
	return false;
}

} /* namespace scene */
} /* namespace pola */

#endif /* IMESHSCENENODE_H_ */
