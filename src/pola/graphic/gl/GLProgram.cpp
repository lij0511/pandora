/*
 * GLProgram.cpp
 *
 *  Created on: 2016年5月19日
 *      Author: lijing
 */

#include "pola/log/Log.h"
#include "pola/graphic/gl/GLProgram.h"

//#define DEBUG_SHADER 1;

namespace pola {
namespace graphic {

GLProgram::GLProgram(const char* vertexShader, const char* fragmentShader) :
		mProgramId(0),
		mVertexShaderHandle(0),
		mFragmentShaderHandle(0) {
	compile(vertexShader, fragmentShader);
	glDeleteShader(mVertexShaderHandle);
	glDeleteShader(mFragmentShaderHandle);
}

GLProgram::~GLProgram() {
	glDeleteProgram(mProgramId);
}

void GLProgram::use() {
	glUseProgram(mProgramId);
}

bool GLProgram::fetchAttribute(const utils::String& name, GLint& location) {
	if (!mAttributes.get(name, location)) {
		location = glGetAttribLocation(mProgramId, name.characters());
		mAttributes.put(name, location);
	}
	return location >= 0;
}

bool GLProgram::fetchUniform(const utils::String& name, GLint& location) {
	if (!mUniforms.get(name, location)) {
		location = glGetUniformLocation(mProgramId, name.characters());
		mUniforms.put(name, location);
	}
	return location >= 0;
}

void GLProgram::compile(const char* vertexShader, const char* fragmentShader) {

	mVertexShaderHandle = buildShader(vertexShader, GL_VERTEX_SHADER);
	if (mVertexShaderHandle) {
		mFragmentShaderHandle = buildShader(fragmentShader, GL_FRAGMENT_SHADER);
		if (mFragmentShaderHandle) {
			mProgramId = glCreateProgram();
			glAttachShader(mProgramId, mVertexShaderHandle);
			glAttachShader(mProgramId, mFragmentShaderHandle);

			glLinkProgram(mProgramId);

			GLint status;
			glGetProgramiv(mProgramId, GL_LINK_STATUS, &status);
			if (status != GL_TRUE) {
				GLint infoLen = 0;
				glGetProgramiv(mProgramId, GL_INFO_LOG_LENGTH, &infoLen);
				if (infoLen > 1) {
					GLchar log[infoLen];
					glGetProgramInfoLog(mProgramId, infoLen, 0, &log[0]);
					LOGI("%s\n", log);
				}
				LOG_ALWAYS_FATAL("Error while linking shaders\n");
			}
		} else {
            glDeleteShader(mVertexShaderHandle);
            LOG_ALWAYS_FATAL("Error while building fragment shader\n");
        }
	} else {
		LOG_ALWAYS_FATAL("Error while building vertex shader\n");
	}
}

GLuint GLProgram::buildShader(const char* source, GLenum type) {

#ifdef DEBUG_SHADER
	LOGI("type=%d\nsource=%s\n", type, source);
#endif

	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, 0);
	glCompileShader(shader);


	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		// Some drivers return wrong values for GL_INFO_LOG_LENGTH
		// use a fixed size instead
		GLchar log[512];
		glGetShaderInfoLog(shader, sizeof(log), 0, &log[0]);
		LOGE("Error while compiling shader:%s\n", source);
		LOG_ALWAYS_FATAL("Error log: %s\n", log);
		return 0;
	}

	return shader;
}

} /* namespace graphic */
} /* namespace pola */
