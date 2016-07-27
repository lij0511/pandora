/*
 * BitmapUtils.cpp
 *
 *  Created on: 2016年7月27日
 *      Author: lijing
 */

#include "BitmapUtils.h"

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

bool clearBitmap(Bitmap& bitmap, RGBA32 color) {
	uint32_t width = bitmap.getWidth();
	uint32_t height = bitmap.getHeight();
	if (width == 0 || height == 0) {
		return false;
	}
	uint32_t rowBytes = bitmap.rowBytes();
	uint8_t* data = bitmap.pixels();
	uint32_t c = toFormat(bitmap.getFormat(), color);
	switch (bitmap.getFormat()) {
	case Bitmap::Format::RGBA8888: {
		uint32_t* pixels = (uint32_t*) data;
		for (unsigned w = 0; w < width; w ++) {
			pixels[w] = c;
		}
		for (unsigned h = 1; h < height; h ++) {
			uint8_t* row = data + h * rowBytes;
			memcpy(row, data, rowBytes);
		}
		break;
	}
	case Bitmap::Format::ALPHA8:
		memset(data, c & 0xFF, height * rowBytes);
		break;
	case Bitmap::Format::RGB888: {
		uint8_t r = (c >> 16) && 0xFF;
		uint8_t g = (c >> 8) && 0xFF;
		uint8_t b = (c) && 0xFF;
		for (unsigned w = 0; w < width; w ++) {
			data[w] = r;
			data[w + 1] = g;
			data[w + 2] = b;
		}
		for (unsigned h = 1; h < height; h ++) {
			uint8_t* row = data + h * rowBytes;
			memcpy(row, data, rowBytes);
		}
		break;
	}
		break;
	case Bitmap::Format::RGB565: {
		uint16_t* pixels = (uint16_t*) data;
		for (unsigned w = 0; w < width; w ++) {
			pixels[w] = c;
		}
		for (unsigned h = 1; h < height; h ++) {
			uint8_t* row = data + h * rowBytes;
			memcpy(row, data, rowBytes);
		}
		break;
	}
	default:
		break;
	}
	return true;
}

struct Pixel3 {
	uint8_t a, b, c;
};

void blit_linear(const Bitmap& src, Bitmap& dst) {
	uint32_t swidth = src.getWidth();
	uint32_t sheight = src.getHeight();
	uint32_t dwidth = dst.getWidth();
	uint32_t dheight = dst.getHeight();

	uint32_t spitch = src.rowBytes();
	uint32_t dpitch = dst.rowBytes();

	uint32_t x_ratio = (swidth << 16) / dwidth + 1;
	uint32_t y_ratio = (sheight << 16) / dheight + 1;

	uint8_t* spixels = src.pixels();
	uint8_t* dpixels = dst.pixels();

	uint32_t pixelSize = src.bytesPerPixel();

	unsigned h = 0;
	unsigned w = 0;

	for (h = 0; h < dheight; h ++) {
		uint32_t sy = ((h * y_ratio) >> 16);
		if (sy >= sheight) continue;
		if (swidth == dwidth) {
			memcpy(dpixels + h * dpitch, spixels + sy * spitch, spitch);
		} else {
			if (pixelSize == 1) {
				uint8_t* srow = spixels + sy * spitch;
				uint8_t* drow = dpixels + h * dpitch;
				for (w = 0; w < dwidth; w ++) {
					uint32_t sx = ((w * x_ratio) >> 16);
					if (sx >= swidth) continue;
					drow[w] = srow[sx];
				}
			} else if (pixelSize == 2) {
				uint16_t* srow = (uint16_t*) (spixels + sy * spitch);
				uint16_t* drow = (uint16_t*) (dpixels + h * dpitch);
				for (w = 0; w < dwidth; w ++) {
					uint32_t sx = ((w * x_ratio) >> 16);
					if (sx >= swidth) continue;
					drow[w] = srow[sx];
				}
			} else if (pixelSize == 3) {
				Pixel3* srow = (Pixel3*) (spixels + sy * spitch);
				Pixel3* drow = (Pixel3*) (dpixels + h * dpitch);
				for (w = 0; w < dwidth; w ++) {
					uint32_t sx = ((w * x_ratio) >> 16);
					if (sx >= swidth) continue;
					drow[w] = srow[sx];
				}
			} else if (pixelSize == 4) {
				uint32_t* srow = (uint32_t*) (spixels + sy * spitch);
				uint32_t* drow = (uint32_t*) (dpixels + h * dpitch);
				for (w = 0; w < dwidth; w ++) {
					uint32_t sx = ((w * x_ratio) >> 16);
					if (sx >= swidth) continue;
					drow[w] = srow[sx];
				}
			}
		}
	}
}

bool scaleBitmap(const Bitmap& src, Bitmap*& dst, float scaleW, float scaleH, BitmapScaleMode scaleMode) {
	uint32_t width = src.getWidth();
	uint32_t height = src.getHeight();
	Bitmap::Format format = src.getFormat();
	if (width <= 0 || height <= 0 || scaleW <= 0 || scaleH <= 0) {
		return false;
	}
	uint32_t dstWidth = uint32_t(width * scaleW);
	uint32_t dstHeight = uint32_t(height * scaleH);
	if (dstWidth <= 0 || dstHeight <= 0) {
		return false;
	}
	if (dst == nullptr) {
		dst = Bitmap::create();
	}
	if (width == dstWidth && height == dstHeight) {
		dst->set(dstWidth, dstHeight, format, src.pixels());
		return true;
	} else {
		dst->set(dstWidth, dstHeight, format);
	}

	if (scaleMode == LINEAR) {
		blit_linear(src, *dst);
	}

	return true;
}

} /* namespace graphic */
} /* namespace pola */
