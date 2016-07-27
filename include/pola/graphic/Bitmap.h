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
		UNKONWN,
		ALPHA8,
		RGBA8888,
		RGB888,
		RGB565
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

	static Bitmap* create(uint32_t w, uint32_t h, Format format);
	static Bitmap* create();

	void set(uint32_t w, uint32_t h, Format format, uint8_t* pixels = nullptr);

	uint32_t getGenerationID() const;

	uint8_t* pixels() const;

	bool scale(Bitmap*& dst, float scaleW, float scaleH);

protected:
	Bitmap(uint32_t w, uint32_t h, Format format);
	Bitmap();
private:

	uint32_t mWidth;
	uint32_t mHeight;
	Format mFormat;
	uint32_t mGenerationID;
	bool mRecycled;
	bool mHasAlpha;
	uint8_t* mData;
	uint32_t mRowBytes;

};
}
}

#endif /* POLA_BITMAP_H_ */
