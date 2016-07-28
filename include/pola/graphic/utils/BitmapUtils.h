/*
 * BitmapUtils.h
 *
 *  Created on: 2016年7月27日
 *      Author: lijing
 */

#ifndef POLA_BITMAPUTILS_H_
#define POLA_BITMAPUTILS_H_

#include "pola/graphic/Bitmap.h"
#include "pola/graphic/Color.h"

namespace pola {
namespace graphic {

bool clearBitmap(Bitmap& bitmap, RGBA32 color);

enum BitmapScaleMode {
	NEAREST,
	BILINEAR,
};

bool scaleBitmap(const Bitmap& src, Bitmap*& dst, float scaleW, float scaleH, BitmapScaleMode scaleMode = BILINEAR);

uint8_t PreMultiplyAlpha(uint8_t a, uint8_t b);
uint32_t PreMultiplyAlpha(uint32_t rgba);


typedef bool (*RowProc)(void* dstRow,
                            const uint8_t* src,
                            uint32_t width, uint32_t deltaSrc);

uint32_t convertColorFormat(uint32_t srcColor, Bitmap::Format srcFormat, Bitmap::Format dstFormat);

class ImageSampler {
public:
	ImageSampler(Bitmap::Format srcFormat, Bitmap::Format dstFormat);
	bool sampleScanline(void* dst, const uint8_t* src, uint32_t width, uint32_t deltaSrc);
private:
	RowProc mRowProc;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_BITMAPUTILS_H_ */
