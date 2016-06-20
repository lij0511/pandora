/*
 * Environment.cpp
 *
 *  Created on: 2016年5月29日
 *      Author: lijing
 */

#include "log/Log.h"
#include "scene/Environment.h"

namespace pola {
namespace scene {

Environment::Environment() {
	mLights = new graphic::Lights;
}

Environment::~Environment() {
}

void Environment::addLight(graphic::Light* light) {
	mLights->addLight(light);
}

void Environment::removeLight(graphic::Light* light) {
	mLights->removeLight(light);
}

graphic::Lights* Environment::lights() const {
	return mLights;
}

} /* namespace scene */
} /* namespace pola */
