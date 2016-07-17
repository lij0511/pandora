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
	ImageSampler(Bitmap* bitmap, Bitmap::Format sourceFormat, unsigned sampleSize = 1);
	virtual ~ImageSampler();

	bool needsSample() const;

	void sample(unsigned row, const uint8_t* rowPixels);

private:
	Bitmap* mBitmap;
	Bitmap::Format mFormat;
	unsigned mSampleSize;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_IMAGESAMPLER_H_ */
