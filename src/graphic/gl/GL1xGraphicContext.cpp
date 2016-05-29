/*
 * GL1xGraphicContext.cpp
 *
 *  Created on: 2016年5月29日
 *      Author: lijing
 */

#include "graphic/gl/GL1xGraphicContext.h"
#include "graphic/BitmapFactory.h"

namespace pola {
namespace graphic {

GL1xGraphicContext::GL1xGraphicContext() {
	glEnable(GL_DEPTH_TEST);
	glDepthMask(true);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);
	glEnable(GL_DITHER);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
}

GL1xGraphicContext::~GL1xGraphicContext() {
}

void GL1xGraphicContext::setViewport(int32_t width, int32_t height) {
	GraphicContext::setViewport(width, height);
	glViewport(0, 0, width, height);
}

void GL1xGraphicContext::renderMeshBuffer(MeshBuffer& meshBuffer) {
	if (meshBuffer.getVertexCount() == 0) {
		return;
	}

	static float x;
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(M_PI / 2.5f, 1.0f, 0, 3000);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gluLookAt(0, 0, 50, 0, 0, 49, 0, 1, 0);
glTranslated(0, 0, -5000);
glRotated(x ++, 0, 1, 0);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glColor4f(1, 0, 0, 1);
	if (meshBuffer.m_vertexInfo.offset_texcoord >= 0) {
		glTexCoordPointer(2, GL_FLOAT, meshBuffer.m_vertexInfo.item_size, ((GLbyte*) meshBuffer.getVertexBuffer() + meshBuffer.m_vertexInfo.offset_texcoord));
	}
	glVertexPointer(meshBuffer.m_vertexInfo.count_position, GL_FLOAT, meshBuffer.m_vertexInfo.item_size, ((GLbyte*) meshBuffer.getVertexBuffer() + meshBuffer.m_vertexInfo.offset_position));
	if (meshBuffer.m_vertexInfo.offset_normal >= 0) {
		glNormalPointer(GL_FLOAT, meshBuffer.m_vertexInfo.item_size, ((GLbyte*) meshBuffer.getVertexBuffer() + meshBuffer.m_vertexInfo.offset_normal));
	}
	if (meshBuffer.getIndexCount() > 0) {
		glDrawElements(GL_TRIANGLES, meshBuffer.getIndexCount(), GL_UNSIGNED_SHORT, meshBuffer.getIndexBuffer());
	} else {
		glDrawArrays(GL_TRIANGLE_STRIP, 0, meshBuffer.getVertexCount());
	}
}

Texture* GL1xGraphicContext::doLoadTexture(io::InputStream* is) {
	Bitmap* bitmap = BitmapFactory::decodeStream(is);
	if (bitmap == nullptr) {
		return nullptr;
	}
	/**
	 * Deferred texture generation. Generated when prepare to render.
	 */
	GLTexture* texture = new GLTexture;
	texture->m_bitmap = bitmap;

	return texture;
}

} /* namespace graphic */
} /* namespace pola */
