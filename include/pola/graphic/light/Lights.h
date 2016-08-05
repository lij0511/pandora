/*
 * Lights.h
 *
 *  Created on: 2016年6月19日
 *      Author: lijing
 */

#ifndef POLA_LIGHTS_H_
#define POLA_LIGHTS_H_

#include "pola/graphic/light/Light.h"
#include "pola/graphic/light/DirectionalLight.h"
#include "pola/graphic/light/PointLight.h"

#include <vector>

namespace pola {
namespace graphic {

class Lights {
public:
	Lights();
	virtual ~Lights();

	void clear();

	void addLight(Light* light);
	void removeLight(Light* light);

	void setAmbientLight(const FColor3& light);
	FColor3 ambientLight() const;

	size_t directionalLightCount() const;
	size_t pointLightCount() const;
	size_t spotLightCount() const;

	Light* directionalLight(unsigned index) const;
	Light* pointLight(unsigned index) const;
	Light* spotLight(unsigned index) const;

	bool shadowMap() const;
private:
	void addLight(std::vector<Light*>& lights, Light* light);
	void removeLight(std::vector<Light*>& lights, Light* light);
	void clearLights(std::vector<Light*>& lights);

	FColor3 mAmbientLight;
	std::vector<Light*> mDirectionalLights;
	std::vector<Light*> mPointLights;
	std::vector<Light*> mSpotLights;

	bool mShadowMap;

};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_LIGHTS_H_ */
