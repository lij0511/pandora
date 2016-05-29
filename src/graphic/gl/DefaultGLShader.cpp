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

void DefaultGLShader::invalidate() {
	GLShader::invalidate();
	m_dirty = true;
}

const utils::String DefaultGLShader::generateVertexShader() {
	utils::StringBuffer sb;
	sb.append(generatePrefix());
	sb.append("attribute vec4 a_position;\n"
			"uniform mat4 u_MVPMatrix;\n"
			"#ifdef texture0\n"
			"attribute vec2 a_texCoords;\n"
			"varying vec2 v_texCoords;\n"
			"#endif\n"
			"#ifdef lighting\n"
			"attribute vec3 a_normal;\n"
			"varying vec3 v_lightDiffuse;\n"
			"#endif\n"
			"void main()\n"
			"{\n"
			"  #ifdef texture0\n"
			"  v_texCoords = a_texCoords;\n"
			"  #endif\n"
			"  #ifdef lighting\n"
			"  vec3 lightDir = -vec3(0.0f, 0.0f, -1.0f);\n"
			"  float NdotL = clamp(dot(a_normal, lightDir), 0.0, 1.0);\n"
			"  vec3 value = vec3(1.0f, 1.0f, 1.0f) * NdotL;\n"
			"  v_lightDiffuse += value;\n"
			"  #endif\n"
			"  gl_Position = u_MVPMatrix * a_position;\n"
			"}\n");
	utils::String string;
	sb.release(string);
	return string;
}

const utils::String DefaultGLShader::generateFragmentShader() {
	utils::StringBuffer sb;
	sb.append(generatePrefix());
	sb.append("#ifdef GL_ES\n"
			"#define LOWP lowp\n"
			"precision highp float;\n"
			"#else\n"
			"#define LOWP \n"
			"#endif\n"
			"#ifdef texture0\n"
			"uniform sampler2D u_baseSampler;\n"
			"varying vec2 v_texCoords;\n"
			"#endif\n"
			"#ifdef lighting\n"
			"varying vec3 v_lightDiffuse;\n"
			"#endif\n"
			"void main()\n"
			"{\n"
			"  #ifdef texture0\n"
			"  gl_FragColor = texture2D(u_baseSampler,  v_texCoords);\n"
			"  #else\n"
			"  gl_FragColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);\n"
			"  #endif\n"
			"  #ifdef lighting\n"
			"  gl_FragColor.rgb = gl_FragColor.rgb * (v_lightDiffuse);\n"
			"  #endif\n"
			"}\n");
	utils::String string;
	sb.release(string);
	return string;
}

const ProgramDescription* DefaultGLShader::description() {
	if (mDescription == nullptr) {
		mDescription = new ProgramDescription(this);
		mDescription->texture0 = texture0;
		mDescription->lighting = lighting;
	}
	return mDescription;
}

utils::String& DefaultGLShader::generatePrefix() {
	if (m_dirty) {
		// TODO
		utils::StringBuffer sb;
		if (texture0) {
			sb.append("#define texture0\n");
		}
		if (lighting) {
			sb.append("#define lighting\n");
		}
		m_dirty = false;
		sb.release(m_prefix);
	}
	return m_prefix;
}

} /* namespace graphic */
} /* namespace pola */
