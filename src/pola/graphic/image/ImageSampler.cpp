/*
 * ImageSampler.cpp
 *
 *  Created on: 2016年7月29日
 *      Author: lijing
 */

#include "ImageSampler.h"
#include "pola/graphic/Color.h"
#include "pola/graphic/utils/ColorPriv.h"

#include <string.h>

namespace pola {
namespace graphic {

uint8_t PreMultiplyAlpha(uint8_t a, uint8_t b) {
	unsigned prod = a * b + 128;
	return (prod + (prod >> 8)) >> 8;
}

uint32_t PreMultiplyAlpha(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	r = PreMultiplyAlpha(r, a);
	g = PreMultiplyAlpha(g, a);
	b = PreMultiplyAlpha(b, a);

	uint32_t color = ColorSetRGBA(r, g, b, a);
	return color;
}

uint32_t PreMultiplyAlphaAndPack(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	r = PreMultiplyAlpha(r, a);
	g = PreMultiplyAlpha(g, a);
	b = PreMultiplyAlpha(b, a);

	return PackRGBA8888(r, g, b, a);
}

static bool Sample_RGBA8888_2_RGBA8888(void* dstRow, const uint8_t* src, uint32_t width, uint32_t deltaSrc, bool preMultiplyAlpha) {
	uint32_t* dst = (uint32_t*) dstRow;
	unsigned alphaMask = 0xff;
	for (unsigned i = 0; i < width; i ++) {
		uint8_t alpha = src[3];
		alphaMask &= alpha;
		if (preMultiplyAlpha) {
			dst[i] = PreMultiplyAlphaAndPack(src[0], src[1], src[2], alpha);
		} else {
			dst[i] = PackRGBA8888(src[0], src[1], src[2], alpha);
		}
		src += deltaSrc;
	}
	return alphaMask != 0xff;
}
static bool Sample_ALPHA8_2_RGBA8888(void* dstRow, const uint8_t* src, uint32_t width, uint32_t deltaSrc, bool preMultiplyAlpha) {
	uint32_t* dst = (uint32_t*) dstRow;
	unsigned alphaMask = 0xff;
	for (unsigned i = 0; i < width; i ++) {
		alphaMask &= src[0];
		if (preMultiplyAlpha) {
			dst[i] = PreMultiplyAlphaAndPack(0xff, 0xff, 0xff, src[0]);
		} else {
			dst[i] = PackRGBA8888(0xff, 0xff, 0xff, src[0]);
		}
		src += deltaSrc;
	}
	return alphaMask != 0xff;
}
static bool Sample_RGB888_2_RGBA8888(void* dstRow, const uint8_t* src, uint32_t width, uint32_t deltaSrc, bool preMultiplyAlpha) {
	uint32_t* dst = (uint32_t*) dstRow;
	for (unsigned i = 0; i < width; i ++) {
		if (preMultiplyAlpha) {
			dst[i] = PreMultiplyAlphaAndPack(src[0], src[1], src[2], 0xff);
		} else {
			dst[i] = PackRGBA8888(src[0], src[1], src[2], 0xff);
		}
		src += deltaSrc;
	}
	return false;
}

static bool Sample_RGBA8888_2_RGB888(void* dstRow, const uint8_t* src, uint32_t width, uint32_t deltaSrc, bool preMultiplyAlpha) {
	uint8_t* dst = (uint8_t*) dstRow;
	for (unsigned i = 0; i < width * 3; i += 3) {
		uint32_t color = PreMultiplyAlpha(src[0], src[1], src[2], src[3]);
		dst[i] = ColorGetR(color);
		dst[i + 1] = ColorGetG(color);
		dst[i + 2] = ColorGetB(color);
		src += deltaSrc;
	}
	return false;
}
static bool Sample_ALPHA8_2_RGB888(void* dstRow, const uint8_t* src, uint32_t width, uint32_t deltaSrc, bool preMultiplyAlpha) {
	uint8_t* dst = (uint8_t*) dstRow;
	for (unsigned i = 0; i < width * 3; i += 3) {
		uint32_t color = PreMultiplyAlpha(0xff, 0xff, 0xff, src[0]);
		dst[i] = ColorGetR(color);
		dst[i + 1] = ColorGetG(color);
		dst[i + 2] = ColorGetB(color);
		src += deltaSrc;
	}
	return false;
}
static bool Sample_RGB888_2_RGB888(void* dstRow, const uint8_t* src, uint32_t width, uint32_t deltaSrc, bool preMultiplyAlpha) {
	uint8_t* dst = (uint8_t*) dstRow;
	for (unsigned i = 0; i < width * 3; i += 3) {
		dst[i] = src[0];
		dst[i + 1] = src[1];
		dst[i + 2] = src[2];
		src += deltaSrc;
	}
	return false;
}

static bool Sample_RGBA8888_2_ALPHA8(void* dstRow, const uint8_t* src, uint32_t width, uint32_t deltaSrc, bool preMultiplyAlpha) {
	uint8_t* dst = (uint8_t*) dstRow;
	unsigned alphaMask = 0xff;
	for (unsigned i = 0; i < width; i ++) {
		alphaMask &= src[3];
		dst[i] = src[3];
		src += deltaSrc;
	}
	return alphaMask != 0xff;
}
static bool Sample_ALPHA8_2_ALPHA8(void* dstRow, const uint8_t* src, uint32_t width, uint32_t deltaSrc, bool preMultiplyAlpha) {
	uint8_t* dst = (uint8_t*) dstRow;
	unsigned alphaMask = 0xff;
	for (unsigned i = 0; i < width; i ++) {
		alphaMask &= src[0];
		dst[i] = src[0];
		src += deltaSrc;
	}
	return alphaMask != 0xff;
}
static bool Sample_RGB888_2_ALPHA8(void* dstRow, const uint8_t* src, uint32_t width, uint32_t deltaSrc, bool preMultiplyAlpha) {
	uint8_t* dst = (uint8_t*) dstRow;
	memset(dst, 0xff, width);
	return false;
}

static bool Sample_RGBA8888_2_RGB565(void* dstRow, const uint8_t* src, uint32_t width, uint32_t deltaSrc, bool preMultiplyAlpha) {
	uint16_t* dst = (uint16_t*) dstRow;
	for (unsigned i = 0; i < width; i ++) {
		uint32_t color = PreMultiplyAlpha(src[0], src[1], src[2], src[3]);
		dst[i] = ((ColorGetR(color) >> 3) << 11) | ((ColorGetG(color) >> 2) << 5) | (ColorGetB(color) >> 3);
		src += deltaSrc;
	}
	return false;
}
static bool Sample_ALPHA8_2_RGB565(void* dstRow, const uint8_t* src, uint32_t width, uint32_t deltaSrc, bool preMultiplyAlpha) {
	uint16_t* dst = (uint16_t*) dstRow;
	for (unsigned i = 0; i < width; i ++) {
		uint32_t color = PreMultiplyAlpha(0xff, 0xff, 0xff, src[0]);
		dst[i] = ((ColorGetR(color) >> 3) << 11) | ((ColorGetG(color) >> 2) << 5) | (ColorGetB(color) >> 3);
		src += deltaSrc;
	}
	return false;
}
static bool Sample_RGB888_2_RGB565(void* dstRow, const uint8_t* src, uint32_t width, uint32_t deltaSrc, bool preMultiplyAlpha) {
	uint16_t* dst = (uint16_t*) dstRow;
	for (unsigned i = 0; i < width; i ++) {
		uint32_t color = ColorSetRGBA(src[0], src[1], src[2], 0xff);
		dst[i] = ((ColorGetR(color) >> 3) << 11) | ((ColorGetG(color) >> 2) << 5) | (ColorGetB(color) >> 3);
		src += deltaSrc;
	}
	return false;
}

uint32_t convertColorFormat(uint32_t srcColor, PixelFormat srcFormat, PixelFormat dstFormat) {
	if (dstFormat == PixelFormat::UNKONWN || srcFormat == dstFormat) {
		return srcColor;
	}

	return srcColor;
}

ImageSampler::ImageSampler(PixelFormat srcFormat, PixelFormat dstFormat, unsigned samplesize, bool preMultiplyAlpha) : mSampleSize(samplesize), mPreMultiplyAlpha(preMultiplyAlpha) {
	if (dstFormat == PixelFormat::UNKONWN) {
		dstFormat = srcFormat;
	}
	RowProc rowProc = nullptr;
	switch (dstFormat) {
		case PixelFormat::RGBA8888: {
			switch (srcFormat) {
				case PixelFormat::RGBA8888:
					rowProc = Sample_RGBA8888_2_RGBA8888;
					break;
				case PixelFormat::ALPHA8:
					rowProc = Sample_ALPHA8_2_RGBA8888;
					break;
				case PixelFormat::RGB888:
					rowProc = Sample_RGB888_2_RGBA8888;
					break;
				default:
					break;
			}
			break;
		}
		case PixelFormat::RGB888: {
			switch (srcFormat) {
				case PixelFormat::RGBA8888:
					rowProc = Sample_RGBA8888_2_RGB888;
					break;
				case PixelFormat::ALPHA8:
					rowProc = Sample_ALPHA8_2_RGB888;
					break;
				case PixelFormat::RGB888:
					rowProc = Sample_RGB888_2_RGB888;
					break;
				default:
					break;
			}
			break;
		}
		case PixelFormat::ALPHA8: {
			switch (srcFormat) {
				case PixelFormat::RGBA8888:
					rowProc = Sample_RGBA8888_2_ALPHA8;
					break;
				case PixelFormat::ALPHA8:
					rowProc = Sample_ALPHA8_2_ALPHA8;
					break;
				case PixelFormat::RGB888:
					rowProc = Sample_RGB888_2_ALPHA8;
					break;
				default:
					break;
			}
			break;
		}
		case PixelFormat::RGB565: {
			switch (srcFormat) {
				case PixelFormat::RGBA8888:
					rowProc = Sample_RGBA8888_2_RGB565;
					break;
				case PixelFormat::ALPHA8:
					rowProc = Sample_ALPHA8_2_RGB565;
					break;
				case PixelFormat::RGB888:
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
	return mRowProc(dst, src, width, deltaSrc, mPreMultiplyAlpha);
}

}
}


