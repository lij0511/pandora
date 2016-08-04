/*
 * ShadowMap.cpp
 *
 *  Created on: 2016年8月4日
 *      Author: lijing
 */

#include "pola/scene/light/ShadowMap.h"

namespace pola {
namespace scene {

ShadowMap::ShadowMap(graphic::Lights* lights) : mLights(lights) {
}

ShadowMap::~ShadowMap() {
}

ShadowMap& ShadowMap::operator=(const ShadowMap& other) {
	return *this;
}
ShadowMap::ShadowMap(const ShadowMap& other) {
	mLights = nullptr;
}

void ShadowMap::render(graphic::GraphicContext* graphic, p_nsecs_t timeMs) {
	graphic->setLights(nullptr);

	for (unsigned index = 0; index < mLights->lightCount(); index ++) {
		graphic::Light* light = mLights->lightAt(index);
		if (light->map == nullptr) {
			light->map = graphic->createRenderTarget(light->mapSize.width, light->mapSize.height);
		}
	}
}

} /* namespace scene */
} /* namespace pola */
