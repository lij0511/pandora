/*
 * Environment.cpp
 *
 *  Created on: 2016年5月29日
 *      Author: lijing
 */

#include "pola/log/Log.h"
#include "pola/scene/Environment.h"

namespace pola {
namespace scene {

Environment::Environment() {
	mLights = new graphic::Lights;
}

Environment::~Environment() {
	delete mLights;
}

Environment::Environment(const Environment& other) {
	mLights = nullptr;
}

Environment& Environment::operator=(const Environment& other) {
	return *this;
}

void Environment::addLight(graphic::Light* light) {
	mLights->addLight(light);
}

void Environment::removeLight(graphic::Light* light) {
	mLights->removeLight(light);
}

void Environment::setAmbientLight(const graphic::FColor3& color) {
	mLights->setAmbientLight(color);
}

graphic::FColor3 Environment::ambientLight() const {
	return mLights->ambientLight();
}

graphic::Lights* Environment::lights() const {
	return mLights;
}

} /* namespace scene */
} /* namespace pola */
