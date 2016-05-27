/*
 * BMPImageDecoder.cpp
 *
 *  Created on: 2016年5月26日
 *      Author: lijing
 */

#include <string.h>

#include "log/Log.h"
#include "io/IOUtils.h"

#include "graphic/image/BMPImageDecoder.h"
#include "graphic/image/ImageDecoderFactory.h"

namespace pola {
namespace graphic {

#include "utils/spack.h"
struct BMPHeader {
	uint16_t	Id;					//	BM - Windows 3.1x, 95, NT, 98, 2000, ME, XP
										//	BA - OS/2 Bitmap Array
										//	CI - OS/2 Color Icon
										//	CP - OS/2 Color Pointer
										//	IC - OS/2 Icon
										//	PT - OS/2 Pointer
	uint32_t	FileSize;
	uint32_t	Reserved;
	uint32_t	BitmapDataOffset;
	uint32_t	BitmapHeaderSize;	// should be 28h for windows bitmaps or
										// 0Ch for OS/2 1.x or F0h for OS/2 2.x
	uint32_t Width;
	uint32_t Height;
	uint16_t Planes;
	uint16_t BPP;					// 1: Monochrome bitmap
										// 4: 16 color bitmap
										// 8: 256 color bitmap
										// 16: 16bit (high color) bitmap
										// 24: 24bit (true color) bitmap
										// 32: 32bit (true color) bitmap

	uint32_t  Compression;			// 0: none (Also identified by BI_RGB)
										// 1: RLE 8-bit / pixel (Also identified by BI_RLE4)
										// 2: RLE 4-bit / pixel (Also identified by BI_RLE8)
										// 3: Bitfields  (Also identified by BI_BITFIELDS)

	uint32_t  BitmapDataSize;		// Size of the bitmap data in bytes. This number must be rounded to the next 4 byte boundary.
	uint32_t  PixelPerMeterX;
	uint32_t  PixelPerMeterY;
	uint32_t  Colors;
	uint32_t  ImportantColors;
} PACK_STRUCT;

#include "utils/sunpack.h"

static uint8_t readByte(io::InputStream* is) {
	int b = is->read();
	if (b == EOF) {
		return 0;
	}
	return b & 0xFF;
}

static int16_t readShort(io::InputStream* is) {
	uint8_t b1 = readByte(is);
	uint8_t b2 = readByte(is);
	return b1 | (b2 << 8);
}

static int16_t readInt(io::InputStream* is) {
	uint8_t b1 = readByte(is);
	uint8_t b2 = readByte(is);
	uint8_t b3 = readByte(is);
	uint8_t b4 = readByte(is);
	return b1 | (b2 << 8) | (b3 << 16) | (b4 << 24);
}

static void putPixel565(Bitmap* bitmap, uint32_t x, uint32_t y, uint8_t* color_table, uint8_t color) {
	uint32_t base = bitmap->rowBytes() * y + x * bitmap->bytesPerPixel();//((y * width_) + x) * 3;
	uint16_t* pixels = (uint16_t*) (bitmap->pixels() + base);
	uint32_t colBase = color * 3;
	uint8_t* c = color_table + colBase;

	*pixels = (uint16_t) (((unsigned(c[0]) << 8) & 0xF800) |
			((unsigned(c[1]) << 3) & 0x7E0)  |
			((unsigned(c[2]) >> 3)));
}

static void putPixel888(Bitmap* bitmap, uint32_t x, uint32_t y, uint8_t* color_table, uint8_t color) {
	uint32_t base = bitmap->rowBytes() * y + x * bitmap->bytesPerPixel();//((y * width_) + x) * 3;
	uint8_t* pixels = bitmap->pixels() + base;
	uint32_t colBase = color * 3;
	pixels[base] = color_table[colBase];
	pixels[base + 1] = color_table[colBase + 1];
	pixels[base + 2] = color_table[colBase + 2];
}

static void putPixel565_1(Bitmap* bitmap, uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b) {
	uint32_t base = bitmap->rowBytes() * y + x * bitmap->bytesPerPixel();//((y * width_) + x) * 3;
	uint16_t* pixels = (uint16_t*) (bitmap->pixels() + base);
	*pixels = (uint16_t) (((r << 8) & 0xF800) |
			((g << 3) & 0x7E0)  |
			((b >> 3)));
}

static void putPixel888_1(Bitmap* bitmap, uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b) {
	uint32_t base = bitmap->rowBytes() * y + x * bitmap->bytesPerPixel();//((y * width_) + x) * 3;
	uint8_t* pixels = bitmap->pixels() + base;
	pixels[base] = r;
	pixels[base + 1] = g;
	pixels[base + 2] = b;
}

static void doRLEDecode(BMPHeader& header, io::InputStream* is, Bitmap* bitmap,
		uint8_t* color_table) {
	static const uint8_t RLE_ESCAPE = 0;
	static const uint8_t RLE_EOL = 0;
	static const uint8_t RLE_EOF = 1;
	static const uint8_t RLE_DELTA = 2;

	void (*putPixel)(Bitmap*, uint32_t, uint32_t, uint8_t*, uint8_t);
	putPixel =
			bitmap->getFormat() == Bitmap::RGB565 ? &putPixel565 : &putPixel888;

	uint32_t width_ = bitmap->getWidth();
	uint32_t height_ = bitmap->getHeight();

	uint32_t x = 0;
	uint32_t y = height_ - 1;
	while (1) {
		uint8_t cmd = readByte(is);
		if (cmd != RLE_ESCAPE) {
			uint8_t pixels = readByte(is);
			int num = 0;
			uint8_t col = pixels;
			while (cmd-- && x < width_) {
				if (header.BPP == 4) {
					if (num & 1) {
						col = pixels & 0xf;
					} else {
						col = pixels >> 4;
					}
				}
				putPixel(bitmap, x++, y, color_table, col);
				num++;
			}
		} else {
			cmd = readByte(is);
			if (cmd == RLE_EOF) {
				return;
			} else if (cmd == RLE_EOL) {
				x = 0;
				y--;
				if (y < 0) {
					return;
				}
			} else if (cmd == RLE_DELTA) {
				uint8_t dx = readByte(is);
				uint8_t dy = readByte(is);
				x += dx;
				if (x > width_) {
					x = width_;
				}
				y -= dy;
				if (y < 0) {
					return;
				}
			} else {
				int num = 0;
				int bytesRead = 0;
				uint8_t val = 0;
				while (cmd--) {
					if (header.BPP == 8 || !(num & 1)) {
						val = readByte(is);
						bytesRead++;
					}
					uint8_t col = val;
					if (header.BPP == 4) {
						if (num & 1) {
							col = col & 0xf;
						} else {
							col >>= 4;
						}
					}
					if (x < width_) {
						putPixel(bitmap, x++, y, color_table, col);
					}
					num++;
				}
				// All pixel runs must be an even number of bytes - skip a byte if we
				// read an odd number.
				if ((bytesRead & 1)) {
					readByte(is);
				}
			}
		}
	}
}

static void doStandardDecode(BMPHeader& header, io::InputStream* is,
		Bitmap* bitmap, uint8_t* color_table) {

	uint32_t width_ = bitmap->getWidth();
	uint32_t height_ = bitmap->getHeight();

	uint32_t pixelPad_ = 0;
	uint32_t rowPad_ = 0;
	uint32_t rowLen;
	if (header.BPP == 32) {
		rowLen = width_ * 4;
		pixelPad_ = 1;
	} else if (header.BPP == 24) {
		rowLen = width_ * 3;
	} else if (header.BPP == 16) {
		rowLen = width_ * 2;
	} else if (header.BPP == 8) {
		rowLen = width_;
	} else if (header.BPP == 4) {
		rowLen = width_ / 2;
		if (width_ & 1) {
			rowLen++;
		}
	} else if (header.BPP == 1) {
		rowLen = width_ / 8;
		if (width_ & 7) {
			rowLen++;
		}
	} else {
		return;
	}
	// Round the rowLen up to a multiple of 4.
	if (rowLen % 4 != 0) {
		rowPad_ = 4 - (rowLen % 4);
		rowLen += rowPad_;
	}

	void (*putPixel)(Bitmap*, uint32_t, uint32_t, uint8_t*, uint8_t);
	putPixel =
			bitmap->getFormat() == Bitmap::RGB565 ? &putPixel565 : &putPixel888;
	void (*putPixel1)(Bitmap* bitmap, uint32_t x, uint32_t y, uint8_t r,
			uint8_t g, uint8_t b);
	putPixel1 =
			bitmap->getFormat() == Bitmap::RGB565 ?
					&putPixel565_1 : &putPixel888_1;

	uint32_t row = 0;
	uint8_t currVal = 0;
	for (int32_t h = height_ - 1; h >= 0; h--, row++) {
		for (int32_t w = 0; w < width_; w++) {
			if (header.BPP >= 24) {
				putPixel1(bitmap, w, h, readByte(is), readByte(is),
						readByte(is));
			} else if (header.BPP == 16) {/*
			 uint32_t val = readShort(is);
			 line[0] = ((val & redBits_) >> redShiftRight_) << redShiftLeft_;
			 line[1] = ((val & greenBits_) >> greenShiftRight_) << greenShiftLeft_;
			 line[2] = ((val & blueBits_) >> blueShiftRight_) << blueShiftLeft_;
			 */
			} else if (header.BPP <= 8) {
				uint8_t col;
				if (header.BPP == 8) {
					col = readByte(is);
				} else if (header.BPP == 4) {
					if ((w % 2) == 0) {
						currVal = readByte(is);
						col = currVal >> 4;
					} else {
						col = currVal & 0xf;
					}
				} else {
					if ((w % 8) == 0) {
						currVal = readByte(is);
					}
					int bit = w & 7;
					col = ((currVal >> (7 - bit)) & 1);
				}

				putPixel(bitmap, w, h, color_table, col);
			}
			for (int i = 0; i < pixelPad_; ++i) {
				readByte(is);
			}
		}
		for (int i = 0; i < rowPad_; ++i) {
			readByte(is);
		}
	}
}

BMPImageDecoder::BMPImageDecoder() {
}

BMPImageDecoder::~BMPImageDecoder() {
}

Bitmap* BMPImageDecoder::decode(io::InputStream* is) {
	BMPHeader header;
	is->read(&header, sizeof(BMPHeader));
	LOGI("id=%x, FileSize=%u, Reserved=%u, BitmapDataOffset=%u, BitmapHeaderSize=%u, Width=%u, Height=%u, Planes=%u, BPP=%u, Compression=%u, BitmapDataSize=%u, PixelPerMeterX=%u, PixelPerMeterY=%u, Colors=%u, ImportantColors=%u\n",
			header.Id, header.FileSize, header.Reserved, header.BitmapDataOffset, header.BitmapHeaderSize, header.Width, header.Height, header.Planes, header.BPP, header.Compression, header.BitmapDataSize, header.PixelPerMeterX, header.PixelPerMeterY, header.Colors, header.ImportantColors);

	if (!header.Width || !header.Height) {
		LOGE("Invalid Width or Height, Width=%u, Height=%u\n", header.Width, header.Height);
		return nullptr;
	}
	if (header.Compression > 2) // we'll only handle RLE-Compression
	{
		LOGE("Compression mode not supported, Compression=%u. We only handle RLE-Compression.\n", header.Compression);
		return 0;
	}
	if (header.Colors < 0 || header.Colors > 256) {
		return nullptr;
	}

	// Allocate then read in the colour map.
	if (header.Colors == 0 && header.BPP <= 8) {
		header.Colors = 1 << header.BPP;
	}
	static uint8_t color_table[256 * 3] = {'\0'};
	memset(color_table, '\0', 256 * 3);

	if (header.Colors > 0) {
		for (unsigned i = 0; i < header.Colors; ++i) {
			int base = i * 3;
			color_table[base + 2] = readByte(is);
			color_table[base + 1] = readByte(is);
			color_table[base] = readByte(is);
			readByte(is);
		}
	}

	is->seek(header.BitmapDataOffset);

	Bitmap::Format format = Bitmap::RGB565;
	switch (header.BPP) {
		case 32:
		case 24:
			format = Bitmap::RGB888;
			break;
		default:
			break;
	}

	Bitmap* bitmap = Bitmap::create();
	bitmap->set(header.Width, header.Height, format);
	uint8_t* pixels = bitmap->pixels();

	bool rle = false;
	if (header.Compression == 1 || header.Compression == 2) {
		rle = true;
	}

	if (rle && (header.BPP == 4 || header.BPP == 8)) {
		doRLEDecode(header, is, bitmap, color_table);
	} else {
		doStandardDecode(header, is, bitmap, color_table);
	}
	return bitmap;
}

static bool is_bmp(io::InputStream* is) {
	static const char kBmpMagic[] = { 'B', 'M' };
	char buffer[sizeof(kBmpMagic)];
	return is->read(buffer, sizeof(kBmpMagic)) == sizeof(kBmpMagic) &&
		!memcmp(buffer, kBmpMagic, sizeof(kBmpMagic));
}

static ImageDecoder* bmp_image_factory(io::InputStream* is) {
	if (is_bmp(is)) {
		return new BMPImageDecoder;
	}
	return nullptr;
}

ImageDecoderReg bmp_reg(bmp_image_factory);

} /* namespace graphic */
} /* namespace pola */
