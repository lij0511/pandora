/*
 * GLGraphicContext.cpp
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#include "graphic/gl/GLGraphicContext.h"
#include "graphic/gl/DefaultGLShader.h"
#include "graphic/BitmapFactory.h"

namespace pola {
namespace graphic {

GLGraphicContext::GLGraphicContext() {
	glEnable(GL_DEPTH_TEST);
	glDepthMask(true);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_DITHER);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
}

GLGraphicContext::~GLGraphicContext() {
}

void GLGraphicContext::setViewport(int32_t width, int32_t height) {
	GraphicContext::setViewport(width, height);
	glViewport(0, 0, width, height);
}

void GLGraphicContext::renderMeshBuffer(MeshBuffer& meshBuffer) {
	if (meshBuffer.getVertexCount() == 0) {
		return;
	}

	static GLShader* shader = new DefaultGLShader;
	shader->invalidate();
//	static GLShader* shader = new GLShader;
	shader->makeCurrent();
	mat4 m = m_camera;
//	m.translate(0, 0, -100);
	shader->setMatrix("u_MVPMatrix", m);

	GLint a_texCoords;
	if (meshBuffer.m_vertexInfo.offset_texcoord >= 0 && shader->fetchAttribute("a_texCoords", a_texCoords)) {
		glEnableVertexAttribArray(a_texCoords);
		glVertexAttribPointer(a_texCoords, 2, GL_FLOAT, GL_FALSE, meshBuffer.m_vertexInfo.item_size, ((GLbyte*) meshBuffer.getVertexBuffer() + meshBuffer.m_vertexInfo.offset_texcoord));
	}
	GLint a_position;
	if (shader->fetchAttribute("a_position", a_position)) {
		glEnableVertexAttribArray(a_position);
		glVertexAttribPointer(a_position, meshBuffer.m_vertexInfo.count_position, GL_FLOAT, GL_FALSE, meshBuffer.m_vertexInfo.item_size, ((GLbyte*) meshBuffer.getVertexBuffer() + meshBuffer.m_vertexInfo.offset_position));
	}
	GLint a_normal;
	if (meshBuffer.m_vertexInfo.offset_normal >= 0 && shader->fetchAttribute("a_normal", a_normal)) {
		glEnableVertexAttribArray(a_normal);
		glVertexAttribPointer(a_normal, meshBuffer.m_vertexInfo.count_normal, GL_FLOAT, GL_FALSE, meshBuffer.m_vertexInfo.item_size, ((GLbyte*) meshBuffer.getVertexBuffer() + meshBuffer.m_vertexInfo.offset_normal));
	}
	if (meshBuffer.getIndexCount() > 0) {
		glDrawElements(GL_TRIANGLES, meshBuffer.getIndexCount(), GL_UNSIGNED_SHORT, meshBuffer.getIndexBuffer());
	} else {
		glDrawArrays(GL_TRIANGLE_STRIP, 0, meshBuffer.getVertexCount());
	}
}

Texture* GLGraphicContext::doLoadTexture(io::InputStream* is) {
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
