/*
 * GraphicContext.h
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#ifndef POLA_GRAPHICCONTEXT_H_
#define POLA_GRAPHICCONTEXT_H_

#include <stdint.h>

#include "graphic/MeshBuffer.h"
#include "graphic/math/Matrix4.h"
#include "graphic/light/Lights.h"
#include "graphic/Texture.h"
#include "io/InputStream.h"

namespace pola {
namespace graphic {
class Material;

class GraphicContext {
public:
	enum MatrixType {
		VIEW,
		WORLD,
		PROJECTION,
	};
	GraphicContext();
	virtual ~GraphicContext();

	virtual void setViewport(int32_t width, int32_t height);

	Texture* loadTexture(const char* file);
	Texture* loadTexture(io::InputStream* is);

	virtual void beginFrame(const FColor4& clearColor);
	virtual void endFrame();

	void setLights(const Lights& lights);
	const Lights& lights() const;

	void setMatrix(MatrixType type, const mat4& matrix);

	virtual void renderMeshBuffer(MeshBuffer& meshBuffer, Material* material = nullptr) = 0;

protected:
	virtual Texture* doLoadTexture(io::InputStream* is) = 0;

protected:
	mat4 mView;
	mat4 mWorld;
	mat4 mProjection;

	Material* mDefaultMaterial;
	Lights mLights;
private:
	int32_t mWidth;
	int32_t mHeight;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_GRAPHICCONTEXT_H_ */
