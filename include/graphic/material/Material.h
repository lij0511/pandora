/*
 * Material.h
 *
 *  Created on: 2016年5月23日
 *      Author: lijing
 */

#ifndef POLA_MATERIAL_H_
#define POLA_MATERIAL_H_

// TODO
#define OGL_RENDERER

#include "utils/RefBase.h"
#include "utils/String.h"
#include "graphic/Program.h"
#include "graphic/GraphicContext.h"
#include "graphic/Color.h"
#include "graphic/Texture.h"

namespace pola {
namespace graphic {

class Material : public utils::RefBase<Material> {
public:
	Material(const FColor3& color = {1.f, 1.f, 1.f}, Texture* textureMap = nullptr);
	virtual ~Material();

	bool hasTextureMap() const;

	const utils::String getVertexShader();
	const utils::String getFragmentShader();

	virtual void bind(GraphicContext* graphic, Program* program);

	const char* getMaterialType() const;

protected:
	virtual const utils::String generateVertexShader();
	virtual const utils::String generateFragmentShader();

	virtual bool isShaderMaterial() const;

	utils::String mVertexShader;
	utils::String mFragmentShader;

protected:
	FColor3 mColor;
	Texture* mTextureMap;

};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_MATERIAL_H_ */
