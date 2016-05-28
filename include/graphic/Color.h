/*
 * Color.h
 *
 *  Created on: 2016年1月10日
 *      Author: lijing
 */

#ifndef POLA_COLOR_H_
#define POLA_COLOR_H_

#include <stdint.h>

namespace pola {
namespace graphic {

typedef uint32_t RGBA32; // RGBA quadruplet

struct Color {
	RGBA32 color;

	void getRGBA(float& red, float& green, float&blue, float& alpha) {
		// RGBA
		const float a = ((color) & 0xff) / 255.0f;
		red = a * ((color >> 24) & 0xff) / 255.0f;
		green = a * ((color >> 16) & 0xff) / 255.0f;
		blue = a * ((color >> 8) & 0xff) / 255.0f;
		alpha = a;
	}
};

struct FColor {
	float r, g, b, a;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_COLOR_H_ */
