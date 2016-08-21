/*
 * ShadowMapMaterial.h
 *
 *  Created on: 2016年8月3日
 *      Author: lijing
 */

#ifndef POLA_SHADOWMAPMATERIAL_H_
#define POLA_SHADOWMAPMATERIAL_H_

#include "pola/graphic/material/ShaderMaterial.h"

namespace pola {
namespace graphic {

/*
 *
 */
class ShadowMapMaterial: public ShaderMaterial {
public:
	ShadowMapMaterial();
	virtual ~ShadowMapMaterial();

protected:
	virtual const utils::String generateVertexShader();;
	virtual const utils::String generateFragmentShader();

};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_SHADOWMAPMATERIAL_H_ */
