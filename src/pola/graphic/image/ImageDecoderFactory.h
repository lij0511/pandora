/*
 * ImageDecoderFactory.h
 *
 *  Created on: 2016年1月4日
 *      Author: lijing
 */

#ifndef POLA_IMAGEDECODERFACTORY_H_
#define POLA_IMAGEDECODERFACTORY_H_

#include "pola/io/InputStream.h"
#include "pola/graphic/image/ImageDecoder.h"

namespace pola {
namespace graphic {

typedef ImageDecoder* (*image_factory)(io::InputStream* is);

void image_factory_reg(image_factory f);
ImageDecoder* newDecoder(io::InputStream* is);

class ImageDecoderReg {
public:
	ImageDecoderReg(image_factory f);
};
inline ImageDecoderReg::ImageDecoderReg(image_factory f) {
	image_factory_reg(f);
}

}
}

#endif /* POLA_IMAGEDECODERFACTORY_H_ */
