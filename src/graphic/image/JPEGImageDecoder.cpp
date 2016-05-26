/*
 * JPEGImageDecoder.cpp
 *
 *  Created on: 2015年12月30日
 *      Author: lijing
 */

#include "log/Log.h"
#include "graphic/image/ImageDecoderFactory.h"
#include "graphic/image/JPEGImageDecoder.h"

#include <string.h>

namespace pola {
namespace graphic {

/* Automatically clean up after throwing an exception */
class JPEGAutoClean {
public:
    JPEGAutoClean(): cinfo_ptr(NULL) {}
    ~JPEGAutoClean() {
        if (cinfo_ptr) {
            jpeg_destroy_decompress(cinfo_ptr);
        }
    }
    void set(jpeg_decompress_struct* info) {
        cinfo_ptr = info;
    }
private:
    jpeg_decompress_struct* cinfo_ptr;
};

/////////////////////////////// jpeg_util //////////////////////////////////////
static void pola_jpeg_init_source(j_decompress_ptr cinfo) {
	pola_jpeg_source_mgr*  src = (pola_jpeg_source_mgr*) cinfo->src;
    src->next_input_byte = (const JOCTET*) src->fBuffer;
    src->bytes_in_buffer = 0;
    if (!src->fStream->rewind()) {
        cinfo->err->error_exit((j_common_ptr) cinfo);
    }
}
static boolean pola_jpeg_fill_input_buffer(j_decompress_ptr cinfo) {
	pola_jpeg_source_mgr* src = (pola_jpeg_source_mgr*) cinfo->src;
    size_t bytes = src->fStream->read(src->fBuffer, pola_jpeg_source_mgr::kBufferSize);
    // note that JPEG is happy with less than the full read,
    // as long as the result is non-zero
    if (bytes == 0) {
        return FALSE;
    }
    src->next_input_byte = (const JOCTET*) src->fBuffer;
    src->bytes_in_buffer = bytes;
    return TRUE;
}
static void pola_jpeg_skip_input_data(j_decompress_ptr cinfo, long num_bytes) {
	pola_jpeg_source_mgr*  src = (pola_jpeg_source_mgr*) cinfo->src;
    if (num_bytes > (long)src->bytes_in_buffer) {
        size_t bytesToSkip = num_bytes - src->bytes_in_buffer;
        while (bytesToSkip > 0) {
            size_t bytes = src->fStream->skip(bytesToSkip);
            if (bytes <= 0 || bytes > bytesToSkip) {
                cinfo->err->error_exit((j_common_ptr)cinfo);
                return;
            }
            bytesToSkip -= bytes;
        }
        src->next_input_byte = (const JOCTET*) src->fBuffer;
        src->bytes_in_buffer = 0;
    } else {
        src->next_input_byte += num_bytes;
        src->bytes_in_buffer -= num_bytes;
    }
}
static void pola_jpeg_term_source(j_decompress_ptr /*cinfo*/) {
}
pola_jpeg_source_mgr::pola_jpeg_source_mgr(io::InputStream* is) :
	fStream(is) {
	init_source = pola_jpeg_init_source;
	fill_input_buffer = pola_jpeg_fill_input_buffer;
	skip_input_data = pola_jpeg_skip_input_data;
	resync_to_restart = jpeg_resync_to_restart;
	term_source = pola_jpeg_term_source;
}
pola_jpeg_source_mgr::~pola_jpeg_source_mgr() {
}

static void pola_jpeg_error_exit(j_common_ptr cinfo) {
    pola_jpeg_error_mgr* error = (pola_jpeg_error_mgr*) cinfo->err;
    (*error->output_message) (cinfo);

    /* Let the memory manager delete any temp files before we die */
    jpeg_destroy(cinfo);

    longjmp(error->fJmpBuf, -1);
}


/////////////////////////////// JPEGImageDecoder //////////////////////////////////////
JPEGImageDecoder::JPEGImageDecoder() {
}

JPEGImageDecoder::~JPEGImageDecoder() {
}

static Bitmap::Format selectColorType(jpeg_decompress_struct* cinfo) {
	Bitmap::Format format = Bitmap::RGB565;
	switch (cinfo->jpeg_color_space) {
		case JCS_CMYK:
			// Fall through.
		case JCS_YCCK:
			// libjpeg cannot convert from CMYK or YCCK to RGB - here we set up
			// so libjpeg will give us CMYK samples back and we will later
			// manually convert them to RGB
			cinfo->out_color_space = JCS_CMYK;
			format = Bitmap::RGBA8888;
			break;
		case JCS_GRAYSCALE:
			format = Bitmap::ALPHA8;
			break;
		default:
			cinfo->out_color_space = JCS_RGB;
			break;
	}
	return format;
}

static uint8_t MulDiv255Round(uint8_t a, uint8_t b) {
	unsigned prod = (a * b) + 128;
	return (prod + (prod >> 8)) >> 8;
}
// Convert a scanline of CMYK samples to RGBX in place. Note that this
// method moves the "scanline" pointer in its processing
static void convert_CMYK_to_RGB(unsigned char* scanline, unsigned char* output, uint32_t width) {
    // At this point we've received CMYK pixels from libjpeg. We
    // perform a crude conversion to RGB (based on the formulae
    // from easyrgb.com):
    //  CMYK -> CMY
    //    C = ( C * (1 - K) + K )      // for each CMY component
    //  CMY -> RGB
    //    R = ( 1 - C ) * 255          // for each RGB component
    // Unfortunately we are seeing inverted CMYK so all the original terms
    // are 1-. This yields:
    //  CMYK -> CMY
    //    C = ( (1-C) * (1 - (1-K) + (1-K) ) -> C = 1 - C*K
    // The conversion from CMY->RGB remains the same
    for (uint32_t x = 0; x < width; ++x, scanline += 4, output += 4) {
    	output[0] = MulDiv255Round(scanline[0], scanline[3]);
    	output[1] = MulDiv255Round(scanline[1], scanline[3]);
    	output[2] = MulDiv255Round(scanline[2], scanline[3]);
    	output[3] = 255;
    }
}

Bitmap* JPEGImageDecoder::decode(io::InputStream* is) {
	JPEGAutoClean autoClean;
	struct jpeg_decompress_struct  cinfo;

	struct pola_jpeg_error_mgr errorManager;
	cinfo.err = jpeg_std_error(&errorManager);
	errorManager.error_exit = pola_jpeg_error_exit;

	// All objects need to be instantiated before this setjmp call so that
	// they will be cleaned up properly if an error occurs.
	if (setjmp(errorManager.fJmpBuf)) {
		LOGE("ReadJpegFile: Failed to setjmp.\n");
		return nullptr;
	}
	pola_jpeg_source_mgr       srcManager(is);

	jpeg_create_decompress(&cinfo);
	cinfo.src = &srcManager;

	autoClean.set(&cinfo);

	int status = jpeg_read_header(&cinfo, TRUE);
	if (status != JPEG_HEADER_OK) {
		LOGE("ReadJpegFile: Failed to read header.\n");
		return nullptr;
	}

	cinfo.dct_method = JDCT_ISLOW;
	Bitmap::Format format = selectColorType(&cinfo);

	if (!jpeg_start_decompress(&cinfo)) {
		LOGE("ReadJpegFile: Failed to jpeg_start_decompress.\n");
		return nullptr;
	}

	// XXX Why?  glTexImage2D一行像素字节数为奇数有问题？？？。
	/*uint32_t fixed = cinfo.output_width % 2;*/
	Bitmap* bitmap = Bitmap::create();;
	bitmap->set(cinfo.output_width/* - fixed*/, cinfo.output_height, format);
	uint32_t rowBytes = bitmap->rowBytes();
	unsigned char* srcRow = bitmap->pixels();
	// now loop through scanlines
	if (JCS_CMYK == cinfo.out_color_space) {
		JSAMPLE* rowptr = (JSAMPLE*) malloc(sizeof(JSAMPLE) * 4 * cinfo.output_width);
		while (cinfo.output_scanline < cinfo.output_height) {
			jpeg_read_scanlines(&cinfo, &rowptr, 1);
			convert_CMYK_to_RGB(rowptr, srcRow, cinfo.output_width);
			srcRow += rowBytes;
		}
		free(rowptr);
	} else {
		if (format == Bitmap::RGB565) {
			JSAMPLE* rowptr = (JSAMPLE*) malloc(sizeof(JSAMPLE) * 3 * cinfo.output_width);
			uint16_t* srcRow_s = (uint16_t*) srcRow;
			while (cinfo.output_scanline < cinfo.output_height) {
				JSAMPLE* scanline = rowptr;
				jpeg_read_scanlines(&cinfo, &rowptr, 1);
				for (uint32_t x = 0; x < cinfo.output_width; ++x, scanline += 3, srcRow_s += 1) {
					srcRow_s[0] = (uint16_t) (((unsigned(scanline[0]) << 8) & 0xF800) |
							((unsigned(scanline[1]) << 3) & 0x7E0)  |
							((unsigned(scanline[2]) >> 3)));
				}
			}
		} else {
			while (cinfo.output_scanline < cinfo.output_height) {
				JSAMPLE* rowptr = (JSAMPLE*) srcRow;
				jpeg_read_scanlines(&cinfo, &rowptr, 1);
				srcRow += rowBytes;
			}
		}

	}

	jpeg_finish_decompress(&cinfo);
	return bitmap;
}

static bool is_jpeg(io::InputStream* is) {
	static const unsigned char gHeader[] = { 0xFF, 0xD8, 0xFF };
	static const size_t HEADER_SIZE = sizeof(gHeader);

	char buffer[HEADER_SIZE];
	size_t len = is->read(buffer, HEADER_SIZE);

	if (len != HEADER_SIZE) {
		return false;   // can't read enough
	}
	if (memcmp(buffer, gHeader, HEADER_SIZE)) {
		return false;
	}
	return true;
}

static ImageDecoder* jpeg_image_factory(io::InputStream* is) {
	if (is_jpeg(is)) {
		return new JPEGImageDecoder;
	}
	return nullptr;
}

ImageDecoderReg jpeg_reg(jpeg_image_factory);
}
}
