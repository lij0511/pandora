/*
 * PointLight.cpp
 *
 *  Created on: 2016年5月29日
 *      Author: lijing
 */

#include "pola/graphic/light/PointLight.h"

namespace pola {
namespace graphic {

PointLight::PointLight() : Light(LIGHT_POINT){
}

PointLight::~PointLight() {
}

void PointLight::setPosition(const vec3& position) {
	m_position = position;
}

} /* namespace graphic */
} /* namespace pola */
