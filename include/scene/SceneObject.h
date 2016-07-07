/*
 * SceneObject.h
 *
 *  Created on: 2016年6月24日
 *      Author: lijing
 */

#ifndef POLA_SCENEOBJECT_H_
#define POLA_SCENEOBJECT_H_

#include "graphic/math/Vector.h"
#include "graphic/math/Quaternion.h"
#include "graphic/math/Euler.h"
#include "graphic/math/Matrix4.h"
#include "graphic/math/Box3.h"
#include "graphic/GraphicContext.h"

#include "utils/Times.h"
#include "utils/RefBase.h"

namespace pola {
namespace scene {

/*
 *
 */
class SceneObject : public utils::RefBase<SceneObject> {
public:
	SceneObject();
	virtual ~SceneObject();

	void setPosition(const graphic::vec3& position);
	const graphic::vec3& getPosition() const;

	void setRotation(const graphic::Euler& rotation);
	const graphic::Euler& getRotation() const;

	void setScale(const graphic::vec3& scale);
	const graphic::vec3& getScale() const;

	const graphic::mat4 getTransform();

	const graphic::mat4 getWorldTransform();

	void addChild(SceneObject* node);
	void removeChild(SceneObject* node);

protected:
	virtual void onPropertyChange();

	virtual void updateTransform();

	graphic::vec3 mPosition;
	graphic::Euler mRotation;
	graphic::vec3 mScale;

	graphic::mat4 mWorldMatrix;
	graphic::mat4 mMatrix;
	bool mMatrixDirty;

	graphic::Box3 mBoundingBox;

	SceneObject* mParent;
	utils::Vector<SceneObject*> mChildren;
};

} /* namespace scene */
} /* namespace pola */

#endif /* SCENEOBJECT_H_ */
