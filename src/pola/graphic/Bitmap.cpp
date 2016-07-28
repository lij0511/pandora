/*
 * Bitmap.cpp
 *
 *  Created on: 2015年12月3日
 *      Author: lijing
 */

#include <string.h>

#include "pola/graphic/Bitmap.h"
#include "pola/graphic/utils/BitmapUtils.h"

namespace pola {
namespace graphic {

static uint32_t rowBytesAlign(uint32_t w, uint32_t bytesPerPixel) {
	uint32_t align = 2;//bytesPerPixel % 2 == 0 ? bytesPerPixel : bytesPerPixel + 1;
	uint32_t widthInBytes = w * bytesPerPixel;
	return widthInBytes + ((align - (widthInBytes % align))) % align;
}

Bitmap::Bitmap(uint32_t w, uint32_t h, Format format) :
	mWidth(w),
	mHeight(h),
	mFormat(format),
	mGenerationID(0),
	mRecycled(false),
	mHasAlpha(false)
{
	mRowBytes = rowBytesAlign(mWidth, bytesPerPixel());
	mData = new unsigned char[rowBytes() * mHeight];
}
Bitmap::Bitmap() :
	mWidth(0),
	mHeight(0),
	mFormat(UNKONWN),
	mGenerationID(0),
	mRecycled(true),
	mHasAlpha(false),
	mData(nullptr),
	mRowBytes(0)
{
}

Bitmap::~Bitmap() {
	if (mData) {
		delete mData;
		mData = nullptr;
	}
}

uint32_t Bitmap::getByteCountPerPixel(Bitmap::Format format) {
	int c;
	switch (format) {
	case Bitmap::ALPHA8:
		c = 1;
		break;
	case Bitmap::RGBA8888:
		c = 4;
		break;
	case Bitmap::RGB888:
		c = 3;
		break;
	case Bitmap::RGB565:
		c = 2;
		break;
	default:
		c = 0;
		break;
	}
	return c;
}

uint32_t Bitmap::getWidth() const {
	return mWidth;
};
uint32_t Bitmap::getHeight() const {
	return mHeight;
};
Bitmap::Format Bitmap::getFormat() const {
	return mFormat;
};
uint32_t Bitmap::bytesPerPixel() const {
	return getByteCountPerPixel(mFormat);
}
uint32_t Bitmap::rowBytes() const {
	return mRowBytes;
}
uint32_t Bitmap::getByteCount() const {
	return rowBytes() * getHeight();
}

void Bitmap::recycle() {
	if (!mRecycled) {
		mRecycled = true;
		if (mData) {
			delete mData;
			mData = nullptr;
		}
	}
}

bool Bitmap::isRecycled() const {
	return mRecycled;
}

bool Bitmap::hasAlpha() const {
	return mHasAlpha;
}

void Bitmap::setHasAlpha(bool hasAlpha) {
	mHasAlpha = hasAlpha;
}

Bitmap* Bitmap::create(uint32_t w, uint32_t h, Format format) {
	return new Bitmap(w, h, format);
}

Bitmap* Bitmap::create() {
	return new Bitmap();
}

void Bitmap::set(uint32_t w, uint32_t h, Format format, uint8_t* pixels) {
	mWidth = w;
	mHeight = h;
	mFormat = format;
	mRecycled = false;
	if (mData) {
		delete mData;
	}
	mRowBytes = rowBytesAlign(mWidth, bytesPerPixel());
	mData = new unsigned char[rowBytes() * mHeight];
	if (pixels != nullptr) {
		memcpy(mData, pixels, getByteCount());
	}
	notifyPixelsChanged();
}

uint32_t Bitmap::getGenerationID() const {
		return mGenerationID;
}

void Bitmap::notifyPixelsChanged() {
	++ mGenerationID;
}

unsigned char* Bitmap::pixels() const {
	return mData;
}

uint32_t Bitmap::getPixel(uint32_t x, uint32_t y) const {
	if (x >= mWidth || y >= mHeight) {
		return 0;
	}
	uint8_t* row = mData + rowBytes() * y;
	uint32_t p = x * bytesPerPixel();
	switch (mFormat) {
		case ALPHA8:
			return row[p];
		case RGBA8888:
			return ((row[p] << 24) & 0xff000000) | ((row[p + 1] << 16) & 0xff0000)  | ((row[p + 2] << 8) & 0xff00)  | (row[p + 3]);
		case RGB888:
			return ((row[p] << 16) & 0xff0000) | ((row[p + 1] << 8) & 0xff00)  | (row[p + 2]);
		case RGB565:
			return ((uint16_t*) (row))[x];
		default:
			return 0;
	}
}

void Bitmap::putPixel(uint32_t x, uint32_t y, uint32_t color) {
	if (x >= mWidth || y >= mHeight) {
		return;
	}
	uint8_t* row = mData + rowBytes() * y;
	uint32_t p = x * bytesPerPixel();
	switch (mFormat) {
		case ALPHA8:
			row[p] = color & 0xff;
			break;
		case RGBA8888:
			row[p] = (color >> 24) & 0xff;
			row[p + 1] = (color >> 16) & 0xff;
			row[p + 2] = (color >> 8) & 0xff;
			row[p + 3] = color & 0xff;
			break;
		case RGB888:
			row[p] = (color >> 16) & 0xff;
			row[p + 1] = (color >> 8) & 0xff;
			row[p + 2] = color & 0xff;
			break;
		case RGB565:
			((uint16_t*) row)[x] = color;
			break;
		default:
			break;
	}
	notifyPixelsChanged();
}

bool Bitmap::scale(Bitmap*& dst, float scaleW, float scaleH) {
	return scaleBitmap(*this, dst, scaleW, scaleH);
}

}
}
