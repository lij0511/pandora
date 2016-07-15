/*
 * SceneNode.h
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#ifndef POLA_SCENENODE_H_
#define POLA_SCENENODE_H_

#include "pola/graphic/math/Vector.h"
#include "pola/graphic/math/Quaternion.h"
#include "pola/graphic/math/Euler.h"
#include "pola/graphic/math/Matrix4.h"
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

	void dispatchRender(graphic::GraphicContext* graphic, nsecs_t timeMs);

protected:
	virtual void render(graphic::GraphicContext* graphic, nsecs_t timeMs);
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_SCENENODE_H_ */
