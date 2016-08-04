/*
 * RenderTarget.cpp
 *
 *  Created on: 2016年8月4日
 *      Author: lijing
 */

#include "pola/graphic/RenderTarget.h"

namespace pola {
namespace graphic {

RenderTarget::RenderTarget(uint32_t width, uint32_t height, PixelFormat format) :
	mWidth(width), mHeight(height), mFormat(format) {
}

RenderTarget::~RenderTarget() {
}

}
}

