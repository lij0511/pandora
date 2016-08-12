/*
 * GLCaches.h
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#ifndef POLA_GLCACHES_H_
#define POLA_GLCACHES_H_

#include "pola/graphic/gl/GLProgramCache.h"
#include "pola/graphic/Texture.h"

namespace pola {
namespace graphic {

// Must define as many texture units as specified by REQUIRED_TEXTURE_UNITS_COUNT
static const GLenum gTextureUnits[] = {
    GL_TEXTURE0,
    GL_TEXTURE1,
    GL_TEXTURE2,
#if MAX_TEXTURE_UNITS_COUNT > 3
	GL_TEXTURE3,
#endif
#if MAX_TEXTURE_UNITS_COUNT > 4
	GL_TEXTURE4,
#endif
#if MAX_TEXTURE_UNITS_COUNT > 5
	GL_TEXTURE5,
#endif
#if MAX_TEXTURE_UNITS_COUNT > 6
	GL_TEXTURE6,
#endif
#if MAX_TEXTURE_UNITS_COUNT > 7
	GL_TEXTURE7,
#endif
#if MAX_TEXTURE_UNITS_COUNT > 8
#error "Unsupport Texture Count"
#endif
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

	GLint activeTexture() const;
	GLenum activeTexture(GLint textureUnit);
	void resetActiveTexture();

	void bindFrameBuffer(GLuint frameBuffer);
	void unbindFrameBuffer(GLuint frameBuffer);

	GLProgramCache programCache;

private:

	GLint mTextureUnit;
	GLuint mBoundTextures[MAX_TEXTURE_UNITS_COUNT];

	GLuint mFramebuffer;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_GLCACHES_H_ */
