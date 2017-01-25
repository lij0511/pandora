/*
 * LightNode.cpp
 *
 *  Created on: 2016年8月4日
 *      Author: lijing
 */

#include "pola/log/Log.h"
#include "pola/scene/light/LightNode.h"
#include "pola/scene/camera/OrthoCamera.h"
#include "pola/scene/camera/PerspectiveCamera.h"

namespace pola {
namespace scene {

LightNode::LightNode(graphic::Light* light) : mLight(light) {
	if (isDirectionalLight()) {
		mShadowCamera = new OrthoCamera(- 32, 32, - 32, 32, 0.5f, 500);
	} else if (isSpotLight()) {
		mShadowCamera = new PerspectiveCamera(M_PI / 180.f * 50, 1, 0.5, 500);
	} else if (isPointLight()) {
		mShadowCamera = new PerspectiveCamera(M_PI / 180.f * 90, 1, 0.5, 500);
	} else {
		LOG_ALWAYS_FATAL("Unknown lightType.");
	}
}

LightNode::~LightNode() {
	delete mLight;
}

graphic::Light* LightNode::light() const {
	return mLight;
}

bool LightNode::isDirectionalLight() const {
	return mLight->isDirectionalLight();
}

bool LightNode::isPointLight() const {
	return mLight->isPointLight();
}

bool LightNode::isSpotLight() const {
	return mLight->isSpotLight();
}

bool LightNode::updateTransform() {
	bool r = SceneNode::updateTransform();
	if (r) {
		if (!mLight->castShadow) {
			mShadowCamera->requestPropertyChange();
		}
	}
	if (mLight->castShadow) {
		mShadowCamera->updateTransform();
	}
	return r;
}

Camera* LightNode::shadowCamera() const {
	return mShadowCamera;
}

} /* namespace scene */
} /* namespace pola */
