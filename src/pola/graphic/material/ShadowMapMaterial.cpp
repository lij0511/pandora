/*
 * ShadowMapMaterial.cpp
 *
 *  Created on: 2016年8月3日
 *      Author: lijing
 */

#include "pola/graphic/material/ShadowMapMaterial.h"
#include "pola/utils/StringBuffer.h"

#ifdef OGL_RENDERER
#include "pola/graphic/gl/GLProgram.h"
#include "pola/graphic/gl/GLShaderLib.h"
#include "pola/graphic/gl/GLTexture.h"
#include "pola/graphic/gl/GLRenderTarget.h"
#include "pola/graphic/gl/GLCaches.h"
#endif

namespace pola {
namespace graphic {

ShadowMapMaterial::ShadowMapMaterial() {
}

ShadowMapMaterial::~ShadowMapMaterial() {
}

void ShadowMapMaterial::setLightPosition(const vec3& lightPos) {
	mLightPosition = lightPos;
}

void ShadowMapMaterial::bind(GraphicContext* graphic, Program* program) {
#ifdef OGL_RENDERER
	GLProgram* glProgram = (GLProgram*) program;
	static utils::String u_lightPos("u_lightPos");
	GLint u_lightPosH;
	if (glProgram->fetchUniform(u_lightPos, u_lightPosH)) {
		glUniform3f(u_lightPosH, mLightPosition.x, mLightPosition.y, mLightPosition.z);
	}
#endif
}

const utils::String ShadowMapMaterial::generateVertexShader() {
	utils::StringBuffer sb(256);
#ifdef OGL_RENDERER
	sb.append(
			"void main()"
			"{")
		.append(GLShaderLib::VS_MainPosition())
		.append(
				"}");
#endif
	utils::String s;
	sb.release(s);
	return s;
}

const utils::String ShadowMapMaterial::generateFragmentShader() {
	utils::StringBuffer sb(256);
#ifdef OGL_RENDERER
	sb.append(GLShaderLib::FS_MainHeader())
		.append(GLShaderLib::Para_Packing())
		.append(STRINGIFY(
				void main()
				{
		))
		.append("  gl_FragColor = packDepthToRGBA( gl_FragCoord.z );"
			"}");
#endif
	utils::String s;
	sb.release(s);
	return s;
}

} /* namespace graphic */
} /* namespace pola */
