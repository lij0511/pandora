/*
 * BitmapUtils.cpp
 *
 *  Created on: 2016年7月27日
 *      Author: lijing
 */

#include "pola/graphic/utils/BitmapUtils.h"

#include <string.h>
#include <stdio.h>

namespace pola {
namespace graphic {

static uint32_t toFormat(Bitmap::Format format, uint32_t color) {
	switch (format) {
	case Bitmap::Format::RGBA8888:
		return color;
	case Bitmap::Format::ALPHA8:
		return color & 0xff;
	case Bitmap::Format::RGB888:
		return (color >> 8) & 0xffffff;
	case Bitmap::Format::RGB565: {
		uint32_t r = (color >> 16) & 0xf800;
		uint32_t g = (color >> 13) & 0x7e0;
		uint32_t b = (color >> 11) & 0x1f;
		return r | g | b;
	}
	default:
		return 0;
	}
}

static uint32_t toRGBA32(Bitmap::Format format, uint32_t color) {
	switch (format) {
	case Bitmap::Format::RGBA8888:
		return color;
	case Bitmap::Format::ALPHA8:
		return (color & 0xff) | 0xffffff00;
	case Bitmap::Format::RGB888:
		return (color << 8) | 0x000000ff;
	case Bitmap::Format::RGB565: {
		uint32_t rr = (color << 16) & 0xf8000000;
		uint32_t gg = (color << 13) & 0xfc0000;
		uint32_t bb = (color << 11) & 0xf800;

		return rr | gg | bb | 0xff;
	}
	default:
		return 0;
	}
	return color;
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

	Bitmap::Format format = src.getFormat();

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
			c1 = toRGBA32(format, src.getPixel(sx, sy));
			if(sx + 1 < swidth) c2 = toRGBA32(format, src.getPixel(sx + 1, sy)); else c2 = c1;
			if(sy + 1< sheight) c3 = toRGBA32(format, src.getPixel(sx, sy + 1)); else c3 = c1;
			if(sx + 1< swidth && sy + 1 < sheight) c4 = toRGBA32(format, src.getPixel(sx + 1, sy + 1)); else c4 = c1;

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


			uint32_t src_col = ((r << 24) & 0xff000000) | ((g << 16) & 0xff0000) | ((b << 8) & 0xff00) | a;
			src_col = toFormat(dst.getFormat(), src_col);

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

	if (scaleMode == NEAREST) {
		blit_nearest(src, *dst);
	} else {
		blit_bilinear(src, *dst);
	}

	return true;
}


uint8_t PreMultiplyAlpha(uint8_t a, uint8_t b) {
	unsigned prod = a * b + 128;
	return (prod + (prod >> 8)) >> 8;
}

uint32_t PreMultiplyAlpha(uint32_t rgba) {
	uint8_t r = (rgba >> 24) & 0xff;
	uint8_t g = (rgba >> 16) & 0xff;
	uint8_t b = (rgba >> 8) & 0xff;
	uint8_t a = (rgba) & 0xff;

	r = PreMultiplyAlpha(r, a);
	g = PreMultiplyAlpha(g, a);
	b = PreMultiplyAlpha(b, a);

	return ((r << 24) & 0xff000000) |  ((g << 16) & 0xff0000) |  ((b << 8) & 0xff00) |  a;
}

static bool Sample_RGBA8888_2_RGBA8888(void* dstRow, const uint8_t* src, uint32_t width, uint32_t deltaSrc) {
	/*uint32_t* dst = (uint32_t*) dstRow;
	bool hasAlpha = false;
	for (unsigned i = 0; i < width; i ++) {
		const uint32_t* srcRow = (const uint32_t*) src;
		hasAlpha |= (srcRow[0] & 0xff) != 255;
		dst[i] = PreMultiplyAlpha(srcRow[0]);
		src += deltaSrc;
	}
	return hasAlpha;*/
	uint8_t* dst = (uint8_t*) dstRow;
	bool hasAlpha = false;
	for (unsigned i = 0; i < width; i ++) {
		uint8_t r = src[0];
		uint8_t g = src[1];
		uint8_t b = src[2];
		uint8_t a = src[3];
		if (a != 0xff) {
			hasAlpha |= true;
			r = PreMultiplyAlpha(r, a);
			g = PreMultiplyAlpha(g, a);
			b = PreMultiplyAlpha(b, a);
		}
		dst[i * 4] = r;
		dst[i * 4 + 1] = g;
		dst[i * 4 + 2] = b;
		dst[i * 4 + 3] = a;
		src += deltaSrc;
	}
	return hasAlpha;
}
static bool Sample_ALPHA8_2_RGBA8888(void* dstRow, const uint8_t* src, uint32_t width, uint32_t deltaSrc) {
	uint32_t* dst = (uint32_t*) dstRow;
	bool hasAlpha = false;
	for (unsigned i = 0; i < width; i ++) {
		hasAlpha |= src[0] != 255;
		dst[i] = PreMultiplyAlpha(toRGBA32(Bitmap::Format::ALPHA8, src[0]));
		src += deltaSrc;
	}
	return hasAlpha;
}
static bool Sample_RGB888_2_RGBA8888(void* dstRow, const uint8_t* src, uint32_t width, uint32_t deltaSrc) {
	uint32_t* dst = (uint32_t*) dstRow;
	for (unsigned i = 0; i < width; i ++) {
		dst[i] = toRGBA32(Bitmap::Format::RGB888, ((src[0] << 16) & 0xff0000) | ((src[1] << 8) & 0xff00) | ((src[2]) & 0xff));
		src += deltaSrc;
	}
	return false;
}

static bool Sample_RGBA8888_2_RGB888(void* dstRow, const uint8_t* src, uint32_t width, uint32_t deltaSrc) {
	uint8_t* dst = (uint8_t*) dstRow;
	for (unsigned i = 0; i < width * 3; i += 3) {
		const uint32_t* srcRow = (const uint32_t*) src;
		uint32_t rgb = toFormat(Bitmap::Format::RGB888, PreMultiplyAlpha(srcRow[0]));
		dst[i] = (rgb >> 16) & 0xff;
		dst[i + 1] = (rgb >> 8) & 0xff;
		dst[i + 2] = (rgb) & 0xff;
		src += deltaSrc;
	}
	return false;
}
static bool Sample_ALPHA8_2_RGB888(void* dstRow, const uint8_t* src, uint32_t width, uint32_t deltaSrc) {
	uint8_t* dst = (uint8_t*) dstRow;
	for (unsigned i = 0; i < width * 3; i += 3) {
		uint32_t rgb = toFormat(Bitmap::Format::RGB888, PreMultiplyAlpha(toRGBA32(Bitmap::Format::ALPHA8, src[0])));
		dst[i] = (rgb >> 16) & 0xff;
		dst[i + 1] = (rgb >> 8) & 0xff;
		dst[i + 2] = (rgb) & 0xff;
		src += deltaSrc;
	}
	return false;
}
static bool Sample_RGB888_2_RGB888(void* dstRow, const uint8_t* src, uint32_t width, uint32_t deltaSrc) {
	uint8_t* dst = (uint8_t*) dstRow;
	for (unsigned i = 0; i < width * 3; i += 3) {
		dst[i] = src[0];
		dst[i + 1] = src[1];
		dst[i + 2] = src[2];
		src += deltaSrc;
	}
	return false;
}

static bool Sample_RGBA8888_2_ALPHA8(void* dstRow, const uint8_t* src, uint32_t width, uint32_t deltaSrc) {
	uint8_t* dst = (uint8_t*) dstRow;
	bool hasAlpha = false;
	for (unsigned i = 0; i < width; i ++) {
		const uint32_t* srcRow = (const uint32_t*) src;
		dst[i] = toFormat(Bitmap::Format::ALPHA8, srcRow[0]);
		hasAlpha |= dst[i] != 255;
		src += deltaSrc;
	}
	return hasAlpha;
}
static bool Sample_ALPHA8_2_ALPHA8(void* dstRow, const uint8_t* src, uint32_t width, uint32_t deltaSrc) {
	uint8_t* dst = (uint8_t*) dstRow;
	bool hasAlpha = false;
	for (unsigned i = 0; i < width; i ++) {
		hasAlpha |= src[0] != 255;
		dst[i] = src[0];
		src += deltaSrc;
	}
	return hasAlpha;
}
static bool Sample_RGB888_2_ALPHA8(void* dstRow, const uint8_t* src, uint32_t width, uint32_t deltaSrc) {
	uint8_t* dst = (uint8_t*) dstRow;
	memset(dst, 0xff, width);
	return false;
}

static bool Sample_RGBA8888_2_RGB565(void* dstRow, const uint8_t* src, uint32_t width, uint32_t deltaSrc) {
	uint16_t* dst = (uint16_t*) dstRow;
	for (unsigned i = 0; i < width; i ++) {
		const uint32_t* srcRow = (const uint32_t*) src;
		dst[i] = toFormat(Bitmap::Format::RGB565, PreMultiplyAlpha(srcRow[0]));
		src += deltaSrc;
	}
	return false;
}
static bool Sample_ALPHA8_2_RGB565(void* dstRow, const uint8_t* src, uint32_t width, uint32_t deltaSrc) {
	uint16_t* dst = (uint16_t*) dstRow;
	for (unsigned i = 0; i < width; i ++) {
		dst[i] = toFormat(Bitmap::Format::RGB565, ((src[0] << 24) & 0xff000000) | ((src[1] << 16) & 0xff0000) | ((src[2] << 8) & 0xff00) | 0xFF);
		src += deltaSrc;
	}
	return false;
}
static bool Sample_RGB888_2_RGB565(void* dstRow, const uint8_t* src, uint32_t width, uint32_t deltaSrc) {
	uint16_t* dst = (uint16_t*) dstRow;
	for (unsigned i = 0; i < width; i ++) {
		dst[i] = toFormat(Bitmap::Format::RGB565, PreMultiplyAlpha(toRGBA32(Bitmap::Format::ALPHA8, src[0])));
		src += deltaSrc;
	}
	return false;
}

uint32_t convertColorFormat(uint32_t srcColor, Bitmap::Format srcFormat, Bitmap::Format dstFormat) {
	if (dstFormat == Bitmap::Format::UNKONWN || srcFormat == dstFormat) {
		return srcColor;
	}

	return srcColor;
}

ImageSampler::ImageSampler(Bitmap::Format srcFormat, Bitmap::Format dstFormat) {
	if (dstFormat == Bitmap::Format::UNKONWN) {
		dstFormat = srcFormat;
	}
	RowProc rowProc = nullptr;
	switch (dstFormat) {
		case Bitmap::Format::RGBA8888: {
			switch (srcFormat) {
				case Bitmap::Format::RGBA8888:
					rowProc = Sample_RGBA8888_2_RGBA8888;
					break;
				case Bitmap::Format::ALPHA8:
					rowProc = Sample_ALPHA8_2_RGBA8888;
					break;
				case Bitmap::Format::RGB888:
					rowProc = Sample_RGB888_2_RGBA8888;
					break;
				default:
					break;
			}
			break;
		}
		case Bitmap::Format::RGB888: {
			switch (srcFormat) {
				case Bitmap::Format::RGBA8888:
					rowProc = Sample_RGBA8888_2_RGB888;
					break;
				case Bitmap::Format::ALPHA8:
					rowProc = Sample_ALPHA8_2_RGB888;
					break;
				case Bitmap::Format::RGB888:
					rowProc = Sample_RGB888_2_RGB888;
					break;
				default:
					break;
			}
			break;
		}
		case Bitmap::Format::ALPHA8: {
			switch (srcFormat) {
				case Bitmap::Format::RGBA8888:
					rowProc = Sample_RGBA8888_2_ALPHA8;
					break;
				case Bitmap::Format::ALPHA8:
					rowProc = Sample_ALPHA8_2_ALPHA8;
					break;
				case Bitmap::Format::RGB888:
					rowProc = Sample_RGB888_2_ALPHA8;
					break;
				default:
					break;
			}
			break;
		}
		case Bitmap::Format::RGB565: {
			switch (srcFormat) {
				case Bitmap::Format::RGBA8888:
					rowProc = Sample_RGBA8888_2_RGB565;
					break;
				case Bitmap::Format::ALPHA8:
					rowProc = Sample_ALPHA8_2_RGB565;
					break;
				case Bitmap::Format::RGB888:
					rowProc = Sample_RGB888_2_RGB565;
					break;
				default:
					break;
			}
			break;
		}
		default:
			break;
	}
	mRowProc = rowProc;
}

bool ImageSampler::sampleScanline(void* dst, const uint8_t* src, uint32_t width, uint32_t deltaSrc) {
	if (mRowProc == nullptr) {
		return false;
	}
	return mRowProc(dst, src, width, deltaSrc);
}

} /* namespace graphic */
} /* namespace pola */
