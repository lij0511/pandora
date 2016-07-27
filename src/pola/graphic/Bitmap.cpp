/*
 * Bitmap.cpp
 *
 *  Created on: 2015年12月3日
 *      Author: lijing
 */

#include <string.h>

#include "pola/graphic/Bitmap.h"
#include "utils/BitmapUtils.h"

namespace pola {
namespace graphic {

static uint32_t rowBytesAlign(uint32_t w, uint32_t bytesPerPixel) {
	uint32_t widthInBytes = w * bytesPerPixel;
	return widthInBytes + ((4 - (widthInBytes % 4))) % 4;
}

Bitmap::Bitmap(uint32_t w, uint32_t h, Format format) :
	mWidth(w),
	mHeight(h),
	mFormat(format),
	mGenerationID(0),
	mRecycled(false),
	mHasAlpha(true)
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
	mHasAlpha(true),
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
}

uint32_t Bitmap::getGenerationID() const {
		return mGenerationID;
}

unsigned char* Bitmap::pixels() const {
	return mData;
}

bool Bitmap::scale(Bitmap*& dst, float scaleW, float scaleH) {
	return scaleBitmap(*this, dst, scaleW, scaleH);
}

}
}
