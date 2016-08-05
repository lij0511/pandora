/*
 * RenderTarget.h
 *
 *  Created on: 2016年8月3日
 *      Author: lijing
 */

#ifndef POLA_RENDERTARGET_H_
#define POLA_RENDERTARGET_H_

#include <stdint.h>

#include "pola/graphic/PixelFormat.h"

namespace pola {
namespace graphic {

/*
 *
 */
class RenderTarget {
public:

	RenderTarget(uint32_t width, uint32_t height, PixelFormat format);

	virtual ~RenderTarget();

	uint32_t getWidth() const;
	uint32_t getHeight() const;

private:
	uint32_t mWidth;
	uint32_t mHeight;
	PixelFormat mFormat;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_RENDERTARGET_H_ */
