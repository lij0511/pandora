/*
 * Color.h
 *
 *  Created on: 2016年1月10日
 *      Author: lijing
 */

#ifndef POLA_COLOR_H_
#define POLA_COLOR_H_

#include <stdint.h>

typedef uint32_t RGBA32; // RGBA quadruplet

#define ColorSetRGBA(r, g, b, a) 	 (r << 24) | (g << 16) | (b << 8) | (a << 0);
/** Return a RGBA32 value from 8 bit component values, with an implied value
    of 0xFF for alpha (fully opaque)
*/
#define ColorSetRGB(r, g, b)  ColorSetRGBA(r, g, b, 0xFF)
/** return the red byte from a RGBA32 value */
#define ColorGetR(color)      (((color) >> 24) & 0xFF)
/** return the green byte from a RGBA32 value */
#define ColorGetG(color)      (((color) >>  16) & 0xFF)
/** return the blue byte from a RGBA32 value */
#define ColorGetB(color)      (((color) >>  8) & 0xFF)
/** return the alpha byte from a RGBA32 value */
#define ColorGetA(color)      (((color) >> 0) & 0xFF)

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
	FColor4(float r = 0, float g = 0, float b = 0, float a = 1.f) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
};

struct Color {
	RGBA32 color;

	Color(RGBA32 rgba) : color(rgba) {}

	Color(uint16_t r, uint16_t g, uint16_t b, uint16_t a) {
		color = ColorSetRGBA(r, g, b, a);
	}

	Color(FColor4 fcolor) : Color(uint16_t(fcolor.r * 255), uint16_t(fcolor.g * 255), uint16_t(fcolor.b * 255), uint16_t(fcolor.a * 255)) {
	}

	void getRGBA(float& red, float& green, float& blue, float& alpha) {
		// RGBA
		red = ColorGetR(color);
		green = ColorGetG(color);
		blue = ColorGetB(color);
		alpha = ColorGetA(color);
	}

	void getFColor(FColor4& c) {
		getRGBA(c.r, c.g, c.b, c.a);
	}
};

struct RGB888 {
	uint8_t r, g, b;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_COLOR_H_ */
