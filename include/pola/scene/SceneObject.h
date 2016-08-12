/*
 * SceneObject.h
 *
 *  Created on: 2016年6月24日
 *      Author: lijing
 */

#ifndef POLA_SCENEOBJECT_H_
#define POLA_SCENEOBJECT_H_

#include "pola/graphic/Object3D.h"
#include "pola/graphic/GraphicContext.h"

#include "pola/utils/Times.h"
#include "pola/utils/RefBase.h"

#include <vector>

namespace pola {
namespace scene {

/*
 *
 */
class SceneObject : public graphic::Object3D, public utils::RefBase<SceneObject> {
public:
	SceneObject();
	virtual ~SceneObject();

	virtual void setPosition(const graphic::vec3& position);

	virtual void setRotation(const graphic::Euler& rotation);

	virtual void setScale(const graphic::vec3& scale);

	const graphic::mat4 getTransform();
	const graphic::mat4 getWorldTransform();
	virtual bool updateTransform();

	void addChild(SceneObject* node);
	void removeChild(SceneObject* node);

	size_t getChildCount() const;
	SceneObject* getChild(unsigned index);

	void translateX(float dx);
	void translateY(float dy);
	void translateZ(float dz);

	void requestPropertyChange();
protected:
	virtual void onPropertyChange();

	void translateOnAxis(const graphic::vec3& axis, float d);

	graphic::mat4 mWorldMatrix;
	graphic::mat4 mMatrix;
	bool mMatrixDirty;

	graphic::Box3 mBoundingBox;

	SceneObject* mParent;
	std::vector<SceneObject*> mChildren;
};

} /* namespace scene */
} /* namespace pola */

#endif /* SCENEOBJECT_H_ */
