/*
 * SceneNode.h
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#ifndef POLA_SCENENODE_H_
#define POLA_SCENENODE_H_

#include "pola/graphic/math/Math.h"
#include "pola/graphic/GraphicContext.h"

#include "pola/scene/SceneObject.h"

#include "pola/utils/Times.h"
#include "pola/utils/RefBase.h"

namespace pola {
namespace scene {

class SceneNode : public SceneObject {
public:
	SceneNode();
	virtual ~SceneNode();

	virtual void setMaterial(uint16_t index, graphic::Material* material);

	virtual void update(p_nsecs_t timeMs);

	void setEnable(bool enable);
	bool isEnable() const;

private:
	bool mEnable;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_SCENENODE_H_ */
