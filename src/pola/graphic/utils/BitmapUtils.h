/*
 * BitmapUtils.h
 *
 *  Created on: 2016年7月27日
 *      Author: lijing
 */

#ifndef POLA_BITMAPUTILS_H_
#define POLA_BITMAPUTILS_H_

#include "pola/graphic/Bitmap.h"
#include "pola/graphic/Color.h"

namespace pola {
namespace graphic {

bool clearBitmap(Bitmap& bitmap, RGBA32 color);

enum BitmapScaleMode {
	LINEAR,
	BILINEAR,
};

bool scaleBitmap(const Bitmap& src, Bitmap*& dst, float scaleW, float scaleH, BitmapScaleMode scaleMode = LINEAR);

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_BITMAPUTILS_H_ */
