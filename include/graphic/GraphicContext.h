/*
 * GraphicContext.h
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#ifndef POLA_GRAPHICCONTEXT_H_
#define POLA_GRAPHICCONTEXT_H_

#include <stdint.h>

#include "scene/mesh/MeshBuffer.h"
#include "graphic/Matrix4.h"

namespace pola {
namespace graphic {


class GraphicContext {
public:
	GraphicContext();
	virtual ~GraphicContext();

	virtual void setViewport(int32_t width, int32_t height);

	void setCurrentCamera(const mat4& projection, const mat4& view);

	virtual void renderMeshBuffer(scene::MeshBuffer& meshBuffer) = 0;

protected:
	mat4 m_projection;
	mat4 m_view;
private:
	int32_t m_width;
	int32_t m_height;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_GRAPHICCONTEXT_H_ */
