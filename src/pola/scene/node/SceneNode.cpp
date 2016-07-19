/*
 * SceneNode.cpp
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#include "pola/scene/node/SceneNode.h"
#include "pola/graphic/GraphicContext.h"

namespace pola {
namespace scene {

SceneNode::SceneNode() {
}

SceneNode::~SceneNode() {
}

void SceneNode::dispatchRender(graphic::GraphicContext* graphic, p_nsecs_t timeMs) {
	render(graphic, timeMs);
	/*for (unsigned i = 0; i < mChildren.size(); i ++) {
		SceneNode* child = dynamic_cast<SceneNode*>(mChildren[i]);
		if (child != nullptr) {
			child->dispatchRender(graphic, timeMs);
		}
	}*/
}

void SceneNode::render(graphic::GraphicContext* graphic, p_nsecs_t timeMs) {
}

} /* namespace scene */
} /* namespace pola */
