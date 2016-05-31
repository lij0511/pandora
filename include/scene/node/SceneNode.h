/*
 * SceneNode.h
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#ifndef POLA_SCENENODE_H_
#define POLA_SCENENODE_H_

#include "graphic/Vector.h"
#include "graphic/Matrix4.h"
#include "graphic/GraphicContext.h"

#include "utils/Times.h"
#include "utils/RefBase.h"

namespace pola {
namespace scene {

class SceneNode : public utils::RefBase<SceneNode> {
public:
	SceneNode(const graphic::vec3& position = graphic::vec3(0,0,0));
	virtual ~SceneNode();

	void setPosition(const graphic::vec3& projection);

	const graphic::mat4 getTransform();

	virtual void render(graphic::GraphicContext* graphic, nsecs_t timeMs);

protected:
	graphic::vec3 mPosition;
	graphic::vec3 mRotation;
	graphic::vec3 mScale;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_SCENENODE_H_ */
