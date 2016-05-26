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
	glActiveTexture(gTextureUnits[0]);
	mTextureUnit = 0;

	resetBoundTextures();
}

GLCaches::~GLCaches() {
}

GLCaches& GLCaches::get() {
	static GLCaches sCaches;
	return sCaches;
}

void GLCaches::bindTexture(GLuint texture) {
    if (mBoundTextures[mTextureUnit] != texture) {
        glBindTexture(GL_TEXTURE_2D, texture);
        mBoundTextures[mTextureUnit] = texture;
    }
}

void GLCaches::bindTexture(GLenum target, GLuint texture) {
    if (target == GL_TEXTURE_2D) {
        bindTexture(texture);
    } else {
        // GLConsumer directly calls glBindTexture() with
        // target=GL_TEXTURE_EXTERNAL_OES, don't cache this target
        // since the cached state could be stale
        glBindTexture(target, texture);
    }
}

void GLCaches::deleteTexture(GLuint texture) {
	if (texture) {
		unbindTexture(texture);
		glDeleteTextures(1, &texture);
	}
}

void GLCaches::resetBoundTextures() {
    memset(mBoundTextures, 0, REQUIRED_TEXTURE_UNITS_COUNT * sizeof(GLuint));
}

void GLCaches::unbindTexture(GLuint texture) {
    for (int i = 0; i < REQUIRED_TEXTURE_UNITS_COUNT; i++) {
        if (mBoundTextures[i] == texture) {
            mBoundTextures[i] = 0;
        }
    }
}

void GLCaches::activeTexture(GLuint textureUnit) {
    if (mTextureUnit != textureUnit) {
        glActiveTexture(gTextureUnits[textureUnit]);
        mTextureUnit = textureUnit;
    }
}

void GLCaches::resetActiveTexture() {
    mTextureUnit = -1;
}

} /* namespace graphic */
} /* namespace pola */
