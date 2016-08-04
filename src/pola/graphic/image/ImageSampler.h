/*
 * ImageSampler.h
 *
 *  Created on: 2016年7月29日
 *      Author: lijing
 */

#ifndef POLA_IMAGESAMPLER_H_
#define POLA_IMAGESAMPLER_H_

#include "pola/graphic/Bitmap.h"

namespace pola {
namespace graphic {

typedef bool (*RowProc)(void* dstRow,
                            const uint8_t* src,
                            uint32_t width, uint32_t deltaSrc, bool preMultiplyAlpha);

class ImageSampler {
public:
	ImageSampler(PixelFormat srcFormat, PixelFormat dstFormat, unsigned samplesize = 1, bool preMultiplyAlpha = true);
	bool sampleScanline(void* dst, const uint8_t* src, uint32_t width, uint32_t deltaSrc);
private:
	RowProc mRowProc;

	/* TODO 暂时不支持 */
	unsigned mSampleSize;
	bool mPreMultiplyAlpha;

};

}
}

#endif /* POLA_IMAGESAMPLER_H_ */
