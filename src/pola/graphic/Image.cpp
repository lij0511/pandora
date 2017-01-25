/*
 * Image.cpp
 *
 *  Created on: 2015年12月3日
 *      Author: lijing
 */

#include "pola/graphic/Image.h"

#include <string.h>

#include "utils/ColorPriv.h"
#include "utils/ImageUtils.h"

namespace pola {
namespace graphic {

static uint32_t rowBytesAlign(uint32_t w, uint32_t bytesPerPixel) {
	uint32_t align = 4;
	uint32_t widthInBytes = w * bytesPerPixel;
	return widthInBytes + ((align - (widthInBytes % align))) % align;
}

Image::Image(uint32_t w, uint32_t h, PixelFormat format) :
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
Image::Image() :
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
Image::Image(const Image& other) :
	mWidth(0),
	mHeight(0),
	mFormat(UNKONWN),
	mGenerationID(0),
	mRecycled(true),
	mHasAlpha(false),
	mData(nullptr),
	mRowBytes(0) {
}

Image& Image::operator=(const Image& other) {
	return *this;
}

Image::~Image() {
	if (mData) {
		delete mData;
		mData = nullptr;
	}
}

uint32_t Image::getByteCountPerPixel(PixelFormat format) {
	int c;
	switch (format) {
	case PixelFormat::ALPHA8:
		c = 1;
		break;
	case PixelFormat::RGBA8888:
		c = 4;
		break;
	case PixelFormat::RGB888:
		c = 3;
		break;
	case PixelFormat::RGB565:
		c = 2;
		break;
	default:
		c = 0;
		break;
	}
	return c;
}

uint32_t Image::getWidth() const {
	return mWidth;
};
uint32_t Image::getHeight() const {
	return mHeight;
};
PixelFormat Image::getFormat() const {
	return mFormat;
};
uint32_t Image::bytesPerPixel() const {
	return getByteCountPerPixel(mFormat);
}
uint32_t Image::rowBytes() const {
	return mRowBytes;
}
uint32_t Image::getByteCount() const {
	return rowBytes() * getHeight();
}

void Image::recycle() {
	if (!mRecycled) {
		mRecycled = true;
		if (mData) {
			delete mData;
			mData = nullptr;
		}
	}
}

bool Image::isRecycled() const {
	return mRecycled;
}

bool Image::hasAlpha() const {
	return mHasAlpha;
}

void Image::setHasAlpha(bool hasAlpha) {
	mHasAlpha = hasAlpha;
}

unsigned char* Image::pixels() const {
	notifyPixelsChanged();
	return mData;
}

bool Image::isEmpty() const {
	return mWidth <= 0 || mHeight <= 0;
}

Image* Image::create(uint32_t w, uint32_t h, PixelFormat format) {
	return new Image(w, h, format);
}

Image* Image::create() {
	return new Image();
}

void Image::set(uint32_t w, uint32_t h, PixelFormat format, uint8_t* pixels) {
	mWidth = w;
	mHeight = h;
	mFormat = format;
	mRecycled = false;
	uint32_t rowBytes = rowBytesAlign(w, getByteCountPerPixel(format));
	if (getByteCount() != rowBytes * h) {
		if (mData) {
			delete mData;
			mData = nullptr;
		}
		if (rowBytes * h > 0) {
			mData = new unsigned char[rowBytes * h];
		}
	}
	mRowBytes = rowBytes;
	if (pixels != nullptr && getByteCount() > 0) {
		memcpy(mData, pixels, getByteCount());
	}
	notifyPixelsChanged();
}

uint32_t Image::getGenerationID() const {
		return mGenerationID;
}

void Image::notifyPixelsChanged() const {
	++ mGenerationID;
}

uint32_t Image::getPixel(uint32_t x, uint32_t y) const {
	if (x >= mWidth || y >= mHeight) {
		return 0;
	}
	uint8_t* row = mData + rowBytes() * y;
	uint32_t p = x * bytesPerPixel();
	uint32_t color = 0;
	switch (mFormat) {
		case ALPHA8:
			color = ColorSetRGBA(0xff, 0xff, 0xff, row[p]);
			break;
		case RGBA8888:
			color = ColorSetRGBA(row[p], row[p + 1], row[p + 2], row[p + 3]);
			break;
		case RGB888:
			color = ColorSetRGBA(row[p], row[p + 1], row[p + 2], 0xff);
			break;
		case RGB565: {
			uint16_t* r = (uint16_t*) (row);
			r += x;
			color = ((r[0] << 16) & 0xf8000000) | ((r[0] << 13) & 0xfc0000) | ((r[0] << 11) & 0xf800) | 0xff;
			break;
		}
		default:
			break;
	}
	return color;
}

void Image::putPixel(uint32_t x, uint32_t y, uint32_t color) {
	if (x >= mWidth || y >= mHeight) {
		return;
	}
	uint8_t* row = mData + rowBytes() * y;
	uint32_t p = x * bytesPerPixel();
	switch (mFormat) {
		case ALPHA8:
			row[p] = ColorGetA(color);
			break;
		case RGBA8888:
			row[p] = ColorGetR(color);
			row[p + 1] = ColorGetG(color);
			row[p + 2] = ColorGetB(color);
			row[p + 3] = ColorGetA(color);
			break;
		case RGB888:
			row[p] = ColorGetR(color);
			row[p + 1] = ColorGetG(color);
			row[p + 2] = ColorGetB(color);
			break;
		case RGB565:
			((uint16_t*) row)[x] = ((ColorGetR(color) >> 3) << 11) | ((ColorGetG(color) >> 2) << 5) | (ColorGetB(color) >> 3);
			break;
		default:
			break;
	}
	notifyPixelsChanged();
}

bool Image::scale(Image*& dst, float scaleW, float scaleH) {
	return scaleBitmap(*this, dst, scaleW, scaleH);
}

}
}
