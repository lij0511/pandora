/*
 * GLTexture.h
 *
 *  Created on: 2016年5月19日
 *      Author: lijing
 */

#ifndef POLA_GRAPHIC_GLTEXTURE_H_
#define POLA_GRAPHIC_GLTEXTURE_H_

#include "graphic/gl/GL.h"
#include "graphic/Texture.h"
#include "graphic/Bitmap.h"

namespace pola {
namespace graphic {

/*
 *
 */
class GLTexture: public Texture {
public:
	GLTexture();
	virtual ~GLTexture();

	void deleteTexture();

	/**
	 * Name of the texture.
	 */
	GLuint id;
	/**
	 * Indicates whether the texture requires blending.
	 */
	bool blend;
	/**
	 * Width of the backing bitmap.
	 */
	uint32_t width;
	/**
	 * Height of the backing bitmap.
	 */
	uint32_t height;
	/**
	 * Indicates whether this texture will use trilinear filtering.
	 */
	bool mipMap;

	Bitmap* m_bitmap;

	bool generateTexture();

};

}
}

#endif /* POLA_GRAPHIC_GLTEXTURE_H_ */
