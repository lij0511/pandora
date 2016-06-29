/*
 * BMPImageDecoder.h
 *
 *  Created on: 2016年5月26日
 *      Author: lijing
 */

#ifndef BMPIMAGEDECODER_H_
#define BMPIMAGEDECODER_H_

#include "graphic/image/ImageDecoder.h"

namespace pola {
namespace graphic {

/*
 *
 */
class BMPImageDecoder: public ImageDecoder {
public:
	BMPImageDecoder();
	virtual ~BMPImageDecoder();

	virtual Bitmap* decode(io::InputStream* is) override;

	static bool decodeable(io::InputStream* is);
};

} /* namespace graphic */
} /* namespace pola */

#endif /* BMPIMAGEDECODER_H_ */
