/*
 * PNGImageDecoder.cpp
 *
 *  Created on: 2015年12月13日
 *      Author: lijing
 */

#include "log/Log.h"
#include "graphic/image/ImageDecoderFactory.h"
#include "graphic/image/PNGImageDecoder.h"

/* These were dropped in libpng >= 1.4 */
#ifndef png_infopp_NULL
#define png_infopp_NULL NULL
#endif

#ifndef png_bytepp_NULL
#define png_bytepp_NULL NULL
#endif

#ifndef int_p_NULL
#define int_p_NULL NULL
#endif

#ifndef png_flush_ptr_NULL
#define png_flush_ptr_NULL NULL
#endif

#define PNG_BYTES_TO_CHECK 4

namespace pola {
namespace graphic {

PNGImageDecoder::PNGImageDecoder() {
}

PNGImageDecoder::~PNGImageDecoder() {
}

static void png_read_fn(png_structp png_ptr, png_bytep data, png_size_t length) {
	io::InputStream* is = (io::InputStream*) png_get_io_ptr(png_ptr);
	size_t bytes = is->read(data, length);
	if (bytes != length) {
		png_error(png_ptr, "Read Error!");
	}
}

Bitmap* PNGImageDecoder::decode(io::InputStream* is) {
	png_structp png_ptr;
	png_infop info_ptr;

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr)
	{
		LOGE("ReadPngFile: Failed to create png_ptr");
		return nullptr;
	}
	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
	{
		png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);
		LOGE("ReadPngFile: Failed to create info_ptr");
		return nullptr;
	}
	if (setjmp(png_jmpbuf(png_ptr)))
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
		LOGE("ReadPngFile: Failed to read the PNG file");
		return nullptr;
	}

	png_set_read_fn(png_ptr, (void *)is, png_read_fn);

	png_set_keep_unknown_chunks(png_ptr, PNG_HANDLE_CHUNK_ALWAYS, (png_byte*)"", 0);

	png_read_info(png_ptr, info_ptr);

	png_uint_32 origWidth, origHeight;
	int bitDepth, colorType, interlaceType = 0;
	png_get_IHDR(png_ptr, info_ptr, &origWidth, &origHeight, &bitDepth,
				 &colorType, &interlaceType, int_p_NULL, int_p_NULL);

	if (colorType==PNG_COLOR_TYPE_PALETTE) {
		png_set_packing(png_ptr);
		png_set_palette_to_rgb(png_ptr); //Expand data to 24-bit RGB or 32-bit RGBA if alpha available.
	}

	/* tell libpng to strip 16 bit/color files down to 8 bits/color */
	if (bitDepth == 16) {
		png_set_strip_16(png_ptr);
	}
	/* Extract multiple pixels with bit depths of 1, 2, and 4 from a single
	 * byte into separate bytes (useful for paletted and grayscale images). */
	if (bitDepth < 8) {
		png_set_packing(png_ptr);
	}
	/* Expand grayscale images to the full 8 bits from 1, 2, or 4 bits/pixel */
	if (colorType == PNG_COLOR_TYPE_GRAY && bitDepth < 8) {
		png_set_expand_gray_1_2_4_to_8(png_ptr);
	}

	if (colorType == PNG_COLOR_TYPE_GRAY_ALPHA) {
		png_set_gray_to_rgb(png_ptr);
	}

	if (colorType == PNG_COLOR_TYPE_RGB) {
		png_set_filler(png_ptr, 0xff, PNG_FILLER_AFTER);
	}

	if (setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
		return nullptr;
	}

	const int number_passes = (interlaceType != PNG_INTERLACE_NONE) ?
	                              png_set_interlace_handling(png_ptr) : 1;
	png_read_update_info(png_ptr, info_ptr);

	Bitmap* bitmap;
	Bitmap::Format format;
	switch (colorType) {
		case PNG_COLOR_TYPE_RGB:
		case PNG_COLOR_TYPE_GRAY_ALPHA:
			format = Bitmap::RGB888;
			break;
		case PNG_COLOR_TYPE_GRAY:
			format = Bitmap::ALPHA8;
			break;
		case PNG_COLOR_TYPE_RGB_ALPHA:
		case PNG_COLOR_TYPE_PALETTE:
			format = Bitmap::RGBA8888;
			break;
		default:
			png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
			return nullptr;
	}
	bitmap = Bitmap::create();
	bitmap->set(origWidth, origHeight, format);

	for (int i = 0; i < number_passes; i++) {
		uint8_t* bmRow = bitmap->pixels();
		for (png_uint_32 y = 0; y < origHeight; y++) {
			png_read_rows(png_ptr, &bmRow, png_bytepp_NULL, 1);
			bmRow += bitmap->rowBytes();
		}
	}

	return bitmap;
}

static bool is_png(io::InputStream* is) {
    char buf[PNG_BYTES_TO_CHECK];
    if (is->read(buf, PNG_BYTES_TO_CHECK) == PNG_BYTES_TO_CHECK &&
        !png_sig_cmp((png_bytep) buf, (png_size_t)0, PNG_BYTES_TO_CHECK)) {
        return true;
    }
    return false;
}

static ImageDecoder* png_image_factory(io::InputStream* is) {
	if (is_png(is)) {
		return new PNGImageDecoder;
	}
	return nullptr;
}

ImageDecoderReg png_reg(png_image_factory);

}
}
