/*
 * Material.h
 *
 *  Created on: 2016年5月23日
 *      Author: lijing
 */

#ifndef POLA_MATERIAL_H_
#define POLA_MATERIAL_H_

#ifndef STRINGIFY
#define STRINGIFY(A)  #A
#endif

#if defined(POLA_GLES) || defined(POLA_GL)
#define OGL_RENDERER
#endif

#include "pola/utils/RefBase.h"
#include "pola/utils/String.h"
#include "pola/graphic/Program.h"
#include "pola/graphic/GraphicContext.h"
#include "pola/graphic/Color.h"
#include "pola/graphic/Texture.h"
#include "pola/graphic/BlendFunc.h"

namespace pola {
namespace graphic {

class Material : public utils::RefBase<Material> {
public:
	Material(const FColor4& color = {1.f, 1.f, 1.f, 1.f}, Texture* textureMap = nullptr);
	virtual ~Material();

	bool hasTextureMap() const;
	bool hasA8TextureMap() const;

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
	FColor4 mColor;
	Texture* mTextureMap;

public:
	bool mBlendEnable;
	BlendFunc mBlendFunc;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_MATERIAL_H_ */
