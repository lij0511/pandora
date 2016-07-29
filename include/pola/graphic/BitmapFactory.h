/*
 * BitmapFactory.h
 *
 *  Created on: 2015年12月3日
 *      Author: lijing
 */

#ifndef POLA_BITMAPFACTORY_H_
#define POLA_BITMAPFACTORY_H_

#include "pola/graphic/Bitmap.h"
#include "pola/io/InputStream.h"

namespace pola {
namespace graphic {

class BitmapFactory {
public:
	static Bitmap* decodeFile(const char *file, Bitmap::Format format = Bitmap::Format::UNKONWN);
	static Bitmap* decodeStream(io::InputStream* is, Bitmap::Format format = Bitmap::Format::UNKONWN);
};

}
}

#endif /* POLA_BITMAPFACTORY_H_ */
