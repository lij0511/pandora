/*
 * GLUniform.cpp
 *
 *  Created on: 2016年8月8日
 *      Author: lijing
 */

#include "pola/graphic/gl/GLUniform.h"

namespace pola {
namespace graphic {

GLUniform::GLUniform(const std::string& n, GLint l, GLenum t) :
	name(n), location(l), type(t) {
}

GLUniform::~GLUniform() {
}


GLUniformArray::GLUniformArray(const std::string& name) :
	GLUniform(name, -1, GL_ZERO) {
}

GLUniformArray::GLUniformArray(const std::string& name, GLint location, GLsizei size, GLenum type) :
	GLUniform(name, -1, GL_ZERO) {
	for (GLsizei i = 0; i < size; i ++) {
		uniforms.push_back(new GLUniform(name, location + i, type));
	}
}

GLUniformArray::~GLUniformArray() {
	for(std::vector<GLUniform*>::iterator iter = uniforms.begin(); iter != uniforms.end(); iter ++) {
		GLUniform* uniform = *iter;
		uniforms.erase(iter);
		delete uniform;
	}
}


GLUniformStructure::GLUniformStructure(const std::string& name) :
	GLUniform(name, -1, GL_ZERO) {
}

GLUniformStructure::~GLUniformStructure() {
	for (std::map<std::string, GLUniform*>::iterator iter = uniforms.begin(); iter != uniforms.end(); iter ++) {
		delete iter->second;
		uniforms.erase(iter);
	}
}

} /* namespace graphic */
} /* namespace pola */
