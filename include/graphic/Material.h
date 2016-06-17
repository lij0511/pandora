/*
 * Material.h
 *
 *  Created on: 2016年5月23日
 *      Author: lijing
 */

#ifndef POLA_MATERIAL_H_
#define POLA_MATERIAL_H_

#include "utils/String.h"
#include "graphic/Program.h"

namespace pola {
namespace graphic {

class Material {
public:
	Material();
	virtual ~Material();

	const utils::String getVertexShader();
	const utils::String getFragmentShader();

	virtual void bind(Program* program);

	const char* getMaterialType() const;

protected:
	virtual const utils::String generateVertexShader() = 0;
	virtual const utils::String generateFragmentShader() = 0;

	virtual bool isShaderMaterial() const;

	utils::String mVertexShader;
	utils::String mFragmentShader;

};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_MATERIAL_H_ */
