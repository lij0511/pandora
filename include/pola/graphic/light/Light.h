/*
 * Light.h
 *
 *  Created on: 2016年5月23日
 *      Author: lijing
 */

#ifndef POLA_LIGHT_H_
#define POLA_LIGHT_H_

#include "pola/graphic/Color.h"
#include "pola/graphic/RenderTarget.h"
#include "pola/graphic/math/Vector.h"
#include "pola/graphic/math/Matrix4.h"

namespace pola {
namespace graphic {

class Lights;

class Light {
public:

	struct MapSize {
		uint32_t width, height;
	};

	enum LightType {
		//! point light, it has a position in space and radiates light in all directions
		LIGHT_POINT,
		//! spot light, it has a position in space, a direction, and a limited cone of influence
		LIGHT_SPOT,
		//! directional light, coming from a direction from an infinite distance
		LIGHT_DIRECTIONAL,
	};

	Light(LightType type, const FColor3& color = {1.f, 1.f, 1.f});
	virtual ~Light();

	void setColor(const FColor3 color);

	LightType lightType() const;

	bool isDirectionalLight() const;
	bool isPointLight() const;
	bool isSpotLight() const;

	bool lightOn() const;
	void setLightOn(bool lightOn);

	bool inUsed() const;

private:
	friend class Lights;
	void setInUsed(bool inUsed);

private:
	LightType mType;
	bool mLightOn;

	bool mInUsed;

public:
	FColor3 color;

	bool castShadow;
	MapSize mapSize;
	RenderTarget* map;
	mat4 matrix;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_LIGHT_H_ */
