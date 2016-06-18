/*
 * BasicMaterial.cpp
 *
 *  Created on: 2016年6月16日
 *      Author: lijing
 */

#include "graphic/material/BasicMaterial.h"
#ifdef OGL_RENDERER
#include "graphic/gl/GLProgram.h"
#include "graphic/gl/GLShaderLib.h"
#endif

#include "utils/StringBuffer.h"

namespace pola {
namespace graphic {

BasicMaterial::BasicMaterial(const FColor& color) : mColor(color) {
}

BasicMaterial::~BasicMaterial() {
}

const utils::String BasicMaterial::generateVertexShader() {
	return Material::generateVertexShader();
}

const utils::String BasicMaterial::generateFragmentShader() {
	utils::StringBuffer sb(256);
#ifdef OGL_RENDERER
	sb.append(GLShaderLib::FS_MainHeader());
	sb.append("uniform vec4 u_color;\n"
			"void main()\n"
			"{\n"
			"  gl_FragColor = u_color;\n"
			"}\n");
#endif
	utils::String s;
	sb.release(s);
	return s;
}

void BasicMaterial::bind(Program* program) {
#ifdef OGL_RENDERER
	GLProgram* glProgram = (GLProgram*) program;
	GLint u_color;
	if (glProgram->fetchUniform(utils::String("u_color", true), u_color)) {
		glUniform4f(u_color, mColor.r, mColor.g, mColor.b, mColor.a);
	}
#endif
}

} /* namespace graphic */
} /* namespace pola */
