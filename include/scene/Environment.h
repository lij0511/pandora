/*
 * Environment.h
 *
 *  Created on: 2016年5月29日
 *      Author: lijing
 */

#ifndef POLA_ENVIRONMENT_H_
#define POLA_ENVIRONMENT_H_

#include "utils/Vector.h"
#include "graphic/light/Lights.h"

namespace pola {
namespace scene {

class Environment {
public:
	Environment();
	virtual ~Environment();

	void addLight(graphic::Light* light);
	void removeLight(graphic::Light* light);

	const graphic::Lights& lights() const;

private:
	graphic::Lights mLights;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_ENVIRONMENT_H_ */
