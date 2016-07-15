/*
 * DirectionalLight.h
 *
 *  Created on: 2016年5月29日
 *      Author: lijing
 */

#ifndef POLA_DIRECTIONALLIGHT_H_
#define POLA_DIRECTIONALLIGHT_H_

#include "pola/graphic/light/Light.h"

namespace pola {
namespace graphic {

class DirectionalLight: public Light {
public:
	DirectionalLight(const vec3& direction, const FColor3& color = {1.f, 1.f, 1.f});
	virtual ~DirectionalLight();

	void setDirection(const vec3& direction);

	vec3 direction;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_DIRECTIONALLIGHT_H_ */
