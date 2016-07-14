/*
 * Color.h
 *
 *  Created on: 2016年1月10日
 *      Author: lijing
 */

#ifndef POLA_COLOR_H_
#define POLA_COLOR_H_

#include <stdint.h>
#include "utils/TypeHelpers.h"

namespace pola {
namespace graphic {

struct FColor3 {
	float r, g, b;
	FColor3(float r = 0, float g = 0, float b = 0) {
		this->r = r;
		this->g = g;
		this->b = b;
	}
};

struct FColor4 {
	float r, g, b, a;
	FColor4(float r = 0, float g = 0, float b = 0, float a = 0) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
};

typedef uint32_t RGBA32; // RGBA quadruplet

struct Color {
	RGBA32 color;

	Color(RGBA32 rgba) : color(rgba) {}

	Color(uint16_t r, uint16_t g, uint16_t b, uint16_t a) {
		color = ((r && 0xFF) << 24);
		color |= ((g && 0xFF) << 16);
		color |= ((b && 0xFF) << 8);
		color |= ((a && 0xFF)          );
	}

	Color(FColor4 fcolor) : Color(uint16_t(fcolor.r * 255), uint16_t(fcolor.g * 255), uint16_t(fcolor.b * 255), uint16_t(fcolor.a * 255)) {
	}

	void getRGBA(float& red, float& green, float& blue, float& alpha) {
		// RGBA
		const float a = ((color) & 0xff) / 255.0f;
		red = ((color >> 24) & 0xff) / 255.0f;
		green = ((color >> 16) & 0xff) / 255.0f;
		blue = ((color >> 8) & 0xff) / 255.0f;
		alpha = a;
	}

	void getFColor(FColor4& c) {
		getRGBA(c.r, c.g, c.b, c.a);
	}
};

} /* namespace graphic */

namespace utils {
POLA_BASIC_TYPES_TRAITS(graphic::FColor4)
}
} /* namespace pola */

#endif /* POLA_COLOR_H_ */
