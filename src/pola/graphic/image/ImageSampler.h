/*
 * ImageSampler.h
 *
 *  Created on: 2016年7月17日
 *      Author: lijing
 */

#ifndef POLA_IMAGESAMPLER_H_
#define POLA_IMAGESAMPLER_H_

#include "pola/graphic/Bitmap.h"

namespace pola {
namespace graphic {

class ImageSampler {
public:
	ImageSampler(uint32_t width, uint32_t height, unsigned sampleSize = 1);
	virtual ~ImageSampler();

	bool beginSample(Bitmap* bitmap, Bitmap::Format format);

	void sample(unsigned row, const uint8_t* rowPixels);

private:
	uint32_t mWidth;
	uint32_t mHeight;
	unsigned mSampleSize;

	Bitmap* mBitmap;
	Bitmap::Format mFormat;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_IMAGESAMPLER_H_ */
