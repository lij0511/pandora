/*
 * Blend.h
 *
 *  Created on: 2016年7月18日
 *      Author: lijing
 */

#ifndef POLA_BLEND_H_
#define POLA_BLEND_H_

#include <stdint.h>

namespace pola {
namespace graphic {

enum BlendMode {
	Clear = 0,
	Src,
	Dst,
	SrcOver,
	DstOver,
	SrcIn,
	DstIn,
	SrcOut,
	DstOut,
	SrcATop,
	DstATop,
	Xor,
	Plus,
	Modulate,
};

uint32_t blend(uint32_t src, uint32_t dst, BlendMode mode = SrcOver);

} /* namespace graphic */
} /* namespace pola */

#endif /* BLEND_H_ */
