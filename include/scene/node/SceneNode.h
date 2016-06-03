/*
 * SceneNode.h
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#ifndef POLA_SCENENODE_H_
#define POLA_SCENENODE_H_

#include "graphic/math/Vector.h"
#include "graphic/math/Quaternion.h"
#include "graphic/math/Matrix4.h"
#include "graphic/GraphicContext.h"

#include "utils/Times.h"
#include "utils/RefBase.h"

namespace pola {
namespace scene {

class SceneNode : public utils::RefBase<SceneNode> {
public:
	SceneNode(const graphic::vec3& position = graphic::vec3(0,0,0));
	virtual ~SceneNode();

	void setPosition(const graphic::vec3& position);
	const graphic::vec3& getPosition() const;

	void setRotation(const graphic::quat4& rotation);
	const graphic::quat4& getRotation() const;

	void setScale(const graphic::vec3& scale);
	const graphic::vec3& getScale() const;

	const graphic::mat4 getTransform();

	virtual void render(graphic::GraphicContext* graphic, nsecs_t timeMs);

protected:
	graphic::vec3 mPosition;
	graphic::quat4 mRotation;
	graphic::vec3 mScale;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_SCENENODE_H_ */
