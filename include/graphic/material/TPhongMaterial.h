/*
 * TPhongMaterial.h
 *
 *  Created on: 2016年6月19日
 *      Author: lijing
 */

#ifndef POLA_TPHONGMATERIAL_H_
#define POLA_TPHONGMATERIAL_H_

#include "graphic/material/TMaterial.h"

namespace pola {
namespace graphic {

class TPhongMaterial: public TMaterial {
public:
	TPhongMaterial(Texture* texture);
	virtual ~TPhongMaterial();

	void bind(GraphicContext* graphic, Program* program);

protected:
	virtual const utils::String generateVertexShader();
	virtual const utils::String generateFragmentShader();
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_TPHONGMATERIAL_H_ */
