/*
 * ImageSampler.cpp
 *
 *  Created on: 2016年7月17日
 *      Author: lijing
 */

#include "pola/graphic/image/ImageSampler.h"

namespace pola {
namespace graphic {

ImageSampler::ImageSampler(Bitmap* bitmap, Bitmap::Format sourceFormat, unsigned sampleSize) :
	mBitmap(bitmap), mFormat(sourceFormat), mSampleSize(sampleSize) {
}

ImageSampler::~ImageSampler() {
}

bool ImageSampler::needsSample() const {
	return (mFormat != Bitmap::Format::UNKONWN && mBitmap->getFormat() != mFormat) || mSampleSize > 1;
}

void ImageSampler::sample(unsigned row, const uint8_t* rowPixels) {
}

} /* namespace graphic */
} /* namespace pola */
