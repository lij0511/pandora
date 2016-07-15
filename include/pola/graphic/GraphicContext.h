/*
 * GraphicContext.h
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#ifndef POLA_GRAPHICCONTEXT_H_
#define POLA_GRAPHICCONTEXT_H_

#include <stdint.h>

#include "pola/graphic/geometries/Geometry2D.h"
#include "pola/graphic/geometries/Geometry3D.h"
#include "pola/graphic/math/Matrix4.h"
#include "pola/graphic/light/Lights.h"
#include "pola/graphic/Texture.h"
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

	virtual void beginFrame(const FColor4& clearColor);
	virtual void endFrame();

	void setLights(Lights* lights);
	Lights* lights() const;

	void setMatrix(MatrixType type, const mat4& matrix);

	virtual void renderGeometry(Geometry* geometry, Material* material = nullptr) = 0;

protected:
	virtual Texture* doLoadTexture(io::InputStream* is) = 0;

protected:
	mat4 mViewMatrix;
	mat4 mModelMatrix;
	mat4 mProjectionMatrix;

	Material* mDefaultMaterial;
	Lights* mLights;
private:
	int32_t mWidth;
	int32_t mHeight;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_GRAPHICCONTEXT_H_ */