/*
 * Lights.h
 *
 *  Created on: 2016年6月19日
 *      Author: lijing
 */

#ifndef POLA_LIGHTS_H_
#define POLA_LIGHTS_H_

#include "utils/Vector.h"
#include "graphic/light/Light.h"
#include "graphic/light/DirectionalLight.h"
#include "graphic/light/PointLight.h"

namespace pola {
namespace graphic {

class Lights {
public:
	Lights();
	virtual ~Lights();

	void addLight(Light* light);
	void removeLight(Light* light);

	void setAmbientLight(const FColor3& color);
	FColor3 ambientLight() const;

	size_t directionalLightCount() const;
	size_t pointLightCount() const;
	size_t spotLightCount() const;

	Light* directionalLight(unsigned index) const;
	Light* pointLight(unsigned index) const;
	Light* spotLight(unsigned index) const;

	uint32_t hash() const;

private:
	void addLight(utils::Vector<Light*>& lights, Light* light);
	void removeLight(utils::Vector<Light*>& lights, Light* light);

	FColor3 mAmbientColor;
	utils::Vector<Light*> mDirectionalLights;
	utils::Vector<Light*> mPointLights;
	utils::Vector<Light*> mSpotLights;

	mutable uint32_t mHash;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_LIGHTS_H_ */
