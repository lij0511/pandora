/*
 * Material.h
 *
 *  Created on: 2016年5月23日
 *      Author: lijing
 */

#ifndef POLA_MATERIAL_H_
#define POLA_MATERIAL_H_

#include "graphic/Color.h"
#include "graphic/Texture.h"

namespace pola {
namespace graphic {

class Material {
public:
	Material();
	virtual ~Material();

	void setTexture(uint32_t i, Texture* texture);
	Texture* getTexture(uint32_t i) const;

private:
	Texture* mTextures[MAX_TEXTURE_UNITS_COUNT];

	FColor mAmbientColor;
	FColor mDiffuseColor;
	FColor mEmissiveColor;
	FColor mSpecularColor;
	float mShininess;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_MATERIAL_H_ */
