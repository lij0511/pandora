/*
 * GLProgram.h
 *
 *  Created on: 2016年5月19日
 *      Author: lijing
 */

#ifndef POLA_GLPROGRAM_H_
#define POLA_GLPROGRAM_H_

#include "pola/graphic/gl/GL.h"
#include "pola/utils/TinyHashMap.h"
#include "pola/utils/String.h"
#include "pola/graphic/Program.h"
#include "pola/graphic/gl/GLUniform.h"
#include "pola/graphic/gl/GLAttribute.h"

#include <map>
#include <vector>

namespace pola {
namespace graphic {

class GLProgram : public Program {
public:
	GLProgram(const char* vertexShader, const char* fragmentShader);
	virtual ~GLProgram();

	void use();
	GLuint programId() const {return mProgramId;};

	bool fetchAttribute(const utils::String& name, GLint& outLocation);
	bool fetchUniform(const utils::String& name, GLint& outLocation);

	GLUniform* fetchUniform(const std::string& name);
	GLUniform* fetchUniform(const std::string& name, int index);
	GLUniform* fetchUniform(const std::string& name, int index, const std::string& subName);

private:
	void compile(const char* vertexShader, const char* fragmentShader);
	GLuint buildShader(const char* source, GLenum type);

	void parseUniforms();
	void addUniform(std::map<std::string, GLUniform*>& uniformContainer, std::string& name, GLint location, GLsizei size, GLenum type);

	void parseAttributes();
private:
	// Name of the OpenGL program and shaders
	GLuint mProgramId;
	GLuint mVertexShaderHandle;
	GLuint mFragmentShaderHandle;

	pola::utils::TinyHashMap<utils::String, GLint> mAAttributes;
	pola::utils::TinyHashMap<utils::String, GLint> mAUniforms;

	std::map<std::string, GLUniform*> mUniforms;
	std::map<std::string, GLAttribute*> mAttributes;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_GLPROGRAM_H_ */
