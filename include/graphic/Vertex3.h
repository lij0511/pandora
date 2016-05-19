/*
 * Vertex3.h
 *
 *  Created on: 2016年5月19日
 *      Author: lijing
 */

#ifndef POLA_GRAPHIC_VERTEX3_H_
#define POLA_GRAPHIC_VERTEX3_H_

#include <stdint.h>

namespace pola {
namespace graphic {

struct Vertex3 {
	float x, y, z;

	static inline void set(Vertex3* vertex, float x, float y, float z) {
		vertex[0].x = x;
		vertex[0].y = y;
		vertex[0].z = z;
	}
};

struct TextureVertex3 : Vertex3 {
	float u, v;

	static inline void set(TextureVertex3* vertex, float x, float y, float z, float u, float v) {
		Vertex3::set(vertex, x, y, z);
		setUV(vertex, u, v);
	}

	static inline void setUV(TextureVertex3* vertex, float u, float v) {
		vertex[0].u = u;
		vertex[0].v = v;
	}
};

struct ColorTextureVertex3 : TextureVertex3 {
    float r, g, b, a;

    static inline void set(ColorTextureVertex3* vertex, float x, float y, float z,
            float u, float v, int32_t color) {
        TextureVertex3::set(vertex, x, y, z, u, v);

        // RGBA
        const float a = ((color) & 0xff) / 255.0f;
        vertex[0].r = a * ((color >> 24) & 0xff) / 255.0f;
        vertex[0].g = a * ((color >> 16) & 0xff) / 255.0f;
        vertex[0].b = a * ((color >> 8) & 0xff) / 255.0f;
        vertex[0].a = a;
    }

    static inline void set(ColorTextureVertex3* vertex, float x, float y, float z,
			float u, float v, float r, float g, float b, float a) {
		TextureVertex3::set(vertex, x, y, z, u, v);

		// RGBA
		vertex[0].r = r;
		vertex[0].g = g;
		vertex[0].b = b;
		vertex[0].a = a;
	}
};

struct ColorVertex3 : Vertex3 {
    float r, g, b, a;

    static inline void set(ColorVertex3* vertex, float x, float y, float z, int32_t color) {
    	Vertex3::set(vertex, x, y, z);

        // RGBA
        const float a = ((color) & 0xff) / 255.0f;
        vertex[0].r = a * ((color >> 24) & 0xff) / 255.0f;
        vertex[0].g = a * ((color >> 16) & 0xff) / 255.0f;
        vertex[0].b = a * ((color >> 8) & 0xff) / 255.0f;
        vertex[0].a = a;
    }

    static inline void set(ColorVertex3* vertex, float x, float y, float z,
			float r, float g, float b, float a) {
    	Vertex3::set(vertex, x, y, z);

		// RGBA
		vertex[0].r = r;
		vertex[0].g = g;
		vertex[0].b = b;
		vertex[0].a = a;
	}
};

struct AlphaVertex3 : Vertex3 {
    float alpha;

    static inline void set(AlphaVertex3* vertex, float x, float y, float z, float alpha) {
        Vertex3::set(vertex, x, y, z);
        vertex[0].alpha = alpha;
    }

    static inline void setColor(AlphaVertex3* vertex, float alpha) {
        vertex[0].alpha = alpha;
    }
};

}
}

#endif /* POLA_GRAPHIC_VERTEX2_H_ */
