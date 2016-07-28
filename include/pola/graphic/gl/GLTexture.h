/*
 * GLTexture.h
 *
 *  Created on: 2016年5月19日
 *      Author: lijing
 */

#ifndef POLA_GRAPHIC_GLTEXTURE_H_
#define POLA_GRAPHIC_GLTEXTURE_H_

#include "pola/graphic/gl/GL.h"
#include "pola/graphic/Texture.h"
#include "pola/graphic/Bitmap.h"

namespace pola {
namespace graphic {

/*
 *
 */
class GLTexture: public Texture {
public:
	GLTexture();
	GLTexture(Bitmap* bitmap);
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
	 * Indicates whether this texture will use trilinear filtering.
	 */
	bool mipMap;

	bool releaseBitmap;

	Bitmap* mBitmap;

	virtual bool generateTexture();

};

}
}

#endif /* POLA_GRAPHIC_GLTEXTURE_H_ */
