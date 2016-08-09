/*
 * GLAttribute.cpp
 *
 *  Created on: 2016年8月9日
 *      Author: lijing
 */

#include "pola/graphic/gl/GLAttribute.h"

namespace pola {
namespace graphic {

GLAttribute::GLAttribute(const std::string& n, GLint l, GLenum t) :
	name(n), location(l), type(t) {
}

GLAttribute::~GLAttribute() {
}

} /* namespace graphic */
} /* namespace pola */
