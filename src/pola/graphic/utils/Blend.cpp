/*
 * Blend.cpp
 *
 *  Created on: 2016年7月18日
 *      Author: lijing
 */

#include "pola/graphic/Blend.h"
#include "pola/graphic/utils/ColorPriv.h"
#include <stdio.h>

namespace pola {
namespace graphic {

static inline unsigned saturated_add(unsigned a, unsigned b) {
    unsigned sum = a + b;
    if (sum > 255) {
        sum = 255;
    }
    return sum;
}

typedef uint32_t (*BlendFunc)(uint32_t src, uint32_t dst);

uint32_t ClearFunc(uint32_t src, uint32_t dst) {
	return 0;
}

uint32_t SrcFunc(uint32_t src, uint32_t dst) {
	return src;
}

uint32_t DstFunc(uint32_t src, uint32_t dst) {
	return dst;
}

uint32_t SrcOverFunc(uint32_t src, uint32_t dst) {
	// Cr = Cs + Cd * (1 – As)
	return src + AlphaMulQ(dst, 256 - (src & 0xFF));
}

uint32_t DstOverFunc(uint32_t src, uint32_t dst) {
	return dst + AlphaMulQ(src, 256 - (dst & 0xFF));
}

uint32_t SrcInFunc(uint32_t src, uint32_t dst) {
	return AlphaMulQ(src, (dst & 0xFF) + 1);
}

uint32_t DstInFunc(uint32_t src, uint32_t dst) {
	return AlphaMulQ(dst, (src & 0xFF) + 1);
}

uint32_t SrcOutFunc(uint32_t src, uint32_t dst) {
	return AlphaMulQ(src, (255 - (dst & 0xFF)) + 1);
}

uint32_t DstOutFunc(uint32_t src, uint32_t dst) {
	return AlphaMulQ(dst, (255 - (src & 0xFF)) + 1);
}

uint32_t SrcATopFunc(uint32_t src, uint32_t dst) {
	unsigned sa = src & 0xFF;
	unsigned da = dst & 0xFF;
	unsigned isa = 255 - sa;

	return PackRGBA8888(
						MulDiv255Round(da, ((src >> 24) & 0xFF)) +
							MulDiv255Round(isa, ((dst >> 24) & 0xFF)),
						MulDiv255Round(da, ((src >> 16) & 0xFF)) +
							MulDiv255Round(isa, ((dst >> 16) & 0xFF)),
						MulDiv255Round(da, ((src >> 8) & 0xFF)) +
							MulDiv255Round(isa, ((dst >> 8) & 0xFF)),
						da);
}

uint32_t DstATopFunc(uint32_t src, uint32_t dst) {
	unsigned sa = src & 0xFF;
	unsigned da = dst & 0xFF;
	unsigned ida = 255 - da;

	return PackRGBA8888(
						MulDiv255Round(ida, ((src >> 24) & 0xFF)) +
							MulDiv255Round(sa, ((dst >> 24) & 0xFF)),
						MulDiv255Round(ida, ((src >> 16) & 0xFF)) +
							MulDiv255Round(sa, ((dst >> 16) & 0xFF)),
						MulDiv255Round(ida, ((src >> 8) & 0xFF)) +
							MulDiv255Round(sa, ((dst >> 8) & 0xFF)),
						sa);
}

uint32_t XorFunc(uint32_t src, uint32_t dst) {
	unsigned sa = src & 0xFF;
	unsigned da = dst & 0xFF;
	unsigned isa = 255 - sa;
	unsigned ida = 255 - da;

	return PackRGBA8888(
						MulDiv255Round(ida, ((src >> 24) & 0xFF)) +
							MulDiv255Round(isa, ((dst >> 24) & 0xFF)),
						MulDiv255Round(ida, ((src >> 16) & 0xFF)) +
							MulDiv255Round(isa, ((dst >> 16) & 0xFF)),
						MulDiv255Round(ida, ((src >> 8) & 0xFF)) +
							MulDiv255Round(isa, ((dst >> 8) & 0xFF)),
						sa + da - (MulDiv255Round(sa, da) << 1));
}

uint32_t PlusFunc(uint32_t src, uint32_t dst) {
	unsigned r = saturated_add((src >> 24) & 0xFF, (dst >> 24) & 0xFF);
	unsigned g = saturated_add((src >> 16) & 0xFF, (dst >> 16) & 0xFF);
	unsigned b = saturated_add((src >> 8) & 0xFF, (dst >> 8) & 0xFF);
	unsigned a = saturated_add((src) & 0xFF, (dst) & 0xFF);
	return PackRGBA8888(r, g, b, a);
}

uint32_t ModulateFunc(uint32_t src, uint32_t dst) {
	unsigned r = MulDiv255Round((src >> 24) & 0xFF, (dst >> 24) & 0xFF);
	unsigned g = MulDiv255Round((src >> 16) & 0xFF, (dst >> 16) & 0xFF);
	unsigned b = MulDiv255Round((src >> 8) & 0xFF, (dst >> 8) & 0xFF);
	unsigned a = MulDiv255Round((src) & 0xFF, (dst) & 0xFF);
    return PackRGBA8888(a, r, g, b);
}

uint32_t blend(uint32_t src, uint32_t dst, BlendMode mode) {
	static BlendFunc gBlendFuncs[] = {
			ClearFunc,
			SrcFunc,
			DstFunc,
			SrcOverFunc,
			DstOverFunc,
			SrcInFunc,
			DstInFunc,
			SrcOutFunc,
			DstOutFunc,
			SrcATopFunc,
			DstATopFunc,
			XorFunc,
			PlusFunc,
			ModulateFunc,
	};
	BlendFunc func = gBlendFuncs[mode];
	return func(src, dst);
}

} /* namespace graphic */
} /* namespace pola */
