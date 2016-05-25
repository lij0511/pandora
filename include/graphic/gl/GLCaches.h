/*
 * GLCaches.h
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#ifndef POLA_GLCACHES_H_
#define POLA_GLCACHES_H_

#include "graphic/gl/GLProgramCache.h"

namespace pola {
namespace graphic {

#define REQUIRED_TEXTURE_UNITS_COUNT 3

// Must define as many texture units as specified by REQUIRED_TEXTURE_UNITS_COUNT
static const GLenum gTextureUnits[] = {
    GL_TEXTURE0,
    GL_TEXTURE1,
    GL_TEXTURE2
};

class GLCaches {
private:
	GLCaches();
public:
	static GLCaches& get();
	virtual ~GLCaches();

	void bindTexture(GLuint texture);
	void bindTexture(GLenum target, GLuint texture);
	void unbindTexture(GLuint texture);
	void deleteTexture(GLuint texture);
	void resetBoundTextures();

	void activeTexture(GLuint textureUnit);
	void resetActiveTexture();

	GLProgramCache programCache;

private:

	GLuint mTextureUnit;
	GLuint mBoundTextures[REQUIRED_TEXTURE_UNITS_COUNT];
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_GLCACHES_H_ */
