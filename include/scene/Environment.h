/*
 * Environment.h
 *
 *  Created on: 2016年5月29日
 *      Author: lijing
 */

#ifndef POLA_ENVIRONMENT_H_
#define POLA_ENVIRONMENT_H_

#include "utils/Vector.h"
#include "graphic/light/Light.h"

namespace pola {
namespace scene {

class Environment {
public:
	Environment();
	virtual ~Environment();

	void addLight(graphic::Light* light);
	void removeLight(graphic::Light* light);

private:
	utils::Vector<utils::sp<graphic::Light>> m_lights;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_ENVIRONMENT_H_ */