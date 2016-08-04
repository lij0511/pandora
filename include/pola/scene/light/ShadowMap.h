/*
 * ShadowMap.h
 *
 *  Created on: 2016年8月4日
 *      Author: lijing
 */

#ifndef POLA_SHADOWMAP_H_
#define POLA_SHADOWMAP_H_

#include "pola/graphic/GraphicContext.h"
#include "pola/graphic/light/Lights.h"
#include "pola/graphic/material/ShadowMapMaterial.h"

#include "pola/utils/Times.h"

namespace pola {
namespace scene {

/*
 *
 */
class ShadowMap {
public:
	ShadowMap(graphic::Lights* lights);
	virtual ~ShadowMap();

	virtual void render(graphic::GraphicContext* graphic, p_nsecs_t timeMs);

private:
	ShadowMap& operator=(const ShadowMap& other);
	ShadowMap(const ShadowMap& other);

private:
	graphic::Lights* mLights;

	graphic::ShadowMapMaterial mShadowMapMaterial;

};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_SHADOWMAP_H_ */
