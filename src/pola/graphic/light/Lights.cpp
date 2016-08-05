/*
 * Lights.cpp
 *
 *  Created on: 2016年6月19日
 *      Author: lijing
 */

#include "pola/utils/JenkinsHash.h"
#include "pola/graphic/light/Lights.h"

namespace pola {
namespace graphic {

Lights::Lights() : mShadowMap(false) {
}

Lights::~Lights() {
	clear();
}

void Lights::clear() {
	clearLights(mDirectionalLights);
	clearLights(mPointLights);
	clearLights(mSpotLights);
	mShadowMap = false;
}

void Lights::addLight(Light* light) {
	if (light->inUsed()) return;
	if (!light->lightOn()) return;
	switch (light->lightType()) {
		case Light::LIGHT_DIRECTIONAL:
			addLight(mDirectionalLights, light);
			break;
		case Light::LIGHT_POINT:
			addLight(mPointLights, light);
			break;
		case Light::LIGHT_SPOT:
			addLight(mSpotLights, light);
			break;
		default:
			break;
	}
}

void Lights::removeLight(Light* light) {
	switch (light->lightType()) {
		case Light::LIGHT_DIRECTIONAL:
			removeLight(mDirectionalLights, light);
			break;
		case Light::LIGHT_POINT:
			removeLight(mPointLights, light);
			break;
		case Light::LIGHT_SPOT:
			removeLight(mSpotLights, light);
			break;
		default:
			break;
	}
}

void Lights::setAmbientLight(const FColor3& light) {
	mAmbientLight = light;
}

FColor3 Lights::ambientLight() const {
	return mAmbientLight;
}

size_t Lights::directionalLightCount() const {
	return mDirectionalLights.size();
}

size_t Lights::pointLightCount() const {
	return mPointLights.size();
}

size_t Lights::spotLightCount() const {
	return mSpotLights.size();
}

Light* Lights::directionalLight(unsigned index) const {
	return mDirectionalLights[index];
}

Light* Lights::pointLight(unsigned index) const {
	return mPointLights[index];
}

Light* Lights::spotLight(unsigned index) const {
	return mSpotLights[index];
}

bool Lights::shadowMap() const {
	return mShadowMap;
}

void Lights::addLight(std::vector<Light*>& lights, Light* light) {
	for (unsigned i = 0; i < lights.size(); i ++) {
		if (lights[i] == light) {
			return;
		}
	}
	light->setInUsed(true);
	lights.push_back(light);
	mShadowMap |= light->castShadow;
}

void Lights::removeLight(std::vector<Light*>& lights, Light* light) {
	for (std::vector<Light*>::iterator iter = lights.begin(); iter != lights.end(); iter ++) {
		if (*iter == light) {
			lights.erase(iter);
			light->setInUsed(false);
			return;
		}
	}
}

void Lights::clearLights(std::vector<Light*>& lights) {
	for (std::vector<Light*>::iterator iter = lights.begin(); iter != lights.end(); iter ++) {
		(*iter)->setInUsed(false);
	}
	lights.clear();
}

} /* namespace graphic */
} /* namespace pola */
