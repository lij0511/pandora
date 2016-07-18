/*
 * Draw.cpp
 *
 *  Created on: 2016年7月18日
 *      Author: lijing
 */

#include "pola/graphic/utils/Draw.h"

namespace pola {
namespace graphic {

static uint32_t toFormat(Bitmap::Format format, RGBA32 color) {
	switch (format) {
	case Bitmap::Format::RGBA8888:
		return color;
	case Bitmap::Format::ALPHA8:
		return color & 0xff;
	case Bitmap::Format::RGB888:
		return color >> 8;
	case Bitmap::Format::RGB565: {
		uint32_t r = (((color & 0xff000000) >> 27) << 11) & 0xf800;
		uint32_t g = (((color & 0xff0000) >> 18) << 5) & 0x7e0;
		uint32_t b = ((color & 0xff00) >> 11) & 0x1f;
		return r | g | b;
	}
	default:
		return 0;
	}
}

Draw::Draw(Bitmap* bitmap) : mBitmap(bitmap), mWidth(bitmap->getWidth()), mHeight(bitmap->getHeight()) {
}

Draw::~Draw() {
}

void Draw::clear(RGBA32 color) {
	if (mWidth == 0 || mHeight == 0) {
		return;
	}
	uint32_t rowBytes = mBitmap->rowBytes();
	uint8_t* data = mBitmap->pixels();
	uint32_t c = toFormat(mBitmap->getFormat(), color);
	switch (mBitmap->getFormat()) {
	case Bitmap::Format::RGBA8888: {
		uint32_t* pixels = (uint32_t*) data;
		for (unsigned w = 0; w < mWidth; w ++) {
			pixels[w] = c;
		}
		for (unsigned h = 1; h < mHeight; h ++) {
			uint8_t* row = data + h * rowBytes;
			memcpy(row, data, rowBytes);
		}
		break;
	}
	case Bitmap::Format::ALPHA8:
		memset(data, c & 0xFF, mHeight * rowBytes);
		break;
	case Bitmap::Format::RGB888: {
		uint8_t r = (c >> 16) && 0xFF;
		uint8_t g = (c >> 8) && 0xFF;
		uint8_t b = (c) && 0xFF;
		for (unsigned w = 0; w < mWidth; w ++) {
			data[w] = r;
			data[w + 1] = g;
			data[w + 2] = b;
		}
		for (unsigned h = 1; h < mHeight; h ++) {
			uint8_t* row = data + h * rowBytes;
			memcpy(row, data, rowBytes);
		}
		break;
	}
		break;
	case Bitmap::Format::RGB565: {
		uint16_t* pixels = (uint16_t*) data;
		for (unsigned w = 0; w < mWidth; w ++) {
			pixels[w] = c;
		}
		for (unsigned h = 1; h < mHeight; h ++) {
			uint8_t* row = data + h * rowBytes;
			memcpy(row, data, rowBytes);
		}
		break;
	}
	default:
		break;
	}
}

void Draw::drawBitmap(const Bitmap* b, int32_t x, int32_t y, int32_t dst_x, int32_t dst_y, uint32_t dst_width, uint32_t dst_height) {
	// TODO
}

} /* namespace graphic */
} /* namespace pola */
