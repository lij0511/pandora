/*
 * SceneObject.h
 *
 *  Created on: 2016年6月24日
 *      Author: lijing
 */

#ifndef POLA_SCENEOBJECT_H_
#define POLA_SCENEOBJECT_H_

#include "pola/graphic/math/Vector.h"
#include "pola/graphic/math/Quaternion.h"
#include "pola/graphic/math/Euler.h"
#include "pola/graphic/math/Matrix4.h"
#include "pola/graphic/math/Box3.h"
#include "pola/graphic/GraphicContext.h"

#include "pola/utils/Times.h"
#include "pola/utils/RefBase.h"

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

	size_t getChildCount() const;
	SceneObject* getChild(unsigned index);

	void translateX(float dx);
	void translateY(float dy);
	void translateZ(float dz);

protected:
	virtual void onPropertyChange();

	virtual void updateTransform();

	void translateOnAxis(const graphic::vec3& axis, float d);

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
