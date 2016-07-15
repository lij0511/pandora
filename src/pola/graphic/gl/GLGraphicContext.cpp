/*
 * GLGraphicContext.cpp
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#include "pola/graphic/gl/GLGraphicContext.h"
#include "pola/graphic/BitmapFactory.h"
#include "pola/graphic/gl/GLShaderLib.h"

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
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
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
	glClearDepthf(1.0f);
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
	description.texture_map = material->hasTextureMap();
	GLProgram* program = mCaches.programCache.get(description);
	if (!program) {
		utils::String vs;
		if (material->hasTextureMap()) {
			vs += "#define TEXTURE_MAP\n";
		}
		vs += GLShaderLib::VS_MainUnifroms();
		vs += GLShaderLib::VS_MainAttributes();
		vs += material->getVertexShader();
		utils::String fs;
		if (mLights && mLights->directionalLightCount() > 0) {
			char buf[40];
			sprintf(buf, "#define NUM_DIR_LIGHTS %lu\n", mLights->directionalLightCount());
			fs = buf;
		}
		if (material->hasTextureMap()) {
			fs += "#define TEXTURE_MAP\n";
		}
		fs += material->getFragmentShader().characters();
		program = new GLProgram(vs.characters(), fs.characters());
		mCaches.programCache.cache(description, program);
	}
	return program;
}

void GLGraphicContext::renderGeometry(Geometry* geometry, Material* material) {
	if (geometry->type() == Geometry::Type::GEOMETRY_3D) {
		renderGeometry((Geometry3D*) geometry, material);
	} else if (geometry->type() == Geometry::Type::GEOMETRY_2D) {
		renderGeometry((Geometry2D*) geometry, material);
	}
}

void GLGraphicContext::renderGeometry(Geometry2D* geometry, Material* material) {
	size_t positionCount = geometry->positionCount();
	if (positionCount == 0) {
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

	GLint a_position;
	if (program->fetchAttribute(utils::String("a_position", true), a_position)) {
		glEnableVertexAttribArray(a_position);
		glVertexAttribPointer(a_position, 2, GL_FLOAT, GL_FALSE, sizeof(graphic::vec2), ((GLbyte*) geometry->positions()));
	}
	GLint a_uv;
	if (geometry->uvCount() >= positionCount && program->fetchAttribute(utils::String("a_uv", true), a_uv)) {
		glEnableVertexAttribArray(a_uv);
		glVertexAttribPointer(a_uv, 2, GL_FLOAT, GL_FALSE, sizeof(graphic::vec2), ((GLbyte*) geometry->uvs()));
	}
	if (geometry->indexCount() > 0) {
		glDrawElements(GL_TRIANGLES, geometry->indexCount(), GL_UNSIGNED_SHORT, (const GLvoid*) geometry->indices());
	} else {
		glDrawArrays(GL_TRIANGLES, 0, positionCount);
	}
}

void GLGraphicContext::renderGeometry(Geometry3D* geometry, Material* material) {
	size_t positionCount = geometry->positionCount();
	if (positionCount == 0) {
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

	GLint a_position;
	if (program->fetchAttribute(utils::String("a_position", true), a_position)) {
		glEnableVertexAttribArray(a_position);
		glVertexAttribPointer(a_position, 3, GL_FLOAT, GL_FALSE, sizeof(graphic::vec3), ((GLbyte*) geometry->positions()));
	}
	GLint a_uv;
	if (geometry->uvCount() >= positionCount && program->fetchAttribute(utils::String("a_uv", true), a_uv)) {
		glEnableVertexAttribArray(a_uv);
		glVertexAttribPointer(a_uv, 2, GL_FLOAT, GL_FALSE, sizeof(graphic::vec2), ((GLbyte*) geometry->uvs()));
	}
	GLint a_normal;
	if (geometry->normalCount() >= positionCount && program->fetchAttribute(utils::String("a_normal", true), a_normal)) {
		glEnableVertexAttribArray(a_normal);
		glVertexAttribPointer(a_normal, 3, GL_FLOAT, GL_FALSE, sizeof(graphic::vec3), ((GLbyte*) geometry->normals()));
	}
	if (geometry->indexCount() > 0) {
		glDrawElements(GL_TRIANGLES, geometry->indexCount(), GL_UNSIGNED_SHORT, (const GLvoid*) geometry->indices());
	} else {
		glDrawArrays(GL_TRIANGLES, 0, positionCount);
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
//	texture->mipMap = true;
	texture->mBitmap = bitmap;

	return texture;
}

} /* namespace graphic */
} /* namespace pola */
