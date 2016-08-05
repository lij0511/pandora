/*
 * GLRenderTarget.h
 *
 *  Created on: 2016年8月4日
 *      Author: lijing
 */

#ifndef POLA_GLRENDERTARGET_H_
#define POLA_GLRENDERTARGET_H_

#include "pola/graphic/RenderTarget.h"
#include "pola/graphic/gl/GLTexture.h"

namespace pola {
namespace graphic {

/*
 *
 */
class GLRenderTarget: public RenderTarget {
public:
	GLRenderTarget(uint32_t width, uint32_t height, PixelFormat format);
	virtual ~GLRenderTarget();

	GLTexture* getTexture() const;
	GLuint getFrameBuffer() const;

private:
	GLTexture* mTexture;
	GLuint mFrameBuffer;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_GLRENDERTARGET_H_ */
