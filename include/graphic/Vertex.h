/*
 * Vertex.h
 *
 *  Created on: 2016年5月19日
 *      Author: lijing
 */

#ifndef POLA_GRAPHIC_VERTEX_H_
#define POLA_GRAPHIC_VERTEX_H_

#include <stdint.h>

#include "graphic/Color.h"

namespace pola {
namespace graphic {

enum VertexType {
	TYPE_VERTEX2,
	TYPE_VERTEX2_TEXTURE,
	TYPE_VERTEX2_TEXTURE_COLOR,
	TYPE_VERTEX2_TEXTURE_ALPHA,
	TYPE_VERTEX2_COLOR,
	TYPE_VERTEX2_ALPHA,
	TYPE_VERTEX3,
	TYPE_VERTEX3_TEXTURE,
	TYPE_VERTEX3_TEXTURE_NORMAL,
	TYPE_VERTEX3_TEXTURE_COLOR,
	TYPE_VERTEX3_TEXTURE_COLOR_NORMAL,
	TYPE_VERTEX3_TEXTURE_ALPHA,
	TYPE_VERTEX3_COLOR,
	TYPE_VERTEX3_ALPHA,
	TYPE_UNKNOWN
};

struct VertexInfo {
	int item_size;
	int offset_position;
	int count_position;
	int offset_texcoord;
	int offset_color;
	int count_color;
	int offset_normal;
	int count_normal;

};
VertexInfo makeVertexInfo(VertexType type);


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

struct NormalTextureVertex3 : TextureVertex3 {
    float nx, ny, nz;

    static inline void set(NormalTextureVertex3* vertex, float x, float y, float z,
            float u, float v, float nx, float ny, float nz) {
    	TextureVertex3::set(vertex, x, y, z, u, v);

    	vertex[0].nx = nx;
		vertex[0].ny = ny;
		vertex[0].nz = nz;
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
};

struct NormalColorTextureVertex3 : ColorTextureVertex3 {
    float nx, ny, nz;

    static inline void set(NormalColorTextureVertex3* vertex, float x, float y, float z,
            float u, float v, Color c, float nx, float ny, float nz) {
    	ColorTextureVertex3::set(vertex, x, y, z, u, v, c);

    	vertex[0].nx = nx;
		vertex[0].ny = ny;
		vertex[0].nz = nz;
    }

    static inline void set(NormalColorTextureVertex3* vertex, float x, float y, float z,
			float u, float v, FColor color, float nx, float ny, float nz) {
    	ColorTextureVertex3::set(vertex, x, y, z, u, v, color);

		vertex[0].nx = nx;
		vertex[0].ny = ny;
		vertex[0].nz = nz;
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

inline VertexInfo makeVertexInfo(VertexType type) {
	VertexInfo vertexInfo;
	int float_size = sizeof(float);
	vertexInfo.offset_position = 0;
	vertexInfo.offset_normal = -1;
	vertexInfo.count_position = 2;
	vertexInfo.offset_texcoord = -1;
	vertexInfo.offset_color = -1;
	switch (type) {
	case TYPE_VERTEX2:
		vertexInfo.item_size = sizeof(Vertex2);
		break;
	case TYPE_VERTEX3:
		vertexInfo.count_position = 3;
		vertexInfo.item_size = sizeof(Vertex3);
		break;
	case TYPE_VERTEX2_TEXTURE:
		vertexInfo.offset_texcoord = 2 * float_size;
		vertexInfo.item_size = sizeof(TextureVertex2);
		break;
	case TYPE_VERTEX3_TEXTURE:
		vertexInfo.count_position = 3;
		vertexInfo.offset_texcoord = 3 * float_size;
		vertexInfo.item_size = sizeof(TextureVertex3);
		break;
	case TYPE_VERTEX3_TEXTURE_NORMAL:
		vertexInfo.count_position = 3;
		vertexInfo.offset_texcoord = 3 * float_size;
		vertexInfo.offset_normal = 5 * float_size;
		vertexInfo.item_size = sizeof(NormalTextureVertex3);
		break;
	case TYPE_VERTEX2_TEXTURE_COLOR:
		vertexInfo.offset_texcoord = 2 * float_size;
		vertexInfo.offset_color = 4 * float_size;
		vertexInfo.item_size = sizeof(ColorTextureVertex2);
		break;
	case TYPE_VERTEX3_TEXTURE_COLOR:
		vertexInfo.count_position = 3;
		vertexInfo.offset_texcoord = 3 * float_size;
		vertexInfo.offset_color = 5 * float_size;
		vertexInfo.item_size = sizeof(ColorTextureVertex3);
		break;
	case TYPE_VERTEX3_TEXTURE_COLOR_NORMAL:
		vertexInfo.count_position = 3;
		vertexInfo.offset_texcoord = 3 * float_size;
		vertexInfo.offset_color = 5 * float_size;
		vertexInfo.offset_normal = 9 * float_size;
		vertexInfo.item_size = sizeof(NormalColorTextureVertex3);
		break;
	case TYPE_VERTEX2_COLOR:
		vertexInfo.offset_color = 2 * float_size;
		vertexInfo.count_color = 4;
		vertexInfo.item_size = sizeof(ColorVertex2);
		break;
	case TYPE_VERTEX3_COLOR:
		vertexInfo.count_position = 3;
		vertexInfo.offset_color = 3 * float_size;
		vertexInfo.count_color = 4;
		vertexInfo.item_size = sizeof(ColorVertex3);
		break;
	case TYPE_VERTEX2_ALPHA:
		vertexInfo.offset_color = 2 * float_size;
		vertexInfo.count_color = 1;
		vertexInfo.item_size = sizeof(AlphaVertex2);
		break;
	case TYPE_VERTEX3_ALPHA:
		vertexInfo.count_position = 3;
		vertexInfo.offset_color = 3 * float_size;
		vertexInfo.count_color = 1;
		vertexInfo.item_size = sizeof(AlphaVertex3);
		break;
	default:
		break;
	}
	return vertexInfo;
}

}
}

#endif /* POLA_GRAPHIC_VERTEX_H_ */
