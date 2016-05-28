/*
 * GL1xGraphicContext.h
 *
 *  Created on: 2016年5月29日
 *      Author: lijing
 */

#ifndef POLA_GL1XGRAPHICCONTEXT_H_
#define POLA_GL1XGRAPHICCONTEXT_H_

#include "graphic/gl/GL.h"
#include "graphic/GraphicContext.h"
#include "graphic/Matrix4.h"
#include "graphic/gl/GLTexture.h"

namespace pola {
namespace graphic {

class GL1xGraphicContext: public GraphicContext {
public:
	GL1xGraphicContext();
	virtual ~GL1xGraphicContext();

	virtual void setViewport(int32_t width, int32_t height);

	virtual void renderMeshBuffer(MeshBuffer& meshBuffer);

protected:
	virtual Texture* doLoadTexture(io::InputStream* is);
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_GL1XGRAPHICCONTEXT_H_ */
