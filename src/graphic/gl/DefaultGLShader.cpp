/*
 * DefaultGLShader.cpp
 *
 *  Created on: 2016年5月21日
 *      Author: lijing
 */

#include "graphic/gl/DefaultGLShader.h"
#include "utils/StringBuffer.h"

namespace pola {
namespace graphic {

DefaultGLShader::DefaultGLShader() {
}

DefaultGLShader::~DefaultGLShader() {
}

const utils::String DefaultGLShader::generateVertexShader() {
	utils::StringBuffer sb;
	sb.append("attribute vec4 a_position;\n"
			"uniform mat4 u_MVPMatrix;\n"
			"attribute vec2 a_texCoords;\n"
			"varying vec2 v_texCoords;\n"
			"void main()\n"
			"{\n"
			"  v_texCoords = a_texCoords;"
			"  gl_Position = u_MVPMatrix * a_position;\n"
			"}\n");
	utils::String string;
	sb.release(string);
	return string;
}

const utils::String DefaultGLShader::generateFragmentShader() {
	utils::StringBuffer sb;
	sb.append("#ifdef GL_ES\n"
			"#define LOWP lowp\n"
			"precision mediump float;\n"
			"#else\n"
			"#define LOWP \n"
			"#endif\n"
			"#ifdef texture0\n"
			"uniform sampler2D u_baseSampler;\n"
			"#endif\n"
			"varying vec2 v_texCoords;\n"
			"void main()\n"
			"{\n"
			"  #ifdef texture0\n"
			"  gl_FragColor = texture2D(u_baseSampler,  v_texCoords);\n"
			"  #else\n"
			"  gl_FragColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);\n"
			"  #endif\n"
			"}\n");
	utils::String string;
	sb.release(string);
	return string;
}

const ProgramDescription* DefaultGLShader::description() {
	if (mDescription == nullptr) {
		mDescription = new ProgramDescription(this);
	}
	return mDescription;
}

} /* namespace graphic */
} /* namespace pola */
