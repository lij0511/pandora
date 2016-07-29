/*
 * BitmapUtils.cpp
 *
 *  Created on: 2016年7月27日
 *      Author: lijing
 */

#include "BitmapUtils.h"
#include "pola/graphic/Color.h"
#include "ColorPriv.h"

#include <string.h>
#include <stdio.h>

namespace pola {
namespace graphic {

bool clearBitmap(Bitmap& bitmap, uint32_t color) {
	uint32_t width = bitmap.getWidth();
	uint32_t height = bitmap.getHeight();
	if (width == 0 || height == 0) {
		return false;
	}
	uint32_t rowBytes = bitmap.rowBytes();
	uint8_t* data = bitmap.pixels();
	switch (bitmap.getFormat()) {
	case Bitmap::Format::RGBA8888: {
		uint32_t* pixels = (uint32_t*) data;
		for (unsigned w = 0; w < width; w ++) {
			pixels[w] = PackRGBA8888(ColorGetR(color), ColorGetG(color), ColorGetB(color), ColorGetA(color));
		}
		for (unsigned h = 1; h < height; h ++) {
			uint8_t* row = data + h * rowBytes;
			memcpy(row, data, rowBytes);
		}
		break;
	}
	case Bitmap::Format::ALPHA8:
		memset(data, ColorGetA(color) & 0xFF, height * rowBytes);
		break;
	case Bitmap::Format::RGB888: {
		uint8_t r = ColorGetR(color);
		uint8_t g = ColorGetG(color);
		uint8_t b = ColorGetB(color);
		for (unsigned w = 0; w < width * 3; w += 3) {
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
		for (unsigned w = 0; w < width; w ++) {
			bitmap.putPixel(w, 0, color);
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

void blit_nearest(const Bitmap& src, Bitmap& dst) {
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
			uint8_t* srow = spixels + sy * spitch;
			uint8_t* drow = dpixels + h * dpitch;
			for (w = 0; w < dwidth; w ++) {
				uint32_t sx = ((w * x_ratio) >> 16);
				if (sx >= swidth) continue;
				for (unsigned p = 0; p < pixelSize; p ++) {
					drow[w * pixelSize + p] = srow[sx * pixelSize + p];
				}
			}
		}
	}
}

void blit_bilinear(const Bitmap& src, Bitmap& dst) {

	uint32_t swidth = src.getWidth();
	uint32_t sheight = src.getHeight();
	uint32_t dwidth = dst.getWidth();
	uint32_t dheight = dst.getHeight();

	float x_ratio = ((float) swidth)/ dwidth;
	float y_ratio = ((float) sheight) / dheight;
	float x_diff = 0;
	float y_diff = 0;

	unsigned h = 0;
	unsigned w = 0;
	for (h = 0; h < dheight; h ++) {
		uint32_t sy = uint32_t(h * y_ratio);
		if (sy >= sheight) continue;
		y_diff = (y_ratio * h) - sy;
		for (w = 0; w < dwidth; w ++) {
			uint32_t sx = uint32_t(w * x_ratio);
			if (sx >= swidth) continue;
			x_diff = (x_ratio * w) - sx;
			uint32_t c1 = 0, c2 = 0, c3 = 0, c4 = 0;
			c1 = src.getPixel(sx, sy);
			if(sx + 1 < swidth) c2 = src.getPixel(sx + 1, sy); else c2 = c1;
			if(sy + 1< sheight) c3 = src.getPixel(sx, sy + 1); else c3 = c1;
			if(sx + 1< swidth && sy + 1 < sheight) c4 = src.getPixel(sx + 1, sy + 1); else c4 = c1;

			float ta = (1 - x_diff) * (1 - y_diff);
			float tb = (x_diff) * (1 - y_diff);
			float tc = (1 - x_diff) * (y_diff);
			float td = (x_diff) * (y_diff);

			uint32_t r = (uint32_t)(((c1 >> 24) & 0xff) * ta +
									((c2 >> 24) & 0xff) * tb +
									((c3 >> 24) & 0xff) * tc +
									((c4 >> 24) & 0xff) * td) & 0xff;
			uint32_t g = (uint32_t)(((c1 >> 16) & 0xff) * ta +
									((c2 >> 16) & 0xff) * tb +
									((c3 >> 16) & 0xff) * tc +
									((c4 >> 16) & 0xff) * td) & 0xff;
			uint32_t b = (uint32_t)(((c1 >> 8) & 0xff) * ta +
									((c2 >> 8) & 0xff) * tb +
									((c3 >> 8) & 0xff) * tc +
									((c4 >> 8) & 0xff) * td) & 0xff;
			uint32_t a = (uint32_t)((c1 & 0xff) * ta +
									(c2 & 0xff) * tb +
									(c3 & 0xff) * tc +
									(c4 & 0xff) * td) & 0xff;


			uint32_t src_col = ColorSetRGBA(r, g, b, a);

			dst.putPixel(w, h, src_col);
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
	dst->setHasAlpha(src.hasAlpha());

	if (scaleMode == NEAREST) {
		blit_nearest(src, *dst);
	} else {
		blit_bilinear(src, *dst);
	}

	return true;
}


} /* namespace graphic */
} /* namespace pola */
