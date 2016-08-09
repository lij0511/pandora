/*
 * GLAttribute.h
 *
 *  Created on: 2016年8月9日
 *      Author: lijing
 */

#ifndef POLA_GLATTRIBUTE_H_
#define POLA_GLATTRIBUTE_H_

#include "pola/graphic/gl/GL.h"

#include <string>

namespace pola {
namespace graphic {

/*
 *
 */
class GLAttribute {
public:
	GLAttribute(const std::string& name, GLint location, GLenum type);
	virtual ~GLAttribute();

	std::string name;
	GLint location;
	GLenum type;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_GLATTRIBUTE_H_ */
