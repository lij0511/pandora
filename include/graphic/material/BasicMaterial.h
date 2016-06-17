/*
 * BasicMaterial.h
 *
 *  Created on: 2016年6月16日
 *      Author: lijing
 */

#ifndef BASICMATERIAL_H_
#define BASICMATERIAL_H_

#include "graphic/Material.h"
#include "graphic/Color.h"

namespace pola {
namespace graphic {

/*
 *
 */
class BasicMaterial: public Material {
public:
	BasicMaterial(const FColor& color = {1.f, 1.f, 1.f, 1.f});
	virtual ~BasicMaterial();

	virtual void bind(Program* program);

protected:
	virtual const utils::String generateVertexShader();
	virtual const utils::String generateFragmentShader();

protected:
	FColor mColor;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* BASICMATERIAL_H_ */
