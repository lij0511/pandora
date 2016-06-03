/*
 * Light.h
 *
 *  Created on: 2016年5月23日
 *      Author: lijing
 */

#ifndef POLA_LIGHT_H_
#define POLA_LIGHT_H_

#include "utils/RefBase.h"
#include "graphic/Color.h"
#include "graphic/math/Vector.h"

#define LIGHT_MAX_COUNT 8;

namespace pola {
namespace graphic {

class Light : public utils::RefBase<Light> {
public:

	enum LightType {
		//! point light, it has a position in space and radiates light in all directions
		LIGHT_POINT,
		//! spot light, it has a position in space, a direction, and a limited cone of influence
		LIGHT_SPOT,
		//! directional light, coming from a direction from an infinite distance
		LIGHT_DIRECTIONAL,
	};

	Light(const LightType type);
	virtual ~Light();

	void setAmbientColor(const FColor color);

	void setDiffuseColor(const FColor color);

	void setSpecularColor(const FColor color);

	const LightType lightType() const;

private:
	FColor m_ambientColor;
	FColor m_diffuseColor;
	FColor m_specularColor;

	const LightType m_type;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_LIGHT_H_ */
