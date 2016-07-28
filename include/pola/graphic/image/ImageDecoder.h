/*
 * ImageDecoder.h
 *
 *  Created on: 2015年12月12日
 *      Author: lijing
 */

#ifndef POLA_IMAGEDECODER_H_
#define POLA_IMAGEDECODER_H_

#include "pola/graphic/Bitmap.h"
#include "pola/graphic/utils/BitmapUtils.h"
#include "pola/io/InputStream.h"

namespace pola {
namespace graphic {

class ImageDecoder {
public:
	virtual ~ImageDecoder();

	virtual Bitmap* decode(io::InputStream* is, Bitmap::Format format = Bitmap::Format::UNKONWN) = 0;

	static ImageDecoder* Factory(io::InputStream* is);
};

}
}

#endif /* POLA_IMAGEDECODER_H_ */
