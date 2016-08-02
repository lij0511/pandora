/*
 * PointLight.h
 *
 *  Created on: 2016年5月29日
 *      Author: lijing
 */

#ifndef POLA_POINTLIGHT_H_
#define POLA_POINTLIGHT_H_

#include "pola/graphic/light/Light.h"

namespace pola {
namespace graphic {

class PointLight: public Light {
public:
	PointLight(const vec3& pos = {1.f, 1.f, 1.f}, float dis = 0, const FColor3& color = {1.f, 1.f, 1.f});
	virtual ~PointLight();

	void setPosition(const vec3& pos);

	vec3 position;
	float distance;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_POINTLIGHT_H_ */
