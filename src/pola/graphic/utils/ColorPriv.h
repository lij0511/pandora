/*
 * ColorPriv.h
 *
 *  Created on: 2016年7月18日
 *      Author: lijing
 */

#ifndef POLA_COLORPRIV_H_
#define POLA_COLORPRIV_H_

#if !defined(POLA_CPU_BENDIAN) && !defined(POLA_CPU_LENDIAN)
    #if defined(__sparc) || defined(__sparc__) || \
      defined(_POWER) || defined(__powerpc__) || \
      defined(__ppc__) || defined(__hppa) || \
      defined(__PPC__) || defined(__PPC64__) || \
      defined(_MIPSEB) || defined(__ARMEB__) || \
      defined(__s390__) || \
      (defined(__sh__) && defined(__BIG_ENDIAN__)) || \
      (defined(__ia64) && defined(__BIG_ENDIAN__))
         #define POLA_CPU_BENDIAN
    #else
        #define POLA_CPU_LENDIAN
    #endif
#endif

#ifdef POLA_CPU_BENDIAN
    #define POLA_RGBA_R32_SHIFT   24
    #define POLA_RGBA_G32_SHIFT   16
    #define POLA_RGBA_B32_SHIFT   8
    #define POLA_RGBA_A32_SHIFT   0
#else
    #define POLA_RGBA_R32_SHIFT   0
    #define POLA_RGBA_G32_SHIFT   8
    #define POLA_RGBA_B32_SHIFT   16
    #define POLA_RGBA_A32_SHIFT   24
#endif

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

static inline uint32_t PackRGBA8888(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	return (a << POLA_RGBA_A32_SHIFT) | (r << POLA_RGBA_R32_SHIFT) |
	           (g << POLA_RGBA_G32_SHIFT) | (b << POLA_RGBA_B32_SHIFT);
}

#define GetPackedR(packed)      ((uint32_t)((packed) << (24 - POLA_RGBA_R32_SHIFT)) >> 24)
#define GetPackedG(packed)      ((uint32_t)((packed) << (24 - POLA_RGBA_G32_SHIFT)) >> 24)
#define GetPackedB(packed)      ((uint32_t)((packed) << (24 - POLA_RGBA_B32_SHIFT)) >> 24)
#define GetPackedA(packed)      ((uint32_t)((packed) << (24 - POLA_RGBA_A32_SHIFT)) >> 24)

}
}

#endif /* POLA_COLORPRIV_H_ */
