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
#include "graphic/math/Euler.h"
#include "graphic/math/Matrix4.h"
#include "graphic/GraphicContext.h"

#include "utils/Times.h"
#include "utils/RefBase.h"

namespace pola {
namespace scene {

class SceneNode : public utils::RefBase<SceneNode> {
public:
	SceneNode();
	virtual ~SceneNode();

	void setPosition(const graphic::vec3& position);
	const graphic::vec3& getPosition() const;

	void setRotation(const graphic::Euler& rotation);
	const graphic::Euler& getRotation() const;

	void setScale(const graphic::vec3& scale);
	const graphic::vec3& getScale() const;

	virtual const graphic::mat4 getTransform();

	void addChild(SceneNode* node);
	void removeChild(SceneNode* node);

	void dispatchRender(graphic::GraphicContext* graphic, nsecs_t timeMs);

protected:
	virtual void render(graphic::GraphicContext* graphic, nsecs_t timeMs);
	virtual void onPropertyChange();

	graphic::vec3 mPosition;
	graphic::Euler mRotation;
	graphic::vec3 mScale;

	graphic::mat4 mMatrix;
	bool mMatrixDirty;

	SceneNode* mParent;
	utils::Vector<SceneNode*> mChildren;

};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_SCENENODE_H_ */
