/*
 * ImageDecoder.cpp
 *
 *  Created on: 2015年12月12日
 *      Author: lijing
 */

#include "log/Log.h"
#include "graphic/image/ImageDecoder.h"
#include "graphic/image/ImageDecoderFactory.h"

namespace pola {
namespace graphic {

ImageDecoder::ImageDecoder() {
}

ImageDecoder::~ImageDecoder() {
}

ImageDecoder* ImageDecoder::Factory(io::InputStream* is) {
	return newDecoder(is);
}

}
}
