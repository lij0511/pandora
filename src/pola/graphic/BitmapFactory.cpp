/*
 * BitmapFactory.cpp
 *
 *  Created on: 2015年12月3日
 *      Author: lijing
 */

#include "pola/io/FileInputStream.h"
#include "pola/graphic/BitmapFactory.h"
#include "pola/graphic/image/ImageDecoder.h"

#include <stdio.h>
#include <string.h>

namespace pola {
namespace graphic {

Bitmap* BitmapFactory::decodeFile(const char *file) {
	io::InputStream* is = new io::FileInputStream(file);
	Bitmap* bitmap = decodeStream(is);
	is->close();
	delete is;
	return bitmap;
}

Bitmap* BitmapFactory::decodeStream(io::InputStream* is) {
	Bitmap* bitmap = nullptr;
	ImageDecoder* decoder = ImageDecoder::Factory(is);
	if (decoder) {
		bitmap = decoder->decode(is);
		delete decoder;
	}
	return bitmap;
}

}
}
