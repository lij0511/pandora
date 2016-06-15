/*
 * GLShader.h
 *
 *  Created on: 2016年3月31日
 *      Author: lijing
 */

#ifndef POLA_GLSHADER_H_
#define POLA_GLSHADER_H_

#include "graphic/gl/GLProgram.h"
#include "graphic/gl/GLProgramCache.h"
#include "utils/String.h"
#include "graphic/math/Matrix4.h"

namespace pola {
namespace graphic {

/*
 *
 */
class GLShader {
public:

	GLShader();
	virtual ~GLShader();

	void makeCurrent();

	void setMatrix(const utils::String& name, const mat4& matrix);
	bool fetchAttribute(const utils::String& name, GLint& outLocation);
	bool fetchUniform(const utils::String& name, GLint& outLocation);

	const utils::String getVertexShader();
	const utils::String getFragmentShader();

	virtual void setValues();

	/**
	 * Must be called when ShaderProgram is changed, both Vertex and Fragment.
	 */
	virtual void invalidate();
protected:
	virtual const utils::String generateVertexShader();
	virtual const utils::String generateFragmentShader();

	virtual const ProgramDescription* description();

	ProgramDescription* mDescription;
private:
	GLProgram* mProgram;
};

}
}

#endif /* POLA_SHADER_H_ */
