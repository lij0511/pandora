/*
 * SpotLight.cpp
 *
 *  Created on: 2016年8月10日
 *      Author: lijing
 */

#include "pola/graphic/light/SpotLight.h"

namespace pola {
namespace graphic {

SpotLight::SpotLight(const FColor3& color) : Light(LIGHT_SPOT, color) {
}

SpotLight::~SpotLight() {
}

} /* namespace graphic */
} /* namespace pola */
