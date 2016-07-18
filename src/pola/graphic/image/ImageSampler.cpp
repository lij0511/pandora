/*
 * ImageSampler.cpp
 *
 *  Created on: 2016年7月17日
 *      Author: lijing
 */

#include "pola/graphic/image/ImageSampler.h"

namespace pola {
namespace graphic {

ImageSampler::ImageSampler(uint32_t width, uint32_t height, unsigned sampleSize) :
	mWidth(width), mHeight(height), mSampleSize(sampleSize), mBitmap(nullptr), mFormat(Bitmap::Format::UNKONWN) {
}

ImageSampler::~ImageSampler() {
}

bool ImageSampler::beginSample(Bitmap* bitmap, Bitmap::Format format) {
	mBitmap = bitmap;
	mFormat = format;
	if (mFormat == Bitmap::Format::UNKONWN) {
		return false;
	}

	return true;
}

void ImageSampler::sample(unsigned row, const uint8_t* rowPixels) {
}

} /* namespace graphic */
} /* namespace pola */
