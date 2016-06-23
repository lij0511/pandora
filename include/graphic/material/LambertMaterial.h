/*
 * LambertMaterial.h
 *
 *  Created on: 2016年6月23日
 *      Author: lijing
 */

#ifndef POLA_LAMBERTMATERIAL_H_
#define POLA_LAMBERTMATERIAL_H_

#include "graphic/material/Material.h"

namespace pola {
namespace graphic {

class LambertMaterial: public Material {
public:
	LambertMaterial(const FColor3& color = {1.f, 1.f, 1.f}, Texture* textureMap = nullptr);
	virtual ~LambertMaterial();

	void bind(GraphicContext* graphic, Program* program);

protected:
	virtual const utils::String generateVertexShader();
	virtual const utils::String generateFragmentShader();
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_LAMBERTMATERIAL_H_ */
