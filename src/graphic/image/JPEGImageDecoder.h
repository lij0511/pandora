/*
 * JPEGImageDecoder.h
 *
 *  Created on: 2015年12月30日
 *      Author: lijing
 */

#ifndef POLA_JPEGIMAGEDECODER_H_
#define POLA_JPEGIMAGEDECODER_H_

#include "graphic/image/ImageDecoder.h"

#include <stdio.h>
extern "C" {
    #include "jpeglib.h"
    #include "jerror.h"
}
#include <setjmp.h>

namespace pola {
namespace graphic {

struct pola_jpeg_source_mgr : jpeg_source_mgr {
	pola_jpeg_source_mgr(io::InputStream* is);
	~pola_jpeg_source_mgr();

	// fStream is ref'ed and unref'ed
	io::InputStream*       fStream;
	enum {
		kBufferSize = /*1024*/ 1024 * 512
	};
	char    fBuffer[kBufferSize];
};
/* Our error-handling struct.
 *
*/
struct pola_jpeg_error_mgr : jpeg_error_mgr {
    jmp_buf fJmpBuf;
};

class JPEGImageDecoder: public ImageDecoder {
public:
	JPEGImageDecoder();
	virtual ~JPEGImageDecoder();

	virtual Bitmap* decode(io::InputStream* is) override;

	static bool decodeable(io::InputStream* is);
};

}
}

#endif /* POLA_JPEGIMAGEDECODER_H_ */
