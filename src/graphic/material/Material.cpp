/*
 * Material.cpp
 *
 *  Created on: 2016年5月23日
 *      Author: lijing
 */

#include <typeinfo>
#include "graphic/material/Material.h"

#include "utils/StringBuffer.h"

namespace pola {
namespace graphic {

Material::Material(const FColor3& color, Texture* textureMap)
	: mVertexShader(true), mFragmentShader(true),
	  mColor(color), mTextureMap(textureMap) {
}

Material::~Material() {
}

bool Material::hasTextureMap() const {
	return mTextureMap != nullptr;
}

const utils::String Material::getVertexShader() {
	if (mVertexShader.isEmpty()) {
		mVertexShader = generateVertexShader();
	}
	return mVertexShader;
}

const utils::String Material::getFragmentShader() {
	if (mFragmentShader.isEmpty()) {
		mFragmentShader = generateFragmentShader();
	}
	return mFragmentShader;
}

void Material::bind(GraphicContext* graphic, Program* program) {
#ifdef OGL_RENDERER
	GLProgram* glProgram = (GLProgram*) program;
	static utils::String u_color = utils::String("u_color", true);
	GLint u_colorH;
	if (glProgram->fetchUniform(u_color, u_colorH)) {
		glUniform3f(u_colorH, mColor.r, mColor.g, mColor.b);
	}
	if (hasTextureMap()) {
		GLTexture* glTexture = (GLTexture*) mTextureMap;
		if (glTexture->generateTexture()) {
			GLCaches::get().resetActiveTexture();
			GLCaches::get().activeTexture(0);
			GLCaches::get().bindTexture(glTexture->id);
			GLProgram* glProgram = (GLProgram*) program;
			static utils::String u_textureMap = utils::String("u_textureMap", true);
			GLint u_textureMapH;
			if (glProgram->fetchUniform(u_textureMap, u_textureMapH)) {
				glUniform1i(u_textureMapH, 0);
			}
		}
	}
#endif
}

const char* Material::getMaterialType() const {
	if (isShaderMaterial()) {
		return nullptr;
	} else {
		return typeid(*this).name();
	}
}

const utils::String Material::generateVertexShader() {
	utils::StringBuffer sb(256);
#ifdef OGL_RENDERER
	sb.append(GLShaderLib::VS_Para_TextureMap())
		.append("void main()\n"
			"{\n")
		.append(GLShaderLib::VS_TextureMap())
		.append(GLShaderLib::VS_MainPosition())
		.append("}\n");
#endif
	utils::String s;
	sb.release(s);
	return s;
}

const utils::String Material::generateFragmentShader() {
	utils::StringBuffer sb(256);
#ifdef OGL_RENDERER
	sb.append(GLShaderLib::FS_MainHeader())
		.append(GLShaderLib::FS_Para_TextureMap())
		.append("uniform vec3 u_color;\n"
			"void main()\n"
			"{\n")
		.append(GLShaderLib::FS_DiffuseColor())
		.append("  diffuseColor = vec4(u_color, 1.0f);\n")
		.append(GLShaderLib::FS_TextureMap())
		.append("  gl_FragColor = diffuseColor;\n"
			"}\n");
#endif
	utils::String s;
	sb.release(s);
	return s;
}

bool Material::isShaderMaterial() const {
	return false;
}

} /* namespace graphic */
} /* namespace pola */