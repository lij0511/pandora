/*
 * PhongMaterial.h
 *
 *  Created on: 2016年6月19日
 *      Author: lijing
 */

#ifndef POLA_PHONGMATERIAL_H_
#define POLA_PHONGMATERIAL_H_

#include "graphic/material/Material.h"

namespace pola {
namespace graphic {

class PhongMaterial: public Material {
public:
	PhongMaterial(const FColor3& color = {1.f, 1.f, 1.f}, Texture* textureMap = nullptr);
	virtual ~PhongMaterial();

	void bind(GraphicContext* graphic, Program* program);

protected:
	virtual const utils::String generateVertexShader();
	virtual const utils::String generateFragmentShader();
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_PHONGMATERIAL_H_ */
