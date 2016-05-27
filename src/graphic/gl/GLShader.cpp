/*
 * GLShader.cpp
 *
 *  Created on: 2016年3月31日
 *      Author: lijing
 */

#include "graphic/gl/GLCaches.h"
#include "graphic/gl/GLShader.h"

#include "utils/JenkinsHash.h"

namespace pola {
namespace graphic {

GLShader::GLShader() : mDescription(nullptr), mProgram(nullptr) {
}

GLShader::~GLShader() {
	invalidate();
}

void GLShader::makeCurrent() {
	if (mProgram == nullptr) {
		mProgram = GLCaches::get().programCache.get(*description());
	}
	mProgram->use();
}

void GLShader::setMatrix(const char* name, const mat4& MVPMatrix) {
	GLint u_projection;
	if (mProgram->fetchUniform(name, u_projection)) {
		glUniformMatrix4fv(u_projection, 1, GL_FALSE, &MVPMatrix.data[0]);
	}
}

const utils::String GLShader::getVertexShader() {
	return generateVertexShader();
}

const utils::String GLShader::getFragmentShader() {
	return generateFragmentShader();
}

void GLShader::setValues() {
}

bool GLShader::fetchAttribute(const char* name, GLint& location) {
	return mProgram->fetchAttribute(name, location);
}

bool GLShader::fetchUniform(const char* name, GLint& location) {
	return mProgram->fetchUniform(name, location);
}

const utils::String GLShader::generateVertexShader() {
	return utils::String("attribute vec4 a_position;\n"
			"uniform mat4 u_MVPMatrix;\n"
			"void main()\n"
			"{\n"
			"  gl_Position = u_MVPMatrix * a_position;\n"
			"}\n", true);
}

const utils::String GLShader::generateFragmentShader() {
	return utils::String("#ifdef GL_ES\n"
			"#define LOWP lowp\n"
			"precision mediump float;\n"
			"#else\n"
			"#define LOWP \n"
			"#endif\n"
			"void main()\n"
			"{\n"
			"  gl_FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
			"}\n", true);
}

void GLShader::invalidate() {
	if (mDescription != nullptr) {
		delete mDescription;
		mDescription = nullptr;
	}
	mProgram = nullptr;
}

const ProgramDescription* GLShader::description() {
	if (mDescription == nullptr) {
		mDescription = new ProgramDescription(getVertexShader(), getFragmentShader());
	}
	return mDescription;
}

}
}
