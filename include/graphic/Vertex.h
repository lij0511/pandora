/*
 * Vertex2.h
 *
 *  Created on: 2016年5月19日
 *      Author: lijing
 */

#ifndef POLA_GRAPHIC_VERTEX2_H_
#define POLA_GRAPHIC_VERTEX2_H_

#include <stdint.h>

#include "graphic/Color.h"

namespace pola {
namespace graphic {

enum VertexType {
	TYPE_VERTEX2,
	TYPE_VERTEX3,
	TYPE_VERTEX2_TEXTURE,
	TYPE_VERTEX3_TEXTURE,
	TYPE_VERTEX2_TEXTURE_COLOR,
	TYPE_VERTEX3_TEXTURE_COLOR,
	TYPE_VERTEX2_TEXTURE_ALPHA,
	TYPE_VERTEX3_TEXTURE_ALPHA,
	TYPE_VERTEX2_COLOR,
	TYPE_VERTEX3_COLOR,
	TYPE_VERTEX2_ALPHA,
	TYPE_VERTEX3_ALPHA,
	TYPE_UNKNOWN
};

struct Vertex2 {
	float x, y;

	static inline void set(Vertex2* vertex, float x, float y) {
		vertex[0].x = x;
		vertex[0].y = y;
	}

	static VertexType type() {
		return TYPE_VERTEX2;
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

	static VertexType type() {
		return TYPE_VERTEX2_TEXTURE;
	}
};

struct ColorTextureVertex2 : TextureVertex2 {
    float r, g, b, a;

    static inline void set(ColorTextureVertex2* vertex, float x, float y,
            float u, float v, Color c) {
        TextureVertex2::set(vertex, x, y, u, v);

        c.getRGBA(vertex[0].r, vertex[0].g, vertex[0].b, vertex[0].a);
    }
    static inline void set(ColorTextureVertex2* vertex, float x, float y,
    			float u, float v, FColor color) {
		TextureVertex2::set(vertex, x, y, u, v);

		// RGBA
		vertex[0].r = color.r;
		vertex[0].g = color.g;
		vertex[0].b = color.b;
		vertex[0].a = color.a;
	}

    static VertexType type() {
		return TYPE_VERTEX2_TEXTURE_COLOR;
	}
};

struct ColorVertex2 : Vertex2 {
    float r, g, b, a;

    static inline void set(ColorVertex2* vertex, float x, float y, Color c) {
    	Vertex2::set(vertex, x, y);

    	c.getRGBA(vertex[0].r, vertex[0].g, vertex[0].b, vertex[0].a);
    }
    static inline void set(ColorVertex2* vertex, float x, float y,
			FColor color) {
    	Vertex2::set(vertex, x, y);

    	// RGBA
		vertex[0].r = color.r;
		vertex[0].g = color.g;
		vertex[0].b = color.b;
		vertex[0].a = color.a;
	}
    static VertexType type() {
		return TYPE_VERTEX2_COLOR;
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
    static VertexType type() {
		return TYPE_VERTEX2_ALPHA;
	}
};



struct Vertex3 {
	float x, y, z;

	static inline void set(Vertex3* vertex, float x, float y, float z) {
		vertex[0].x = x;
		vertex[0].y = y;
		vertex[0].z = z;
	}
	static VertexType type() {
		return TYPE_VERTEX3;
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
	static VertexType type() {
		return TYPE_VERTEX3_TEXTURE;
	}
};

struct ColorTextureVertex3 : TextureVertex3 {
    float r, g, b, a;

    static inline void set(ColorTextureVertex3* vertex, float x, float y, float z,
            float u, float v, Color c) {
        TextureVertex3::set(vertex, x, y, z, u, v);

        c.getRGBA(vertex[0].r, vertex[0].g, vertex[0].b, vertex[0].a);
    }

    static inline void set(ColorTextureVertex3* vertex, float x, float y, float z,
			float u, float v, FColor color) {
		TextureVertex3::set(vertex, x, y, z, u, v);

		// RGBA
		vertex[0].r = color.r;
		vertex[0].g = color.g;
		vertex[0].b = color.b;
		vertex[0].a = color.a;
	}
    static VertexType type() {
		return TYPE_VERTEX3_TEXTURE_COLOR;
	}
};

struct ColorVertex3 : Vertex3 {
    float r, g, b, a;

    static inline void set(ColorVertex3* vertex, float x, float y, float z, Color c) {
    	Vertex3::set(vertex, x, y, z);

    	c.getRGBA(vertex[0].r, vertex[0].g, vertex[0].b, vertex[0].a);
    }

    static inline void set(ColorVertex3* vertex, float x, float y, float z,
    		FColor color) {
		Vertex3::set(vertex, x, y, z);

		// RGBA
		vertex[0].r = color.r;
		vertex[0].g = color.g;
		vertex[0].b = color.b;
		vertex[0].a = color.a;
	}
    static VertexType type() {
		return TYPE_VERTEX3_COLOR;
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
    static VertexType type() {
		return TYPE_VERTEX3_ALPHA;
	}
};

}
}

#endif /* POLA_GRAPHIC_VERTEX2_H_ */
