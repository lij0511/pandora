/*
 * SceneNode.h
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#ifndef POLA_SCENENODE_H_
#define POLA_SCENENODE_H_

#include "graphic/Vector.h"

namespace pola {
namespace graphic {
class GraphicContext;
}
namespace scene {

class SceneNode {
public:
	SceneNode(const graphic::vec3& position = graphic::vec3(0,0,0));
	virtual ~SceneNode();

	virtual void render(graphic::GraphicContext* graphic);

protected:
	graphic::vec3 m_position;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_SCENENODE_H_ */
