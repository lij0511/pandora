/*
 * ColorPriv.h
 *
 *  Created on: 2016年7月18日
 *      Author: lijing
 */

#ifndef POLA_COLORPRIV_H_
#define POLA_COLORPRIV_H_

namespace pola {
namespace graphic {

static inline uint32_t AlphaMulQ(uint32_t c, unsigned scale) {
	uint32_t mask = 0xFF00FF;

	uint32_t rb = ((c & mask) * scale) >> 8;
	uint32_t ag = ((c >> 8) & mask) * scale;
	return (rb & mask) | (ag & ~mask);
}

static inline unsigned MulDiv255Round(unsigned a, unsigned b) {
    unsigned prod = a * b + 128;
    return (prod + (prod >> 8)) >> 8;
}

static inline uint32_t PackRGBA8888(unsigned r, unsigned g, unsigned b, unsigned a) {
	return ((r & 0xFF) << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | ((a & 0xFF));
}

}
}

#endif /* COLORPRIV_H_ */
