/*
 * DefaultGLShader.h
 *
 *  Created on: 2016年5月21日
 *      Author: lijing
 */

#ifndef POLA_DEFAULTGLSHADER_H_
#define POLA_DEFAULTGLSHADER_H_

#include "graphic/gl/GLShader.h"

namespace pola {
namespace graphic {

class DefaultGLShader: public GLShader {
public:
	DefaultGLShader();
	virtual ~DefaultGLShader();

	virtual void invalidate();

protected:
	virtual const utils::String generateVertexShader();
	virtual const utils::String generateFragmentShader();

	virtual const ProgramDescription* description();

private:
	utils::String& generatePrefix();
	utils::String m_prefix;
	bool m_dirty = true;

public:
	bool texture0 = true;

	bool lighting = false;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_DEFAULTGLSHADER_H_ */
