/*
 * Light.cpp
 *
 *  Created on: 2016年5月23日
 *      Author: lijing
 */

#include "graphic/light/Light.h"

namespace pola {
namespace graphic {

Light::Light(const LightType type) : mType(type) {
}

Light::~Light() {
}

const Light::LightType Light::lightType() const {
	return mType;
}

void Light::setColor(FColor color) {
	mColor = color;
}

} /* namespace graphic */
} /* namespace pola */
