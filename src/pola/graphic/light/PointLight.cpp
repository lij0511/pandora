/*
 * PointLight.cpp
 *
 *  Created on: 2016年5月29日
 *      Author: lijing
 */

#include "pola/graphic/light/PointLight.h"

namespace pola {
namespace graphic {

PointLight::PointLight(const vec3& pos, float dis, const FColor3& color) : Light(LIGHT_POINT, color), position(pos), distance(dis) {
}

PointLight::~PointLight() {
}

void PointLight::setPosition(const vec3& pos) {
	position = pos;
}

} /* namespace graphic */
} /* namespace pola */
