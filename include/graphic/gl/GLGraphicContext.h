/*
 * GLGraphicContext.h
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#ifndef POLA_GLGRAPHICCONTEXT_H_
#define POLA_GLGRAPHICCONTEXT_H_

#include "graphic/gl/GL.h"
#include "graphic/GraphicContext.h"
#include "graphic/Material.h"
#include "graphic/math/Matrix4.h"
#include "graphic/gl/GLTexture.h"
#include "graphic/gl/GLCaches.h"

namespace pola {
namespace graphic {

class GLGraphicContext: public GraphicContext {
public:
	GLGraphicContext();
	virtual ~GLGraphicContext();

	virtual void setViewport(int32_t width, int32_t height);

	virtual void beginFrame(const FColor& clearColor);
	virtual void endFrame();

	virtual void renderMeshBuffer(MeshBuffer& meshBuffer, Material* material = nullptr);

protected:
	virtual Texture* doLoadTexture(io::InputStream* is);

private:
	GLProgram* currentProgram(Material* material);

	GLCaches& mCaches;

	Material* mDefaultMaterial;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_GLGRAPHICCONTEXT_H_ */
