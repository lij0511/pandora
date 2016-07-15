/*
 * ShaderMaterial.h
 *
 *  Created on: 2016年6月16日
 *      Author: lijing
 */

#ifndef SHADERMATERIAL_H_
#define SHADERMATERIAL_H_

#include "pola/graphic/material/Material.h"

namespace pola {
namespace graphic {

/*
 *
 */
class ShaderMaterial: public Material {
public:
	ShaderMaterial();
	virtual ~ShaderMaterial();

protected:
	virtual const utils::String generateVertexShader() = 0;
	virtual const utils::String generateFragmentShader() = 0;

	virtual bool isShaderMaterial() const;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* SHADERMATERIAL_H_ */
