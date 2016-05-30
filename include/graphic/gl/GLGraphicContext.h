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
#include "graphic/Matrix4.h"
#include "graphic/gl/GLTexture.h"

namespace pola {
namespace graphic {

class GLGraphicContext: public GraphicContext {
public:
	GLGraphicContext();
	virtual ~GLGraphicContext();

	virtual void setViewport(int32_t width, int32_t height);

	virtual void beginFrame();
	virtual void endFrame();

	virtual void renderMeshBuffer(MeshBuffer& meshBuffer);

protected:
	virtual Texture* doLoadTexture(io::InputStream* is);
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_GLGRAPHICCONTEXT_H_ */
