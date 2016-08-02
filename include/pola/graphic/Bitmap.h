/*
 * Bitmap.h
 *
 *  Created on: 2015年12月3日
 *      Author: lijing
 */

#ifndef POLA_BITMAP_H_
#define POLA_BITMAP_H_

#include <stdint.h>

namespace pola {
namespace graphic {

class Bitmap {
public:

	enum Format {
		ALPHA8,
		RGBA8888,
		RGB888,
		RGB565,
		UNKONWN,
	};

	static uint32_t getByteCountPerPixel(Bitmap::Format format);

	virtual ~Bitmap();

	uint32_t getWidth() const;
	uint32_t getHeight() const;
	Format getFormat() const;
	uint32_t bytesPerPixel() const;
	uint32_t rowBytes() const;
	uint32_t getByteCount() const;

	void recycle();

	bool isRecycled() const;
	bool hasAlpha() const;

	void setHasAlpha(bool hasAlpha);

	uint8_t* pixels() const;

	bool isEmpty() const;

	static Bitmap* create(uint32_t w, uint32_t h, Format format);
	static Bitmap* create();
	Bitmap();

	void set(uint32_t w, uint32_t h, Format format, uint8_t* pixels = nullptr);

	uint32_t getGenerationID() const;
	void notifyPixelsChanged() const;


	uint32_t getPixel(uint32_t x, uint32_t y) const;
	void putPixel(uint32_t x, uint32_t y, uint32_t color);

	bool scale(Bitmap*& dst, float scaleW, float scaleH);

protected:
	Bitmap(uint32_t w, uint32_t h, Format format);
private:
	Bitmap& operator=(const Bitmap& other);
	Bitmap(const Bitmap& other);

	uint32_t mWidth;
	uint32_t mHeight;
	Format mFormat;
	mutable uint32_t mGenerationID;
	bool mRecycled;
	bool mHasAlpha;
	uint8_t* mData;
	uint32_t mRowBytes;

};
}
}

#endif /* POLA_BITMAP_H_ */
