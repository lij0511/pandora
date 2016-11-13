/*
 * BlendFunc.h
 *
 *  Created on: 2016年11月11日
 *      Author: lijing
 */

#ifndef POLA_GRAPHIC_BLENDFUNC_H_
#define POLA_GRAPHIC_BLENDFUNC_H_

#if defined(POLA_GLES) || defined(POLA_GL)
#include "pola/graphic/gl/GL.h"
#endif

namespace pola {
namespace graphic {

enum BlendFactor {
#if defined(POLA_GLES) || defined(POLA_GL)
	FACTOR_ZERO															= GL_ZERO,
	FACTOR_ONE																= GL_ONE,
	FACTOR_DST_COLOR												= GL_DST_COLOR,
	FACTOR_ONE_MINUS_DST_COLOR					= GL_ONE_MINUS_DST_COLOR,
	FACTOR_SRC_COLOR												= GL_SRC_COLOR,
	FACTOR_ONE_MINUS_SRC_COLOR					= GL_ONE_MINUS_SRC_COLOR,
	FACTOR_SRC_ALPHA												= GL_SRC_ALPHA,
	FACTOR_ONE_MINUS_SRC_ALPHA						= GL_ONE_MINUS_SRC_ALPHA,
	FACTOR_DST_ALPHA												= GL_DST_ALPHA,
	FACTOR_ONE_MINUS_DST_ALPHA						= GL_ONE_MINUS_DST_ALPHA,
	FACTOR_SRC_ALPHA_SATURATE							= GL_SRC_ALPHA_SATURATE,
#else
	FACTOR_ZERO															= 0,
	FACTOR_ONE																= 1,
	FACTOR_DST_COLOR												= 2,
	FACTOR_ONE_MINUS_DST_COLOR					= 3,
	FACTOR_SRC_COLOR												= 4,
	FACTOR_ONE_MINUS_SRC_COLOR					= 5,
	FACTOR_SRC_ALPHA												= 6,
	FACTOR_ONE_MINUS_SRC_ALPHA						= 7,
	FACTOR_DST_ALPHA												= 8,
	FACTOR_ONE_MINUS_DST_ALPHA						= 9,
	FACTOR_SRC_ALPHA_SATURATE							= 10,
#endif
};

struct BlendFunc {
	BlendFactor mBlendFactorSrc;
	BlendFactor mBlendFactorDst;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_GRAPHIC_BLENDFUNC_H_ */
