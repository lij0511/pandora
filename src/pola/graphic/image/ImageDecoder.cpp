/*
 * ImageDecoder.cpp
 *
 *  Created on: 2015年12月12日
 *      Author: lijing
 */

#include "pola/log/Log.h"
#include "pola/graphic/image/ImageDecoder.h"
#include "pola/graphic/image/ImageDecoderFactory.h"
#include "pola/graphic/image/BMPImageDecoder.h"
#include "pola/graphic/image/JPEGImageDecoder.h"
#include "pola/graphic/image/PNGImageDecoder.h"

namespace pola {
namespace graphic {

ImageDecoder::~ImageDecoder() {
}

ImageDecoder* ImageDecoder::Factory(io::InputStream* is) {
//	return newDecoder(is);
	// TODO
	if (BMPImageDecoder::decodeable(is)) {
		if (is->rewind()) {
			return new BMPImageDecoder;
		}
		return nullptr;
	}
	if (!is->rewind()) {
		return nullptr;
	}

	if (JPEGImageDecoder::decodeable(is)) {
		if (is->rewind()) {
			return new JPEGImageDecoder;
		}
		return nullptr;
	}
	if (!is->rewind()) {
		return nullptr;
	}

	if (PNGImageDecoder::decodeable(is)) {
		if (is->rewind()) {
			return new PNGImageDecoder;
		}
		return nullptr;
	}
	if (!is->rewind()) {
		return nullptr;
	}
	return nullptr;
}

}
}
