/*
 * PointLight.h
 *
 *  Created on: 2016年5月29日
 *      Author: lijing
 */

#ifndef POLA_POINTLIGHT_H_
#define POLA_POINTLIGHT_H_

#include "graphic/light/Light.h"

namespace pola {
namespace graphic {

class PointLight: public Light {
public:
	PointLight();
	virtual ~PointLight();

	void setPosition(const vec3& position);

private:
	vec3 m_position;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_POINTLIGHT_H_ */
