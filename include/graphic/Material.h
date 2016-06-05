/*
 * Material.h
 *
 *  Created on: 2016年5月23日
 *      Author: lijing
 */

#ifndef POLA_MATERIAL_H_
#define POLA_MATERIAL_H_

#include "graphic/Color.h"

namespace pola {
namespace graphic {

class Material {
public:
	Material();
	virtual ~Material();

private:
	Color mAmbientColor;
	Color mDiffuseColor;
	Color mSpecularColor;
	float mShininess;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_MATERIAL_H_ */
