/*
 * BMPImageDecoder.cpp
 *
 *  Created on: 2016年5月26日
 *      Author: lijing
 */

#include <string.h>

#include "graphic/image/BMPImageDecoder.h"
#include "graphic/image/ImageDecoderFactory.h"

namespace pola {
namespace graphic {

BMPImageDecoder::BMPImageDecoder() {
}

BMPImageDecoder::~BMPImageDecoder() {
}

Bitmap* BMPImageDecoder::decode(io::InputStream* is) {

	return nullptr;
}

static bool is_bmp(io::InputStream* is) {
	static const char kBmpMagic[] = { 'B', 'M' };
	char buffer[sizeof(kBmpMagic)];
	return is->read(buffer, sizeof(kBmpMagic)) == sizeof(kBmpMagic) &&
		!memcmp(buffer, kBmpMagic, sizeof(kBmpMagic));
}

static ImageDecoder* bmp_image_factory(io::InputStream* is) {
	if (is_bmp(is)) {
		return new BMPImageDecoder;
	}
	return nullptr;
}

ImageDecoderReg bmp_reg(bmp_image_factory);

} /* namespace graphic */
} /* namespace pola */
