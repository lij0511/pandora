/*
 * Light.cpp
 *
 *  Created on: 2016年5月23日
 *      Author: lijing
 */

#include "graphic/light/Light.h"

namespace pola {
namespace graphic {

Light::Light(const LightType type) : m_type(type) {
}

Light::~Light() {
}

const Light::LightType Light::lightType() const {
	return m_type;
}

} /* namespace graphic */
} /* namespace pola */
