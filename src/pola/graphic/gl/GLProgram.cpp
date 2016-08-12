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

	parseUniforms();
	parseAttributes();
}

GLProgram::~GLProgram() {
	glDeleteProgram(mProgramId);

	for (std::map<std::string, GLUniform*>::iterator iter = mUniforms.begin(); iter != mUniforms.end(); iter ++) {
		delete iter->second;
		mUniforms.erase(iter);
	}
	for (std::map<std::string, GLAttribute*>::iterator iter = mAttributes.begin(); iter != mAttributes.end(); iter ++) {
		delete iter->second;
		mAttributes.erase(iter);
	}
}

void GLProgram::use() {
	glUseProgram(mProgramId);
}

GLAttribute* GLProgram::fetchAttribute(const std::string& name) {
	std::map<std::string, GLAttribute*>::iterator iter = mAttributes.find(name);
	if (iter == mAttributes.end()) return nullptr;
	return iter->second;
}

GLUniform* GLProgram::fetchUniform(const std::string& name) {
	std::map<std::string, GLUniform*>::iterator iter = mUniforms.find(name);
	if (iter == mUniforms.end()) return nullptr;
	return iter->second->location >= 0 ? iter->second : nullptr;
}

GLUniform* GLProgram::fetchUniform(const std::string& name, int index) {
	std::map<std::string, GLUniform*>::iterator iter = mUniforms.find(name);
	if (iter == mUniforms.end()) return nullptr;
	GLUniformArray* array = dynamic_cast<GLUniformArray*>(iter->second);
	if (array != nullptr && ssize_t(array->uniforms.size()) > index) {
		return array->uniforms[index]->location >= 0 ? array->uniforms[index] : nullptr;
	}
	return nullptr;
}

GLUniform* GLProgram::fetchUniform(const std::string& name, int index, const std::string& subName) {
	std::map<std::string, GLUniform*>::iterator iter = mUniforms.find(name);
	if (iter == mUniforms.end()) return nullptr;
	GLUniformArray* array = dynamic_cast<GLUniformArray*>(iter->second);
	if (array != nullptr && ssize_t(array->uniforms.size()) > index) {
		GLUniformStructure* structure = dynamic_cast<GLUniformStructure*>(array->uniforms[index]);
		if (structure != nullptr && (iter = structure->uniforms.find(subName)) != structure->uniforms.end()) {
			return iter->second->location >= 0 ? iter->second : nullptr;
		}
	}
	return nullptr;
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
		glGetShaderInfoLog(shader, 512, 0, log);
		LOGE("Error while compiling shader:%s\n", source);
		LOG_ALWAYS_FATAL("Error log: %s\n", log);
		return 0;
	}

	return shader;
}

void GLProgram::parseUniforms() {
	GLint activeUniforms;
	glGetProgramiv(mProgramId, GL_ACTIVE_UNIFORMS, &activeUniforms);
	if (activeUniforms > 0) {
		GLint length;
		glGetProgramiv(mProgramId, GL_ACTIVE_UNIFORM_MAX_LENGTH, &length);
		if (length > 0) {
			GLchar* uniformName = (GLchar*) malloc(length + 1);
			for (int i = 0; i < activeUniforms; ++i) {
				GLsizei name_length = 0;
				GLint size = 0;
				GLenum type = GL_ZERO;
				glGetActiveUniform(mProgramId, i, length, &name_length, &size, &type, uniformName);
				uniformName[name_length] = '\0';
				GLint location = glGetUniformLocation(mProgramId, uniformName);
				std::string name = uniformName;
				addUniform(mUniforms, name, location, size, type);
			}
			free(uniformName);
		}
	}
}

void GLProgram::addUniform(std::map<std::string, GLUniform*>& uniformContainer, std::string& name, GLint location, GLsizei size, GLenum type) {
	if (name.length() == 0) return;
	ssize_t dot = name.find_first_of('.');
	ssize_t bracket = name.find_first_of('[');
	ssize_t bracketRight = name.find_first_of(']');
	if (dot == 0 || bracket == 0 || bracketRight == 0) {
		LOGW("Uniform(%s) parse failed\n", name.c_str());
		return;
	}
	if (dot < 0 && bracket < 0) {
		GLUniform* uniform = uniformContainer[name];
		if (uniform != nullptr) {
			delete uniform;
		}
		uniformContainer[name] = new GLUniform(name, location, type);
		return;
	}
	if (dot < 0 && bracketRight + 1 == ssize_t(name.length())) {
		std::string subName = name.substr(0, bracket);
		GLUniform* uniform = uniformContainer[subName];
		if (uniform != nullptr) {
			delete uniform;
		}
		uniformContainer[subName] = new GLUniformArray(subName, location, size, type);
		return;
	} else if (dot < 0) {
		LOGW("Uniform(%s) parse failed\n", name.c_str());
		return;
	}
	if (bracket < 0 || (dot > 0 && dot < bracket)) {
		std::string subName = name.substr(0, dot);
		GLUniform* uniform = uniformContainer[subName];
		GLUniformStructure* structure = dynamic_cast<GLUniformStructure*>(uniform);
		if (structure == nullptr) {
			if (uniform != nullptr) {
				delete uniform;
			}
			structure = new GLUniformStructure(subName);
			uniformContainer[subName] = structure;
		}
		std::string subStr = name.substr(dot + 1, name.length());
		addUniform(structure->uniforms, subStr, location, size, type);
	} else {
		std::string subName = name.substr(0, bracket);
		GLUniform* uniform = uniformContainer[subName];
		GLUniformArray* array = dynamic_cast<GLUniformArray*>(uniform);
		if (array == nullptr) {
			if (uniform != nullptr) {
				delete uniform;
			}
			array = new GLUniformArray(subName);
			uniformContainer[subName] = array;
		}
		ssize_t i = atoi(name.substr(bracket + 1, bracketRight).c_str());
		if (i < 0) {
			LOGW("Uniform(%s) parse failed\n", name.c_str());
			return;
		}
		if (i >= ssize_t(array->uniforms.size())) {
			array->uniforms.resize(i + 1);
			array->uniforms[i] = nullptr;;
		}
		uniform = array->uniforms[i];
		GLUniformStructure* structure = dynamic_cast<GLUniformStructure*>(uniform);
		if (structure == nullptr) {
			if (uniform != nullptr) {
				delete uniform;
			}
			structure = new GLUniformStructure(subName);
			array->uniforms[i] = structure;
		}
		std::string subStr = name.substr(dot + 1);
		addUniform(structure->uniforms, subStr, location, size, type);
	}
}

void GLProgram::parseAttributes() {
	GLint activeAttributes;
	glGetProgramiv(mProgramId, GL_ACTIVE_ATTRIBUTES, &activeAttributes);
	if (activeAttributes > 0) {
		GLint length;
		glGetProgramiv(mProgramId, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &length);
		if (length > 0) {
			GLchar* attributeName = (GLchar*) malloc(length + 1);
			for (int i = 0; i < activeAttributes; ++i) {
				GLsizei name_length = 0;
				GLint size = 0;
				GLenum type = GL_ZERO;
				glGetActiveAttrib(mProgramId, i, length, &name_length, &size, &type, attributeName);
				attributeName[name_length] = '\0';
				GLint location = glGetAttribLocation(mProgramId, attributeName);
				std::string name = attributeName;
				GLAttribute* attribute = mAttributes[name];
				if (attribute == nullptr) {
					mAttributes[name] = new GLAttribute(name, location, type);
				}
			}
			free(attributeName);
		}
	}
}

} /* namespace graphic */
} /* namespace pola */
