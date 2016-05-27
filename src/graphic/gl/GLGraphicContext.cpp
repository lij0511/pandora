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
}

GLGraphicContext::~GLGraphicContext() {
}

void GLGraphicContext::setViewport(int32_t width, int32_t height) {
	GraphicContext::setViewport(width, height);
	glViewport(0, 0, width, height);
}

void GLGraphicContext::renderMeshBuffer(scene::MeshBuffer& meshBuffer) {
	if (meshBuffer.getVertexCount() == 0) {
		return;
	}

	static DefaultGLShader* shader = new DefaultGLShader;
	shader->invalidate();
//	static GLShader* shader = new GLShader;
	shader->makeCurrent();
	mat4 m = m_camera;
//	m.translate(0, 0, -100);
//	m.rotate(90, 0, 1, 0);
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
