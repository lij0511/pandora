/*
 * DirectionalLight.cpp
 *
 *  Created on: 2016年5月29日
 *      Author: lijing
 */

#include "graphic/light/DirectionalLight.h"

namespace pola {
namespace graphic {

DirectionalLight::DirectionalLight() : Light(LIGHT_DIRECTIONAL){
}

DirectionalLight::~DirectionalLight() {
}

void DirectionalLight::setDirection(const vec3& direction) {
	m_direction = direction;
}

} /* namespace graphic */
} /* namespace pola */
