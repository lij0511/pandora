/*
 * BMPImageDecoder.h
 *
 *  Created on: 2016年5月26日
 *      Author: lijing
 */

#ifndef POLA_BMPIMAGEDECODER_H_
#define POLA_BMPIMAGEDECODER_H_

#include "pola/graphic/image/ImageDecoder.h"

namespace pola {
namespace graphic {

/*
 *
 */
class BMPImageDecoder: public ImageDecoder {
public:
	BMPImageDecoder();
	virtual ~BMPImageDecoder();

	virtual bool decode(io::InputStream* is, Bitmap*& bitmap, PixelFormat format = PixelFormat::UNKONWN);

	static bool decodeable(io::InputStream* is);

	static void reg();

};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_BMPIMAGEDECODER_H_ */
