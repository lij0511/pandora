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
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_DEFAULTGLSHADER_H_ */
