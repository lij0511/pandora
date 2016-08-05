/*
 * GraphicContext.h
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#ifndef POLA_GRAPHICCONTEXT_H_
#define POLA_GRAPHICCONTEXT_H_

#include <stdint.h>

#include "pola/graphic/PixelFormat.h"
#include "pola/graphic/GraphicParameter.h"
#include "pola/graphic/geometries/Geometry2D.h"
#include "pola/graphic/geometries/Geometry3D.h"
#include "pola/graphic/math/Matrix4.h"
#include "pola/graphic/light/Lights.h"
#include "pola/graphic/Texture.h"
#include "pola/graphic/RenderTarget.h"
#include "pola/io/InputStream.h"

namespace pola {
namespace graphic {
class Material;

class GraphicContext {
public:
	enum MatrixType {
		VIEW,
		MODEL,
		MODEL_VIEW,
		PROJECTION,
	};
	GraphicContext();
	virtual ~GraphicContext();

	virtual void setViewport(int32_t width, int32_t height);

	Texture* loadTexture(const char* file);

	virtual RenderTarget* createRenderTarget(uint32_t width, uint32_t height, PixelFormat format = PixelFormat::RGBA8888) = 0;

	virtual void setRenderTarget(RenderTarget* renderTarget);

	virtual void beginFrame(const FColor4& clearColor = {0.f, 0.f, 0.f, 0.f});
	virtual void endFrame();

	virtual void clear(const FColor4& clearColor = {0.f, 0.f, 0.f, 0.f}, bool depth = true);

	void setLights(Lights* lights);
	Lights* lights() const;

	void setMatrix(MatrixType type, const mat4& matrix);
	mat4 getMatrix(MatrixType type);

	virtual void renderGeometry(Geometry* geometry, const GraphicParameter& parameter, Material* material = nullptr) = 0;
	virtual void renderGeometry(Geometry* geometry, Material* material = nullptr) = 0;

protected:
	virtual Texture* doLoadTexture(io::InputStream* is) = 0;

protected:
	mat4 mViewMatrix;
	mat4 mModelMatrix;
	mat4 mProjectionMatrix;

	Material* mDefaultMaterial;
	Lights* mLights;
protected:
	int32_t mWidth;
	int32_t mHeight;

	RenderTarget* mRenderTarget;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_GRAPHICCONTEXT_H_ */
