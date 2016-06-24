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

#include "scene/SceneObject.h"

#include "utils/Times.h"
#include "utils/RefBase.h"

namespace pola {
namespace scene {

class SceneNode : public SceneObject {
public:
	SceneNode();
	virtual ~SceneNode();

	void dispatchRender(graphic::GraphicContext* graphic, nsecs_t timeMs);

protected:
	virtual void render(graphic::GraphicContext* graphic, nsecs_t timeMs);
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_SCENENODE_H_ */
