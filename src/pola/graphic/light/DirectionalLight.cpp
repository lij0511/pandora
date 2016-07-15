/*
 * DirectionalLight.cpp
 *
 *  Created on: 2016年5月29日
 *      Author: lijing
 */

#include "pola/graphic/light/DirectionalLight.h"

namespace pola {
namespace graphic {

DirectionalLight::DirectionalLight(const vec3& dir , const FColor3& color) : Light(LIGHT_DIRECTIONAL, color), direction(dir) {
}

DirectionalLight::~DirectionalLight() {
}

void DirectionalLight::setDirection(const vec3& dir) {
	direction = dir;
}

} /* namespace graphic */
} /* namespace pola */
