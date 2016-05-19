/*
 * GLTexture.cpp
 *
 *  Created on: 2016年5月19日
 *      Author: lijing
 */

#include "graphic/gl/GLTexture.h"

namespace pola {
namespace graphic {

GLTexture::GLTexture() : id(0), blend(false), width(0), height(0),
        mipMap(false) {
}

GLTexture::~GLTexture() {
	deleteTexture();
}

void GLTexture::deleteTexture() {
	if (id > 0) {
		glDeleteTextures(1, &id);
		id = 0;
	}
}

}
}
