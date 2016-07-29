/*
 * ImageDecoder.cpp
 *
 *  Created on: 2015年12月12日
 *      Author: lijing
 */

#include "pola/log/Log.h"
#include "pola/graphic/image/ImageDecoder.h"
#include "pola/graphic/image/ImageDecoderFactory.h"

namespace pola {
namespace graphic {

ImageDecoder::ImageDecoder() : mPeeker(nullptr), mPreMultiplyAlpha(true) {
}

ImageDecoder::~ImageDecoder() {
}

ImageDecoder* ImageDecoder::Factory(io::InputStream* is) {
	return newDecoder(is);
}

}
}
