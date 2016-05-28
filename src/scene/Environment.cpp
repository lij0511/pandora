/*
 * Environment.cpp
 *
 *  Created on: 2016年5月29日
 *      Author: lijing
 */

#include "log/Log.h"
#include "scene/Environment.h"

namespace pola {
namespace scene {

Environment::Environment() {
}

Environment::~Environment() {
}

void Environment::addLight(graphic::Light* light) {
	const uint32_t maxCount = LIGHT_MAX_COUNT;
	if (m_lights.size() >= maxCount) {
		LOGE("Can not initial more than %u lights.\n", maxCount);
		return;
	}
	m_lights.push(light);
}

void Environment::removeLight(graphic::Light* light) {
	/*utils::Vector::iterator begin = m_lights.begin();
	utils::Vector::iterator end = m_lights.begin();
	while (begin != end) {
		if (begin == light) {
			m_lights.erase(begin);
		}
		begin ++;
	}*/
}

} /* namespace scene */
} /* namespace pola */
