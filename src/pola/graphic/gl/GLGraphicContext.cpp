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

static GLenum GLDrawMode(GraphicParameter::DrawMode d) {
	switch (d) {
	case GraphicParameter::DrawMode::TRIANGLES:
		return GL_TRIANGLES;
	case GraphicParameter::DrawMode::TRIANGLE_FAN:
		return GL_TRIANGLE_FAN;
	case GraphicParameter::DrawMode::TRIANGLE_STRIP:
		return GL_TRIANGLE_STRIP;
	case GraphicParameter::DrawMode::LINES:
		return GL_LINES;
	case GraphicParameter::DrawMode::LINE_LOOP:
		return GL_LINE_LOOP;
	case GraphicParameter::DrawMode::LINE_STRIP:
		return GL_LINE_STRIP;
	case GraphicParameter::DrawMode::POINTS:
		return GL_POINTS;
	default:
		return GL_TRIANGLES;
	}
}

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
	description.texture_map_a8 = material->hasA8TextureMap();
	description.directional_light_count = mLights ? mLights->directionalLightCount() : 0;
	description.point_light_count = mLights ? mLights->pointLightCount() : 0;
	description.spot_light_count = mLights ? mLights->spotLightCount() : 0;
	GLProgram* program = mCaches.programCache.get(description);
	if (!program) {
		utils::String vs;
		utils::String fs;
		if (mLights && mLights->directionalLightCount() > 0) {
			char buf[40];
			sprintf(buf, "#define NUM_DIR_LIGHTS %lu\n", mLights->directionalLightCount());
			vs = fs = buf;
		}
		if (material->hasTextureMap()) {
			vs += "#define TEXTURE_MAP\n";
			fs += "#define TEXTURE_MAP\n";
			if (material->hasA8TextureMap()) {
				vs += "#define TEXTURE_MAP_A8\n";
				fs += "#define TEXTURE_MAP_A8\n";
			}
		}
		vs += GLShaderLib::VS_MainUnifroms();
		vs += GLShaderLib::VS_MainAttributes();
		vs += material->getVertexShader();
		fs += material->getFragmentShader().characters();
		program = new GLProgram(vs.characters(), fs.characters());
		mCaches.programCache.cache(description, program);
	}
	return program;
}

void GLGraphicContext::renderGeometry(Geometry* geometry, Material* material) {
	renderGeometry(geometry, GraphicParameter(), material);
}

void GLGraphicContext::renderGeometry(Geometry* geometry, const GraphicParameter& parameter, Material* material) {
	if (geometry->type() == Geometry::Type::GEOMETRY_3D) {
		renderGeometry((Geometry3D*) geometry, parameter, material);
	} else if (geometry->type() == Geometry::Type::GEOMETRY_2D) {
		renderGeometry((Geometry2D*) geometry, parameter, material);
	}
}

void GLGraphicContext::renderGeometry(Geometry2D* geometry, const GraphicParameter& parameter, Material* material) {
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
		glDrawElements(GLDrawMode(parameter.drawMode), geometry->indexCount(), GL_UNSIGNED_SHORT, (const GLvoid*) geometry->indices());
	} else {
		glDrawArrays(GLDrawMode(parameter.drawMode), 0, positionCount);
	}
}

void GLGraphicContext::renderGeometry(Geometry3D* geometry, const GraphicParameter& parameter, Material* material) {
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
		glDrawElements(GLDrawMode(parameter.drawMode), geometry->indexCount(), GL_UNSIGNED_SHORT, (const GLvoid*) geometry->indices());
	} else {
		glDrawArrays(GLDrawMode(parameter.drawMode), 0, positionCount);
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
	texture->width = bitmap->getWidth();
	texture->height = bitmap->getHeight();
	texture->format = bitmap->getFormat();

	return texture;
}

} /* namespace graphic */
} /* namespace pola */
