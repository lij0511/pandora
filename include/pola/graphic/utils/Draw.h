/*
 * Draw.h
 *
 *  Created on: 2016年7月18日
 *      Author: lijing
 */

#ifndef DRAW_H_
#define DRAW_H_

#include "pola/graphic/Bitmap.h"

namespace pola {
namespace graphic {

/*
 *
 */
class Draw {
public:
	Draw(Bitmap* bitmap);
	virtual ~Draw();

	void clear(RGBA32 color);
	void drawBitmap(const Bitmap* b, int32_t x, int32_t y, int32_t dst_x, int32_t dst_y, uint32_t dst_width, uint32_t dst_height);

private:
	Bitmap* mBitmap;
	uint32_t mWidth, mHeight;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* DRAW_H_ */
