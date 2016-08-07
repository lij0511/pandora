/*
 * Light.cpp
 *
 *  Created on: 2016年5月23日
 *      Author: lijing
 */

#include "pola/graphic/light/Light.h"
#include "pola/graphic/light/Lights.h"

namespace pola {
namespace graphic {

Light::Light(LightType type, const FColor3& c) : mType(type), mLightOn(true), mInUsed(false), color(c) {
	castShadow = false;
	mapSize = {1024, 1024};
	map = nullptr;
}

Light::~Light() {
	if (map != nullptr) {
		delete map;
	}
}

void Light::setColor(FColor3 color) {
	this->color = color;
}

Light::LightType Light::lightType() const {
	return mType;
}

bool Light::isDirectionalLight() const {
	return mType == LIGHT_DIRECTIONAL;
}

bool Light::isPointLight() const {
	return mType == LIGHT_POINT;
}

bool Light::isSpotLight() const {
	return mType == LIGHT_SPOT;
}

bool Light::lightOn() const {
	return mLightOn;
}
void Light::setLightOn(bool lightOn) {
	mLightOn = lightOn;
}

bool Light::inUsed() const {
	return mInUsed;
}
void Light::setInUsed(bool inUsed) {
	mInUsed = inUsed;
}

} /* namespace graphic */
} /* namespace pola */
