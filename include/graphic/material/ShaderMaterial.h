/*
 * ShaderMaterial.h
 *
 *  Created on: 2016年6月16日
 *      Author: lijing
 */

#ifndef SHADERMATERIAL_H_
#define SHADERMATERIAL_H_

#include "graphic/Material.h"

namespace pola {
namespace graphic {

/*
 *
 */
class ShaderMaterial: public Material {
public:
	ShaderMaterial();
	virtual ~ShaderMaterial();
};

} /* namespace graphic */
} /* namespace pola */

#endif /* SHADERMATERIAL_H_ */
