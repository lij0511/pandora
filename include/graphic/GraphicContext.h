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
#include "graphic/Matrix4.h"
#include "graphic/Texture.h"
#include "io/InputStream.h"

namespace pola {
namespace graphic {


class GraphicContext {
public:
	GraphicContext();
	virtual ~GraphicContext();

	virtual void setViewport(int32_t width, int32_t height);

	Texture* loadTexture(const char* file);
	Texture* loadTexture(io::InputStream* is);

	void setCurrentCamera(const mat4& projection);

	virtual void renderMeshBuffer(MeshBuffer& meshBuffer) = 0;

protected:
	virtual Texture* doLoadTexture(io::InputStream* is) = 0;

protected:
	mat4 m_camera;
private:
	int32_t m_width;
	int32_t m_height;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_GRAPHICCONTEXT_H_ */
