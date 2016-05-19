/*
 * Color.h
 *
 *  Created on: 2016年1月10日
 *      Author: lijing
 */

#ifndef POLA_COLOR_H_
#define POLA_COLOR_H_

namespace pola {
namespace graphic {

typedef uint32_t RGBA32; // RGBA quadruplet

struct Color {
	RGBA32 color;
};

struct FColor {
	float r, g, b, a;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_COLOR_H_ */
