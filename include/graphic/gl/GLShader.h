/*
 * GLShader.h
 *
 *  Created on: 2016年3月31日
 *      Author: lijing
 */

#ifndef POLA_GLSHADER_H_
#define POLA_GLSHADER_H_

#include "graphic/gl/GLProgram.h"
#include "utils/String.h"
#include "graphic/Matrix4.h"

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

	virtual void set(const mat4& MVPMatrix);
	bool fetchAttribute(const char* name, GLint& outLocation);
	bool fetchUniform(const char* name, GLint& outLocation);

	virtual const utils::String getVertexShader();
	virtual const utils::String getFragmentShader();

	utils::hash_t hash();

protected:
	virtual const utils::String generateVertexShader();
	virtual const utils::String generateFragmentShader();

	virtual void invalidate();

private:
	GLProgram* mProgram;
	utils::hash_t mHash;
};

}
}

#endif /* POLA_SHADER_H_ */
