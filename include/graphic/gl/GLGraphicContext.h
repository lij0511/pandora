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

	virtual void beginFrame(FColor clearColor);
	virtual void endFrame();

	virtual void setMaterial(const Material& material);

	virtual void renderMeshBuffer(MeshBuffer& meshBuffer);

protected:
	virtual Texture* doLoadTexture(io::InputStream* is);

private:
	GLCaches& mCaches;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_GLGRAPHICCONTEXT_H_ */
