/*
 * Image.h
 *
 *  Created on: 2015年12月3日
 *      Author: lijing
 */

#ifndef POLA_IMAGE_H_
#define POLA_IMAGE_H_

#include <stdint.h>
#include "pola/graphic/PixelFormat.h"

namespace pola {
namespace graphic {

class Image {
public:

	static uint32_t getByteCountPerPixel(PixelFormat format);

	virtual ~Image();

	uint32_t getWidth() const;
	uint32_t getHeight() const;
	PixelFormat getFormat() const;
	uint32_t bytesPerPixel() const;
	uint32_t rowBytes() const;
	uint32_t getByteCount() const;

	void recycle();

	bool isRecycled() const;
	bool hasAlpha() const;

	void setHasAlpha(bool hasAlpha);

	uint8_t* pixels() const;

	bool isEmpty() const;

	static Image* create(uint32_t w, uint32_t h, PixelFormat format);
	static Image* create();
	Image();

	void set(uint32_t w, uint32_t h, PixelFormat format, uint8_t* pixels = nullptr);

	uint32_t getGenerationID() const;
	void notifyPixelsChanged() const;


	uint32_t getPixel(uint32_t x, uint32_t y) const;
	void putPixel(uint32_t x, uint32_t y, uint32_t color);

	bool scale(Image*& dst, float scaleW, float scaleH);

protected:
	Image(uint32_t w, uint32_t h, PixelFormat format);
private:
	Image& operator=(const Image& other);
	Image(const Image& other);

	uint32_t mWidth;
	uint32_t mHeight;
	PixelFormat mFormat;
	mutable uint32_t mGenerationID;
	bool mRecycled;
	bool mHasAlpha;
	uint8_t* mData;
	uint32_t mRowBytes;

};
}
}

#endif /* POLA_IMAGE_H_ */
