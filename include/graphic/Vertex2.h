/*
 * Vertex2.h
 *
 *  Created on: 2016年5月19日
 *      Author: lijing
 */

#ifndef POLA_GRAPHIC_VERTEX2_H_
#define POLA_GRAPHIC_VERTEX2_H_

#include <stdint.h>

namespace pola {
namespace graphic {

struct Vertex2 {
	float x, y;

	static inline void set(Vertex2* vertex, float x, float y) {
		vertex[0].x = x;
		vertex[0].y = y;
	}
};

struct TextureVertex2 : Vertex2 {
	float u, v;

	static inline void set(TextureVertex2* vertex, float x, float y, float u, float v) {
		Vertex2::set(vertex, x, y);
		setUV(vertex, u, v);
	}

	static inline void setUV(TextureVertex2* vertex, float u, float v) {
		vertex[0].u = u;
		vertex[0].v = v;
	}
};

struct ColorTextureVertex2 : TextureVertex2 {
    float r, g, b, a;

    static inline void set(ColorTextureVertex2* vertex, float x, float y,
            float u, float v, int32_t color) {
        TextureVertex2::set(vertex, x, y, u, v);

        // RGBA
        const float a = ((color) & 0xff) / 255.0f;
        vertex[0].r = a * ((color >> 24) & 0xff) / 255.0f;
        vertex[0].g = a * ((color >> 16) & 0xff) / 255.0f;
        vertex[0].b = a * ((color >> 8) & 0xff) / 255.0f;
        vertex[0].a = a;
    }
    static inline void set(ColorTextureVertex2* vertex, float x, float y,
    			float u, float v, float r, float g, float b, float a) {
		TextureVertex2::set(vertex, x, y, u, v);

		// RGBA
		vertex[0].r = r;
		vertex[0].g = g;
		vertex[0].b = b;
		vertex[0].a = a;
	}
};

struct ColorVertex2 : Vertex2 {
    float r, g, b, a;

    static inline void set(ColorVertex2* vertex, float x, float y, int32_t color) {
    	Vertex2::set(vertex, x, y);

        // RGBA
        const float a = ((color) & 0xff) / 255.0f;
        vertex[0].r = a * ((color >> 24) & 0xff) / 255.0f;
        vertex[0].g = a * ((color >> 16) & 0xff) / 255.0f;
        vertex[0].b = a * ((color >> 8) & 0xff) / 255.0f;
        vertex[0].a = a;
    }
    static inline void set(ColorVertex2* vertex, float x, float y,
			float r, float g, float b, float a) {
    	Vertex2::set(vertex, x, y);

		// RGBA
		vertex[0].r = r;
		vertex[0].g = g;
		vertex[0].b = b;
		vertex[0].a = a;
	}
};

struct AlphaVertex2 : Vertex2 {
    float alpha;

    static inline void set(AlphaVertex2* vertex, float x, float y, float alpha) {
        Vertex2::set(vertex, x, y);
        vertex[0].alpha = alpha;
    }

    static inline void setColor(AlphaVertex2* vertex, float alpha) {
        vertex[0].alpha = alpha;
    }
};

}
}

#endif /* POLA_GRAPHIC_VERTEX2_H_ */
