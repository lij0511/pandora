/*
 * GLUniform.h
 *
 *  Created on: 2016年8月8日
 *      Author: lijing
 */

#ifndef POLA_GLUNIFORM_H_
#define POLA_GLUNIFORM_H_

#include "pola/graphic/gl/GL.h"

#include <string>
#include <vector>
#include <map>

namespace pola {
namespace graphic {

/*
 *
 */
class GLUniform {
public:
	GLUniform(const std::string& name, GLint location, GLenum type);
	virtual ~GLUniform();

	std::string name;
	GLint location;
	GLenum type;
};

class GLUniformArray : public GLUniform {
public:
	GLUniformArray(const std::string& name);
	GLUniformArray(const std::string& name, GLint location, GLsizei size, GLenum type);
	virtual ~GLUniformArray();

	std::vector<GLUniform*> uniforms;
};

class GLUniformStructure : public GLUniform {
public:
	GLUniformStructure(const std::string& name);
	virtual ~GLUniformStructure();

	std::map<std::string, GLUniform*> uniforms;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_GLUNIFORM_H_ */
