/*
 * GLTexture.cpp
 *
 *  Created on: 2016年5月19日
 *      Author: lijing
 */

#include "graphic/gl/GLTexture.h"
#include "graphic/gl/GLCaches.h"

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

GLTexture::GLTexture() : id(0), blend(false), width(0), height(0),
        mipMap(false), m_bitmap(nullptr) {
}

GLTexture::~GLTexture() {
	deleteTexture();
	if (m_bitmap != nullptr) {
		delete m_bitmap;
		m_bitmap = nullptr;
	}
}

void GLTexture::deleteTexture() {
	if (id > 0) {
		glDeleteTextures(1, &id);
		id = 0;
	}
}

bool GLTexture::generateTexture() {
	if (id <= 0 && m_bitmap != nullptr) {
		// We could also enable mipmapping if both bitmap dimensions are powers
		// of 2 but we'd have to deal with size changes. Let's keep this simple
		const bool canMipMap = true;//Extensions::getInstance().hasNPot();

		glGenTextures(1, &id);

		GLCaches::get().bindTexture(id);

//		generation = m_bitmap->getGenerationID();
		width = m_bitmap->getWidth();
		height = m_bitmap->getHeight();

		glPixelStorei(GL_UNPACK_ALIGNMENT, m_bitmap->bytesPerPixel());

		GLenum format = getGLFormat(m_bitmap->getFormat());
		GLenum type = getGLType(m_bitmap->getFormat());
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, type, m_bitmap->pixels());

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	if (m_bitmap != nullptr) {
		delete m_bitmap;
		m_bitmap = nullptr;
	}
	return id > 0;
}

}
}
