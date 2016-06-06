/*
 * Material.cpp
 *
 *  Created on: 2016年5月23日
 *      Author: lijing
 */

#include "graphic/Material.h"

namespace pola {
namespace graphic {

Material::Material() : mTextures({nullptr}), mAmbientColor(1.f, 1.f, 1.f, 1.f)
	, mDiffuseColor(1.f, 1.f, 1.f, 1.f), mEmissiveColor(0.f, 0.f, 0.f, 0.f)
	, mSpecularColor(1.f, 1.f, 1.f, 1.f), mShininess(0.f) {
}

Material::~Material() {
}

void Material::setTexture(uint32_t i, Texture* texture) {
	if (i >= MAX_TEXTURE_UNITS_COUNT) {
		return;
	}
	mTextures[i] = texture;
}

Texture* Material::getTexture(uint32_t i) const {
	if (i >= MAX_TEXTURE_UNITS_COUNT) {
		return nullptr;
	}
	return mTextures[i];
}

} /* namespace graphic */
} /* namespace pola */
