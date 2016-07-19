/*
 * GLTexture.cpp
 *
 *  Created on: 2016年5月19日
 *      Author: lijing
 */

#include "pola/graphic/gl/GLTexture.h"
#include "pola/graphic/gl/GLCaches.h"

namespace pola {
namespace graphic {

static GLenum getGLFormat(Bitmap::Format format) {
	switch (format) {
		case Bitmap::RGBA8888:
			return GL_RGBA;
		case Bitmap::ALPHA8:
			return GL_ALPHA;
		case Bitmap::RGB888:
		case Bitmap::RGB565:
			return GL_RGB;
		default:
			return GL_RGBA;
	}
}
static GLenum getGLType(Bitmap::Format format) {
	if (format == Bitmap::RGB565) {
		return GL_UNSIGNED_SHORT_5_6_5;
	}
	return GL_UNSIGNED_BYTE;
}

GLTexture::GLTexture() : Texture(), id(0), blend(false),
        mipMap(false), releaseBitmap(true), mBitmap(nullptr) {
}

GLTexture::~GLTexture() {
	deleteTexture();
	if (mBitmap != nullptr) {
		delete mBitmap;
		mBitmap = nullptr;
	}
}

void GLTexture::deleteTexture() {
	if (id > 0) {
		glDeleteTextures(1, &id);
		id = 0;
	}
}

bool GLTexture::generateTexture() {
	if (id <= 0 && mBitmap != nullptr) {

		glEnable( GL_TEXTURE_2D);

		glGenTextures(1, &id);

		GLCaches::get().bindTexture(id);

		width = mBitmap->getWidth();
		height = mBitmap->getHeight();
		format = mBitmap->getFormat();

		glPixelStorei(GL_UNPACK_ALIGNMENT, mBitmap->bytesPerPixel());

		GLenum format = getGLFormat(mBitmap->getFormat());
		GLenum type = getGLType(mBitmap->getFormat());
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, type, mBitmap->pixels());

		if (mipMap) {
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	if (mBitmap != nullptr && releaseBitmap) {
		delete mBitmap;
		mBitmap = nullptr;
	}
	return id > 0;
}

}
}
