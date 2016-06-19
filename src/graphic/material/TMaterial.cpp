/*
 * TMaterial.cpp
 *
 *  Created on: 2016年6月18日
 *      Author: lijing
 */

#include "graphic/material/TMaterial.h"
#ifdef OGL_RENDERER
#include "graphic/gl/GLProgram.h"
#include "graphic/gl/GLShaderLib.h"
#include "graphic/gl/GLTexture.h"
#include "graphic/gl/GLCaches.h"
#endif

#include "utils/StringBuffer.h"

namespace pola {
namespace graphic {

TMaterial::TMaterial(Texture* texture) : mTexture(texture) {
}

TMaterial::~TMaterial() {
}

const utils::String TMaterial::generateVertexShader() {
	utils::StringBuffer sb;
#ifdef OGL_RENDERER
	sb.append("varying vec2 v_uv;\n"
			"void main()\n"
			"{\n"
			"  v_uv = a_uv;\n");
	sb.append(GLShaderLib::VS_MainPosition());
	sb.append("}\n");
#endif
	utils::String s;
	sb.release(s);
	return s;
}

const utils::String TMaterial::generateFragmentShader() {
	utils::StringBuffer sb(256);
#ifdef OGL_RENDERER
	sb.append(GLShaderLib::FS_MainHeader());
	sb.append("uniform sampler2D u_texture;\n"
			"varying vec2 v_uv;\n"
			"void main()\n"
			"{\n"
			"  gl_FragColor = texture2D(u_texture,  v_uv);\n"
			"}\n");
#endif
	utils::String s;
	sb.release(s);
	return s;
}

void TMaterial::bind(GraphicContext* graphic, Program* program) {
#ifdef OGL_RENDERER
	GLTexture* glTexture = (GLTexture*) mTexture;
	if (glTexture->generateTexture()) {
		GLCaches::get().resetActiveTexture();
		GLCaches::get().activeTexture(0);
		GLCaches::get().bindTexture(glTexture->id);
		GLProgram* glProgram = (GLProgram*) program;
		GLint u_texture;
		if (glProgram->fetchUniform(utils::String("u_texture", true), u_texture)) {
			glUniform1i(u_texture, 0);
		}
	}
#endif
}

} /* namespace graphic */
} /* namespace pola */
