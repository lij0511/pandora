/*
 * PNGImageDecoder.h
 *
 *  Created on: 2015年12月13日
 *      Author: lijing
 */

#ifndef POLA_PNGIMAGEDECODER_H_
#define POLA_PNGIMAGEDECODER_H_

#include "pola/graphic/image/ImageDecoder.h"

#include <png.h>

namespace pola {
namespace graphic {

class PNGImageDecoder: public ImageDecoder {
public:
	PNGImageDecoder();
	virtual ~PNGImageDecoder();

	virtual bool decode(io::InputStream* is, Bitmap*& bitmap, Bitmap::Format format = Bitmap::Format::UNKONWN);

	static bool decodeable(io::InputStream* is);

	static void reg();
};

}
}

#endif /* POLA_PNGIMAGEDECODER_H_ */
