/*
 * DirectionalLight.h
 *
 *  Created on: 2016年5月29日
 *      Author: lijing
 */

#ifndef POLA_DIRECTIONALLIGHT_H_
#define POLA_DIRECTIONALLIGHT_H_

#include "graphic/light/Light.h"

namespace pola {
namespace graphic {

class DirectionalLight: public Light {
public:
	DirectionalLight();
	virtual ~DirectionalLight();

	void setDirection(const vec3& direction);

private:
	vec3 m_direction;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_DIRECTIONALLIGHT_H_ */
