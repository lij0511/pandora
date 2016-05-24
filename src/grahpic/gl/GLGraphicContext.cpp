/*
 * GLGraphicContext.cpp
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#include "graphic/gl/GLGraphicContext.h"
#include "graphic/gl/GLShader.h"

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

	static GLShader* shader = new GLShader;
	shader->makeCurrent();
	m_view.translate(0, 0, -50);
	mat4 m = m_projection;
	m.multiply(m_view);
	shader->set(m);
	GLint u_color;
	if (shader->fetchUniform("u_color", u_color)) {
		glUniform4f(u_color, 1.0f, 1.0f, 1.0f, 1.0f);
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

} /* namespace graphic */
} /* namespace pola */
