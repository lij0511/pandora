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

static utils::String projection("u_projection");
static utils::String view("u_view");
static utils::String model("u_model");
static utils::String position("a_position");
static utils::String uv("a_uv");
static utils::String normal("a_normal");

static GLenum GLDrawMode(GraphicParameter::DrawMode d) {
	return d;
}

GLGraphicContext::GLGraphicContext() : mCaches(GLCaches::get()) {
	glEnable(GL_DEPTH_TEST);
	glDepthMask(true);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
//	glEnable(GL_DITHER);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
}

GLGraphicContext::~GLGraphicContext() {
}

void GLGraphicContext::setViewport(int32_t width, int32_t height) {
	GraphicContext::setViewport(width, height);
	glViewport(0, 0, width, height);
}

RenderTarget* GLGraphicContext::createRenderTarget(uint32_t width, uint32_t height, PixelFormat format) {
	return new GLRenderTarget(width, height, format);
}

void GLGraphicContext::setRenderTarget(RenderTarget* renderTarget) {
	GLRenderTarget* glRenderTarget = dynamic_cast<GLRenderTarget*>(renderTarget);
	GraphicContext::setRenderTarget(glRenderTarget);
	if (glRenderTarget == nullptr) {
		GLCaches::get().bindFrameBuffer(0);
		glViewport(0, 0, mWidth, mHeight);
	} else {
		GLCaches::get().bindFrameBuffer(glRenderTarget->getFrameBuffer());
		glViewport(0, 0, glRenderTarget->getWidth(), glRenderTarget->getHeight());
		glEnable(GL_DEPTH_TEST);
	}
}

void GLGraphicContext::beginFrame(const FColor4& clearColor) {
	clear(clearColor, true);
}

void GLGraphicContext::clear(const FColor4& clearColor, bool depth) {
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	if (depth) {
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	} else {
		glClear(GL_COLOR_BUFFER_BIT);
	}
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
	description.shadow_map = mLights ? mLights->shadowMap() : false;
	GLProgram* program = mCaches.programCache.get(description);
	if (!program) {
		utils::String vs;
		utils::String fs;
		if (mLights && mLights->directionalLightCount() > 0) {
			char buf[40];
			sprintf(buf, "#define NUM_DIR_LIGHTS %lu\n", mLights->directionalLightCount());
			vs = buf;
		}
		if (mLights && mLights->pointLightCount() > 0) {
			char buf[100];
			sprintf(buf, "#define NUM_POINT_LIGHTS %lu\n", mLights->pointLightCount());
			vs += buf;
		}
		if (mLights && mLights->shadowMap()) {
			vs += "#define USE_SHADOW_MAP\n";
//			vs += "#define SHADOWMAP_TYPE_PCF_SOFT\n";
		}
		if (material->hasTextureMap()) {
			vs += "#define TEXTURE_MAP\n";
			if (material->hasA8TextureMap()) {
				vs += "#define TEXTURE_MAP_A8\n";
			}
		}
		fs = vs;

		vs += GLShaderLib::VS_MainUnifroms();
		vs += GLShaderLib::VS_MainAttributes();
		vs += material->getVertexShader();
		fs += material->getFragmentShader();
		program = new GLProgram(vs.characters(), fs.characters());
		mCaches.programCache.cache(description, program);
	}
	return program;
}

void GLGraphicContext::renderGeometry(Geometry* geometry, uint32_t start, uint32_t end, Material* material) {
	renderGeometry(geometry, start, end, GraphicParameter(), material);
}

void GLGraphicContext::renderGeometry(Geometry* geometry, uint32_t start, uint32_t end, const GraphicParameter& parameter, Material* material) {
	if (geometry->type() == Geometry::Type::GEOMETRY_3D) {
		renderGeometry((Geometry3D*) geometry, start, end, parameter, material);
	} else if (geometry->type() == Geometry::Type::GEOMETRY_2D) {
		renderGeometry((Geometry2D*) geometry, start, end, parameter, material);
	}
}

void GLGraphicContext::renderGeometry(Geometry2D* geometry, uint32_t start, uint32_t end, const GraphicParameter& parameter, Material* material) {
	size_t positionCount = geometry->positionCount();
	if (positionCount == 0) {
		return;
	}
	if (material == nullptr) {
		material = mDefaultMaterial;
	}

	GLProgram* program = currentProgram(material);
	program->use();

	GLUniform* uniform;
	if ((uniform = program->fetchUniform("u_projection")) != nullptr) {
		glUniformMatrix4fv(uniform->location, 1, GL_FALSE, &mProjectionMatrix.data[0]);
	}
	if ((uniform = program->fetchUniform("u_view")) != nullptr) {
		glUniformMatrix4fv(uniform->location, 1, GL_FALSE, &mViewMatrix.data[0]);
	}
	if ((uniform = program->fetchUniform("u_model")) != nullptr) {
		glUniformMatrix4fv(uniform->location, 1, GL_FALSE, &mModelMatrix.data[0]);
	}

	material->bind(this, program);

	GLAttribute* attribute;
	if ((attribute = program->fetchAttribute("a_position")) != nullptr) {
		glEnableVertexAttribArray(attribute->location);
		glVertexAttribPointer(attribute->location, 2, GL_FLOAT, GL_FALSE, sizeof(graphic::vec2), ((GLbyte*) geometry->positions()));
	}
	if (geometry->uvCount() >= positionCount && (attribute = program->fetchAttribute("a_uv")) != nullptr) {
		glEnableVertexAttribArray(attribute->location);
		glVertexAttribPointer(attribute->location, 2, GL_FLOAT, GL_FALSE, sizeof(graphic::vec2), ((GLbyte*) geometry->uvs()));
	}
	if (geometry->indexCount() > 0) {
		if (start >= geometry->indexCount()) {
			start = geometry->indexCount() - 1;
		}
		if (end <= start) {
			end = geometry->indexCount();
		}
		glDrawElements(GLDrawMode(parameter.drawMode), end - start, GL_UNSIGNED_SHORT, (const GLvoid*) (geometry->indices() + start));
	} else {
		if (start >= positionCount) {
			start = positionCount - 1;
		}
		if (end <= start) {
			end = positionCount;
		}
		glDrawArrays(GLDrawMode(parameter.drawMode), start, end - start);
	}
	GLCaches::get().resetActiveTexture();
}

void GLGraphicContext::renderGeometry(Geometry3D* geometry, uint32_t start, uint32_t end, const GraphicParameter& parameter, Material* material) {
	size_t positionCount = geometry->positionCount();
	if (positionCount == 0) {
		return;
	}
	if (material == nullptr) {
		material = mDefaultMaterial;
	}

	GLProgram* program = currentProgram(material);
	program->use();

	GLUniform* uniform;
	if ((uniform = program->fetchUniform("u_projection")) != nullptr) {
		glUniformMatrix4fv(uniform->location, 1, GL_FALSE, &mProjectionMatrix.data[0]);
	}
	if ((uniform = program->fetchUniform("u_view")) != nullptr) {
		glUniformMatrix4fv(uniform->location, 1, GL_FALSE, &mViewMatrix.data[0]);
	}
	if ((uniform = program->fetchUniform("u_model")) != nullptr) {
		glUniformMatrix4fv(uniform->location, 1, GL_FALSE, &mModelMatrix.data[0]);
	}
	/*GLint u_mat;
	if (program->fetchUniform(projection, u_mat)) {
		glUniformMatrix4fv(u_mat, 1, GL_FALSE, &mProjectionMatrix.data[0]);
	}
	if (program->fetchUniform(view, u_mat)) {
		glUniformMatrix4fv(u_mat, 1, GL_FALSE, &mViewMatrix.data[0]);
	}
	if (program->fetchUniform(model, u_mat)) {
		glUniformMatrix4fv(u_mat, 1, GL_FALSE, &mModelMatrix.data[0]);
	}*/

	material->bind(this, program);

	GLAttribute* attribute;
	if ((attribute = program->fetchAttribute("a_position")) != nullptr) {
		glEnableVertexAttribArray(attribute->location);
		glVertexAttribPointer(attribute->location, 3, GL_FLOAT, GL_FALSE, sizeof(graphic::vec3), ((GLbyte*) geometry->positions()));
	}
	if (geometry->uvCount() >= positionCount && (attribute = program->fetchAttribute("a_uv")) != nullptr) {
		glEnableVertexAttribArray(attribute->location);
		glVertexAttribPointer(attribute->location, 2, GL_FLOAT, GL_FALSE, sizeof(graphic::vec2), ((GLbyte*) geometry->uvs()));
	}
	if (geometry->normalCount() >= positionCount && (attribute = program->fetchAttribute("a_normal")) != nullptr) {
		glEnableVertexAttribArray(attribute->location);
		glVertexAttribPointer(attribute->location, 3, GL_FLOAT, GL_FALSE, sizeof(graphic::vec3), ((GLbyte*) geometry->normals()));
	}
	/*GLint a_position;
	if (program->fetchAttribute(position, a_position)) {
		glEnableVertexAttribArray(a_position);
		glVertexAttribPointer(a_position, 3, GL_FLOAT, GL_FALSE, sizeof(graphic::vec3), ((GLbyte*) geometry->positions()));
	}
	GLint a_uv;
	if (geometry->uvCount() >= positionCount && program->fetchAttribute(uv, a_uv)) {
		glEnableVertexAttribArray(a_uv);
		glVertexAttribPointer(a_uv, 2, GL_FLOAT, GL_FALSE, sizeof(graphic::vec2), ((GLbyte*) geometry->uvs()));
	}
	GLint a_normal;
	if (geometry->normalCount() >= positionCount && program->fetchAttribute(normal, a_normal)) {
		glEnableVertexAttribArray(a_normal);
		glVertexAttribPointer(a_normal, 3, GL_FLOAT, GL_FALSE, sizeof(graphic::vec3), ((GLbyte*) geometry->normals()));
	}*/
	if (geometry->indexCount() > 0) {
		if (start >= geometry->indexCount()) {
			start = geometry->indexCount() - 1;
		}
		if (end <= start) {
			end = geometry->indexCount();
		}
		glDrawElements(GLDrawMode(parameter.drawMode), end - start, GL_UNSIGNED_SHORT, (const GLvoid*) (geometry->indices() + start));
	} else {
		if (start >= positionCount) {
			start = positionCount - 1;
		}
		if (end <= start) {
			end = positionCount;
		}
		glDrawArrays(GLDrawMode(parameter.drawMode), start, end - start);
	}
	GLCaches::get().resetActiveTexture();
}

Texture* GLGraphicContext::doLoadTexture(io::InputStream* is) {
	Bitmap* bitmap = BitmapFactory::decodeStream(is);
	if (bitmap == nullptr) {
		return nullptr;
	}
	/**
	 * Deferred texture generation. Generated when prepare to render.
	 */
	GLTexture* texture = new GLTexture(bitmap);

	return texture;
}

} /* namespace graphic */
} /* namespace pola */
