/*
 * BitmapFactory.cpp
 *
 *  Created on: 2015年12月3日
 *      Author: lijing
 */

#include "graphic/BitmapFactory.h"
#include "graphic/image/PNGImageDecoder.h"
#include "io/FileInputStream.h"

#include <stdio.h>
#include <string.h>
#include <png.h>

namespace pola {
namespace graphic {

Bitmap* BitmapFactory::decodeFile(const char *file) {
	Bitmap* bitmap = nullptr;
	io::InputStream* is = new io::FileInputStream(file);
	ImageDecoder* decoder = ImageDecoder::Factory(is);
	if (decoder) {
		bitmap = decoder->decode(is);
		delete decoder;
	}
	is->close();
	delete is;
	return bitmap;
}

}
}
