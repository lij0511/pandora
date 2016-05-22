/*
 * GLCaches.cpp
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#include "graphic/gl/GLCaches.h"

namespace pola {
namespace graphic {

GLCaches::GLCaches() {
}

GLCaches::~GLCaches() {
}

GLCaches& GLCaches::get() {
	static GLCaches sCaches;
	return sCaches;
}

} /* namespace graphic */
} /* namespace pola */
