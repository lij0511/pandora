/*
 * BitmapFactory.cpp
 *
 *  Created on: 2015年12月3日
 *      Author: lijing
 */

#include "pola/io/FileInputStream.h"
#include "pola/graphic/image/ImageDecoder.h"

#include <stdio.h>
#include <string.h>
#include "pola/graphic/ImageFactory.h"

namespace pola {
namespace graphic {

Image* ImageFactory::decodeFile(const char *file, PixelFormat format) {
	io::InputStream* is = new io::FileInputStream(file);
	Image* bitmap = decodeStream(is, format);
	is->close();
	delete is;
	return bitmap;
}

Image* ImageFactory::decodeStream(io::InputStream* is, PixelFormat format) {
	Image* bitmap = nullptr;
	ImageDecoder* decoder = ImageDecoder::Factory(is);
	if (decoder) {
//		decoder->disablePreMultipyAlpha();
		decoder->decode(is, bitmap, format);
		delete decoder;
	}
	return bitmap;
}

}
}
