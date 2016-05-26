/*
 * BMPImageDecoder.cpp
 *
 *  Created on: 2016年5月26日
 *      Author: lijing
 */

#include <string.h>

#include "io/IOUtils.h"

#include "graphic/image/BMPImageDecoder.h"
#include "graphic/image/ImageDecoderFactory.h"

namespace pola {
namespace graphic {

class BmpDecoder {
public:
	BmpDecoder(const uint8_t* data, size_t length);

	void decode();

private:
	uint32_t GetInt();
	uint16_t GetShort();
	uint8_t GetByte();

	const uint8_t* data_;
	size_t pos_;
	size_t len_;
};

BmpDecoder::BmpDecoder(const uint8_t* data, size_t length) : data_(data), pos_(0), len_(length) {
}

uint32_t BmpDecoder::GetInt() {
	uint8_t b1 = GetByte();
	uint8_t b2 = GetByte();
	uint8_t b3 = GetByte();
	uint8_t b4 = GetByte();
  return b1 | (b2 << 8) | (b3 << 16) | (b4 << 24);
}

uint16_t BmpDecoder::GetShort() {
	uint8_t b1 = GetByte();
	uint8_t b2 = GetByte();
  return b1 | (b2 << 8);
}

uint8_t BmpDecoder::GetByte() {
  // We deliberately allow this off-by-one access to cater for BMPs with their
  // last byte missing.
  if (pos_ == len_) {
    return 0;
  }
  return data_[pos_++];
}

BMPImageDecoder::BMPImageDecoder() {
}

BMPImageDecoder::~BMPImageDecoder() {
}

Bitmap* BMPImageDecoder::decode(io::InputStream* is) {
	utils::Vector<uint8_t> vector = io::copyStreamToVector<uint8_t>(is);
	if (vector.size() > 0) {
		BmpDecoder decoder(vector.array(), vector.size());
	}
	return nullptr;
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
