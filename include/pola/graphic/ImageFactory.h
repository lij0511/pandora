/*
 * ImageFactory.h
 *
 *  Created on: 2015年12月3日
 *      Author: lijing
 */

#ifndef POLA_IMAGEFACTORY_H_
#define POLA_IMAGEFACTORY_H_

#include "pola/graphic/Image.h"
#include "pola/io/InputStream.h"

namespace pola {
namespace graphic {

class ImageFactory {
public:
	static Image* decodeFile(const char *file, PixelFormat format = PixelFormat::UNKONWN);
	static Image* decodeStream(io::InputStream* is, PixelFormat format = PixelFormat::UNKONWN);
};

}
}

#endif /* POLA_IMAGEFACTORY_H_ */
