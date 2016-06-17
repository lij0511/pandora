/*
 * GLProgram.h
 *
 *  Created on: 2016年5月19日
 *      Author: lijing
 */

#ifndef POLA_GLPROGRAM_H_
#define POLA_GLPROGRAM_H_

#include "graphic/gl/GL.h"
#include "utils/TinyHashMap.h"
#include "utils/String.h"
#include "graphic/Program.h"

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

private:
	void compile(const char* vertexShader, const char* fragmentShader);
	GLuint buildShader(const char* source, GLenum type);
private:
	// Name of the OpenGL program and shaders
	GLuint mProgramId;
	GLuint mVertexShaderHandle;
	GLuint mFragmentShaderHandle;

	pola::utils::TinyHashMap<utils::String, GLint> mAttributes;
	pola::utils::TinyHashMap<utils::String, GLint> mUniforms;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_GLPROGRAM_H_ */
