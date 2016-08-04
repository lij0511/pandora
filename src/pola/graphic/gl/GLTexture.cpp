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

static GLenum getGLFormat(PixelFormat format) {
	switch (format) {
		case PixelFormat::RGBA8888:
			return GL_RGBA;
		case PixelFormat::ALPHA8:
			return GL_ALPHA;
		case PixelFormat::RGB888:
		case PixelFormat::RGB565:
			return GL_RGB;
		default:
			return GL_RGBA;
	}
}
static GLenum getGLType(PixelFormat format) {
	if (format == PixelFormat::RGB565) {
		return GL_UNSIGNED_SHORT_5_6_5;
	}
	return GL_UNSIGNED_BYTE;
}

GLTexture::GLTexture() : Texture(), id(0), blend(false),
        mipMap(false), releaseBitmap(true), mBitmap(nullptr) {
}

GLTexture::GLTexture(Bitmap* bitmap) : Texture(), id(0), blend(false),
        mipMap(false), releaseBitmap(true), mBitmap(bitmap) {
	if (bitmap != nullptr) {
		width = bitmap->getWidth();
		height = bitmap->getHeight();
		format = bitmap->getFormat();
	}
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
		GLCaches::get().deleteTexture(id);
		id = 0;
	}
}

bool GLTexture::generateTexture(bool useBitmap) {
	if (id <= 0 && (mBitmap != nullptr || !useBitmap)) {

		glEnable( GL_TEXTURE_2D);

		glGenTextures(1, &id);

		GLCaches::get().bindTexture(id);

		if (useBitmap) {
			width = mBitmap->getWidth();
			height = mBitmap->getHeight();
			format = mBitmap->getFormat();
		}

		glPixelStorei(GL_UNPACK_ALIGNMENT, /*mBitmap->bytesPerPixel()*/4);

		GLenum f = getGLFormat(format);
		GLenum type = getGLType(format);

		glTexImage2D(GL_TEXTURE_2D, 0, f, width, height, 0, f, type, useBitmap ? mBitmap->pixels() : 0);

		if (mipMap) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glGenerateMipmap(GL_TEXTURE_2D);
		} else {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
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
