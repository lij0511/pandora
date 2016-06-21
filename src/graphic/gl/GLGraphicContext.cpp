/*
 * GLGraphicContext.cpp
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#include "graphic/gl/GLGraphicContext.h"
#include "graphic/BitmapFactory.h"
#include "graphic/gl/GLShaderLib.h"

namespace pola {
namespace graphic {

GLGraphicContext::GLGraphicContext() : mCaches(GLCaches::get()) {
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

void GLGraphicContext::beginFrame(const FColor4& clearColor) {
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLGraphicContext::endFrame() {
}

GLProgram* GLGraphicContext::currentProgram(Material* material) {
	ProgramDescription description(material->getMaterialType());
	if (!description.material_type) {
		description.mVertexShader = material->getVertexShader();
		description.mFragmentShader = material->getFragmentShader();
	}
	GLProgram* program = mCaches.programCache.get(description);
	if (!program) {
		utils::String vs = GLShaderLib::VS_MainUnifroms();
		vs += GLShaderLib::VS_MainAttributes();
		vs += material->getVertexShader();
		utils::String fs;
		if (mLights && mLights->directionalLightCount() > 0) {
			char buf[40];
			sprintf(buf, "#define NUM_DIR_LIGHTS %lu\n", mLights->directionalLightCount());
			fs = buf;
		}
		fs += material->getFragmentShader().characters();
		program = new GLProgram(vs.characters(), fs.characters());
		mCaches.programCache.cache(description, program);
	}
	return program;
}

void GLGraphicContext::renderMeshBuffer(MeshBuffer& meshBuffer, Material* material) {
	if (meshBuffer.getVertexCount() == 0) {
		return;
	}
	if (material == nullptr) {
		material = mDefaultMaterial;
	}

	GLProgram* program = currentProgram(material);
	program->use();

	GLint u_mat;
	if (program->fetchUniform(utils::String("u_projection", true), u_mat)) {
		glUniformMatrix4fv(u_mat, 1, GL_FALSE, &mProjectionMatrix.data[0]);
	}
	if (program->fetchUniform(utils::String("u_view", true), u_mat)) {
		glUniformMatrix4fv(u_mat, 1, GL_FALSE, &mViewMatrix.data[0]);
	}
	if (program->fetchUniform(utils::String("u_model", true), u_mat)) {
		glUniformMatrix4fv(u_mat, 1, GL_FALSE, &mModelMatrix.data[0]);
	}

	material->bind(this, program);

	GLint a_uv;
	if (meshBuffer.m_vertexInfo.offset_texcoord >= 0 && program->fetchAttribute(utils::String("a_uv", true), a_uv)) {
		glEnableVertexAttribArray(a_uv);
		glVertexAttribPointer(a_uv, 2, GL_FLOAT, GL_FALSE, meshBuffer.m_vertexInfo.item_size, ((GLbyte*) meshBuffer.getVertexBuffer() + meshBuffer.m_vertexInfo.offset_texcoord));
	}
	GLint a_position;
	if (program->fetchAttribute(utils::String("a_position", true), a_position)) {
		glEnableVertexAttribArray(a_position);
		glVertexAttribPointer(a_position, meshBuffer.m_vertexInfo.count_position, GL_FLOAT, GL_FALSE, meshBuffer.m_vertexInfo.item_size, ((GLbyte*) meshBuffer.getVertexBuffer() + meshBuffer.m_vertexInfo.offset_position));
	}
	GLint a_normal;
	if (meshBuffer.m_vertexInfo.offset_normal >= 0 && program->fetchAttribute(utils::String("a_normal", true), a_normal)) {
		glEnableVertexAttribArray(a_normal);
		glVertexAttribPointer(a_normal, meshBuffer.m_vertexInfo.count_normal, GL_FLOAT, GL_FALSE, meshBuffer.m_vertexInfo.item_size, ((GLbyte*) meshBuffer.getVertexBuffer() + meshBuffer.m_vertexInfo.offset_normal));
	}
	if (meshBuffer.getIndexCount() > 0) {
		glDrawElements(GL_TRIANGLES, meshBuffer.getIndexCount(), GL_UNSIGNED_SHORT, meshBuffer.getIndexBuffer());
//		glDrawElements(GL_LINES, meshBuffer.getIndexCount(), GL_UNSIGNED_SHORT, meshBuffer.getIndexBuffer());
//		glDrawArrays(GL_LINES, 0, meshBuffer.getVertexCount());
	} else {
		glDrawArrays(GL_TRIANGLES, 0, meshBuffer.getVertexCount());
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
