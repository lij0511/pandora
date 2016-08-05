/*
 * GLRenderTarget.cpp
 *
 *  Created on: 2016年8月4日
 *      Author: lijing
 */

#include "pola/graphic/gl/GLCaches.h"
#include "pola/graphic/gl/GLRenderTarget.h"

namespace pola {
namespace graphic {

GLRenderTarget::GLRenderTarget(uint32_t width, uint32_t height, PixelFormat format) :
	RenderTarget(width, height, format) {
	mTexture = new GLTexture;
	mTexture->width = width;
	mTexture->height = height;
	mTexture->format = format;
	mTexture->generateTexture(false);
	glGenFramebuffers(1, &mFrameBuffer);
	GLCaches::get().bindFrameBuffer(mFrameBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexture->id, 0);

	GLCaches::get().unbindTexture(mTexture->id);
	GLCaches::get().unbindFrameBuffer(mFrameBuffer);
}

GLRenderTarget::~GLRenderTarget() {
	delete mTexture;
	GLCaches::get().unbindFrameBuffer(mFrameBuffer);
	glDeleteFramebuffers(1, &mFrameBuffer);
}

GLTexture* GLRenderTarget::getTexture() const {
	return mTexture;
}
GLuint GLRenderTarget::getFrameBuffer() const {
	return mFrameBuffer;
}

} /* namespace graphic */
} /* namespace pola */
