/*
 * JPEGImageDecoder.cpp
 *
 *  Created on: 2015年12月30日
 *      Author: lijing
 */

#include "pola/log/Log.h"
#include "pola/graphic/image/ImageDecoderFactory.h"
#include "pola/graphic/image/JPEGImageDecoder.h"
#include "ImageSampler.h"

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
    LOGE("pola_jpeg_error_exit. %d\n", error->msg_code);
    /* Let the memory manager delete any temp files before we die */
    jpeg_destroy(cinfo);

    longjmp(error->fJmpBuf, -1);
}


/////////////////////////////// JPEGImageDecoder //////////////////////////////////////
JPEGImageDecoder::JPEGImageDecoder() {
}

JPEGImageDecoder::~JPEGImageDecoder() {
}

static PixelFormat selectColorType(jpeg_decompress_struct* cinfo) {
	PixelFormat format = PixelFormat::RGB888;
	switch (cinfo->jpeg_color_space) {
		case JCS_CMYK:
			// Fall through.
		case JCS_YCCK:
			// libjpeg cannot convert from CMYK or YCCK to RGB - here we set up
			// so libjpeg will give us CMYK samples back and we will later
			// manually convert them to RGB
			cinfo->out_color_space = JCS_CMYK;
			break;
		case JCS_GRAYSCALE:
			format = PixelFormat::ALPHA8;
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
    for (uint32_t x = 0; x < width; ++x, scanline += 4, output += 3) {
    	output[0] = MulDiv255Round(scanline[0], scanline[3]);
    	output[1] = MulDiv255Round(scanline[1], scanline[3]);
    	output[2] = MulDiv255Round(scanline[2], scanline[3]);
    }
}

bool JPEGImageDecoder::decode(io::InputStream* is, Bitmap*& bitmap, PixelFormat preFormat) {
	JPEGAutoClean autoClean;
	struct jpeg_decompress_struct  cinfo;

	struct pola_jpeg_error_mgr errorManager;
	cinfo.err = jpeg_std_error(&errorManager);
	errorManager.error_exit = pola_jpeg_error_exit;

	// All objects need to be instantiated before this setjmp call so that
	// they will be cleaned up properly if an error occurs.
	if (setjmp(errorManager.fJmpBuf)) {
		LOGE("ReadJpegFile: Failed to setjmp.\n");
		return false;
	}
	pola_jpeg_source_mgr       srcManager(is);

	jpeg_create_decompress(&cinfo);
	cinfo.src = &srcManager;

	autoClean.set(&cinfo);

	int status = jpeg_read_header(&cinfo, TRUE);
	if (status != JPEG_HEADER_OK) {
		LOGE("ReadJpegFile: Failed to read header.\n");
		return false;
	}

	cinfo.dct_method = JDCT_ISLOW;
	PixelFormat format = selectColorType(&cinfo);

	if (!jpeg_start_decompress(&cinfo)) {
		LOGE("ReadJpegFile: Failed to jpeg_start_decompress.\n");
		return false;
	}

	if (preFormat == PixelFormat::UNKONWN) {
		preFormat = format;
	}

	if (bitmap == nullptr) {
		bitmap = Bitmap::create();
	}
	bitmap->set(cinfo.output_width, cinfo.output_height, preFormat);
	uint32_t rowBytes = bitmap->rowBytes();
	unsigned char* srcRow = bitmap->pixels();
	// TODO Preformat convert.
	// now loop through scanlines
	if (format == preFormat && JCS_CMYK != cinfo.out_color_space) {
		while (cinfo.output_scanline < cinfo.output_height) {
			JSAMPLE* rowptr = (JSAMPLE*) srcRow;
			jpeg_read_scanlines(&cinfo, &rowptr, 1);
			srcRow += rowBytes;
		}
	} else if (JCS_CMYK == cinfo.out_color_space) {
		ImageSampler* sampler = nullptr;
		JSAMPLE* rowptr = (JSAMPLE*) malloc(sizeof(JSAMPLE) * 4 * cinfo.output_width);
		uint8_t* tmp = nullptr;
		if (format == preFormat) {
			tmp = (uint8_t*) malloc(sizeof(uint8_t) * 3 * cinfo.output_width);
			sampler = new ImageSampler(format, preFormat, 1, mPreMultiplyAlpha);
		}
		while (cinfo.output_scanline < cinfo.output_height) {
			jpeg_read_scanlines(&cinfo, &rowptr, 1);
			if (tmp != nullptr) {
				convert_CMYK_to_RGB(rowptr, tmp, cinfo.output_width);
				sampler->sampleScanline(srcRow, tmp, cinfo.output_width, Bitmap::getByteCountPerPixel(format));
			} else {
				convert_CMYK_to_RGB(rowptr, srcRow, cinfo.output_width);
			}
			srcRow += rowBytes;
		}
		free(rowptr);
		if (tmp != nullptr) {
			free(tmp);
			delete sampler;
		}
	} else {
		ImageSampler sampler(format, preFormat);
		size_t rowSize = sizeof(uint8_t) * Bitmap::getByteCountPerPixel(format) * cinfo.output_width;
		uint8_t* rowptr = (uint8_t*) malloc(rowSize);
		JSAMPLE* jsample = (JSAMPLE*) rowptr;
		while (cinfo.output_scanline < cinfo.output_height) {
			jpeg_read_scanlines(&cinfo, &jsample, 1);
			sampler.sampleScanline(srcRow, rowptr, cinfo.output_width, Bitmap::getByteCountPerPixel(format));
			srcRow += rowBytes;
		}
		free(rowptr);
	}

	jpeg_finish_decompress(&cinfo);
	return true;
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

bool JPEGImageDecoder::decodeable(io::InputStream* is) {
	return is_jpeg(is);
}

static ImageDecoder* jpeg_image_factory(io::InputStream* is) {
	if (is_jpeg(is)) {
		return new JPEGImageDecoder;
	}
	return nullptr;
}

void JPEGImageDecoder::reg() {
	ImageDecoderReg reg(jpeg_image_factory);
}
}
}
