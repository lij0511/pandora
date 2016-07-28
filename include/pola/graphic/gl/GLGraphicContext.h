/*
 * GLGraphicContext.h
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#ifndef POLA_GLGRAPHICCONTEXT_H_
#define POLA_GLGRAPHICCONTEXT_H_

#include "pola/graphic/gl/GL.h"
#include "pola/graphic/GraphicContext.h"
#include "pola/graphic/material/Material.h"
#include "pola/graphic/math/Matrix4.h"
#include "pola/graphic/gl/GLTexture.h"
#include "pola/graphic/gl/GLCaches.h"

namespace pola {
namespace graphic {

class GLGraphicContext: public GraphicContext {
public:
	GLGraphicContext();
	virtual ~GLGraphicContext();

	virtual void setViewport(int32_t width, int32_t height);

	virtual void beginFrame(const FColor4& clearColor = {0.f, 0.f, 0.f, 0.f});
	virtual void endFrame();

	virtual void renderGeometry(Geometry* geometry, Material* material = nullptr);
	virtual void renderGeometry(Geometry* geometry, const GraphicParameter& parameter, Material* material = nullptr);

protected:
	void renderGeometry(Geometry2D* geometry, const GraphicParameter& parameter, Material* material = nullptr);
	void renderGeometry(Geometry3D* geometry, const GraphicParameter& parameter, Material* material = nullptr);

	virtual Texture* doLoadTexture(io::InputStream* is);

private:
	GLProgram* currentProgram(Material* material);

	GLCaches& mCaches;

};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_GLGRAPHICCONTEXT_H_ */
