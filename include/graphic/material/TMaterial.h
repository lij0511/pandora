/*
 * TMaterial.h
 *
 *  Created on: 2016年6月18日
 *      Author: lijing
 */

#ifndef TMATERIAL_H_
#define TMATERIAL_H_

#include "graphic/Material.h"
#include "graphic/Texture.h"

namespace pola {
namespace graphic {

/*
 *
 */
class TMaterial: public Material {
public:
	TMaterial(Texture* texture);
	virtual ~TMaterial();

	virtual void bind(Program* program);

protected:
	virtual const utils::String generateVertexShader();
	virtual const utils::String generateFragmentShader();

protected:
	Texture* mTexture;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* TMATERIAL_H_ */
