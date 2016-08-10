/*
 * SpotLight.h
 *
 *  Created on: 2016年8月10日
 *      Author: lijing
 */

#ifndef SPOTLIGHT_H_
#define SPOTLIGHT_H_

#include "pola/graphic/light/Light.h"

namespace pola {
namespace graphic {

/*
 *
 */
class SpotLight: public Light {
public:
	SpotLight(const FColor3& color = {1.f, 1.f, 1.f});
	virtual ~SpotLight();
};

} /* namespace graphic */
} /* namespace pola */

#endif /* SPOTLIGHT_H_ */
