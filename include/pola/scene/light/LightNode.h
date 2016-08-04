/*
 * LightNode.h
 *
 *  Created on: 2016年8月4日
 *      Author: lijing
 */

#ifndef POLA_LIGHTNODE_H_
#define POLA_LIGHTNODE_H_

#include "pola/graphic/light/Light.h"
#include "pola/scene/node/SceneNode.h"
#include "pola/scene/camera/Camera.h"

namespace pola {
namespace scene {

/*
 *
 */
class LightNode: public SceneNode {
public:
	LightNode(graphic::Light* light);
	virtual ~LightNode();

	graphic::Light* light() const;

	bool isDirectionalLight() const;
	bool isPointLight() const;
	bool isSpotLight() const;

	virtual bool updateTransform();

	Camera* shadowCamera() const;

private:
	graphic::Light* mLight;
	Camera* mShadowCamera;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_LIGHTNODE_H_ */
