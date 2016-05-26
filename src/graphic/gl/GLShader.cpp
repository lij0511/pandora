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

GLShader::GLShader() : mProgram(nullptr), mHash(0) {
}

GLShader::~GLShader() {
}

void GLShader::makeCurrent() {
	mProgram = GLCaches::get().programCache.get(this);
	mProgram->use();
}

const utils::String GLShader::getVertexShader() {
	return generateVertexShader();
}

const utils::String GLShader::getFragmentShader() {
	return generateFragmentShader();
}

void GLShader::set(const mat4& MVPMatrix) {
	GLint u_projection;
	if (mProgram->fetchUniform("u_MVPMatrix", u_projection)) {
		glUniformMatrix4fv(u_projection, 1, GL_FALSE, &MVPMatrix.data[0]);
	}
}

bool GLShader::fetchAttribute(const char* name, GLint& location) {
	return mProgram->fetchAttribute(name, location);
}

bool GLShader::fetchUniform(const char* name, GLint& location) {
	return mProgram->fetchUniform(name, location);
}

utils::hash_t GLShader::hash() {
	utils::hash_t hash = mHash;
	if (hash == 0) {
		const char* vertexGLShader = getVertexShader().characters();
		const char* fragmentGLShader = getFragmentShader().characters();
		size_t vlen = strlen(vertexGLShader);
		size_t flen = strlen(fragmentGLShader);
		if (vlen <= 0 && flen <= 0) return 0;
		while (vlen --) {
			hash = utils::JenkinsHashMix(hash, *vertexGLShader);
			vertexGLShader ++;
		}
		while (flen --) {
			hash = utils::JenkinsHashMix(hash, *fragmentGLShader);
			fragmentGLShader ++;
		}
		hash = utils::JenkinsHashWhiten(hash);
		mHash = hash;
	}
	return hash;
}

void GLShader::invalidate() {
	mHash = 0;
}

const utils::String GLShader::generateVertexShader() {
	return utils::String("attribute vec4 a_position;\n"
			"uniform mat4 u_MVPMatrix;\n"
			"attribute vec2 a_texCoords;\n"
			"varying vec2 v_texCoords;\n"
			"void main()\n"
			"{\n"
			"  v_texCoords = a_texCoords;"
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
			"uniform sampler2D u_baseSampler;\n"
			"varying vec2 v_texCoords;\n"
			"void main()\n"
			"{\n"
			"  gl_FragColor = texture2D(u_baseSampler,  v_texCoords);\n"
//			"  gl_FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
			"}\n", true);
}

}
}
