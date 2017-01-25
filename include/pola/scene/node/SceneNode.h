/*
 * SceneNode.h
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#ifndef POLA_SCENENODE_H_
#define POLA_SCENENODE_H_

#include "pola/graphic/Object3D.h"
#include "pola/graphic/GraphicContext.h"

#include "pola/utils/Times.h"
#include "pola/utils/RefBase.h"

#include <vector>

namespace pola {
namespace scene {

class SceneNode : public graphic::Object3D, public utils::RefBase {
public:
	SceneNode();
	virtual ~SceneNode();

	virtual void setMaterial(uint16_t index, graphic::Material* material);

	virtual void update(p_nsecs_t timeMs);

	void setEnable(bool enable);
	bool isEnable() const;

	virtual void render(graphic::GraphicContext* graphic, p_nsecs_t timeMs);
	virtual void render(graphic::GraphicContext* graphic, graphic::Material* m, p_nsecs_t timeMs);

	virtual void setPosition(const graphic::vec3& position);

	virtual void setRotation(const graphic::Euler& rotation);

	virtual void setScale(const graphic::vec3& scale);

	const graphic::mat4 getTransform();
	const graphic::mat4 getWorldTransform();
	virtual bool updateTransform();

	void addChild(SceneNode* node);
	void removeChild(SceneNode* node);

	size_t getChildCount() const;
	SceneNode* getChild(unsigned index);

	void translateX(float dx);
	void translateY(float dy);
	void translateZ(float dz);

	virtual bool viewable(const graphic::Frustum& frustum);

	void requestPropertyChange();
protected:
	virtual void onPropertyChange();

	void translateOnAxis(const graphic::vec3& axis, float d);

	graphic::mat4 mWorldMatrix;
	graphic::mat4 mMatrix;
	bool mMatrixDirty;

	graphic::Box3 mBoundingBox;

	SceneNode* mParent;
	std::vector<SceneNode*> mChildren;

	bool mEnable;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_SCENENODE_H_ */
