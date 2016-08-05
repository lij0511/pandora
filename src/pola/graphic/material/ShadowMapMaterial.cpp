/*
 * ShadowMapMaterial.cpp
 *
 *  Created on: 2016年8月3日
 *      Author: lijing
 */

#include "pola/graphic/material/ShadowMapMaterial.h"
#include "pola/utils/StringBuffer.h"

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
	sb.append("varying vec4 v_worldPosition;"
			"void main()"
			"{")
		.append(GLShaderLib::VS_MainPosition())
		.append("v_worldPosition = u_model * a_position;"
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
				varying vec4 v_worldPosition;
				uniform vec3 u_lightPos;
				void main()
				{
		))
		.append("  gl_FragColor = packDepthToRGBA(length( v_worldPosition.xyz - u_lightPos) / 1000.0);"
			"}");
#endif
	utils::String s;
	sb.release(s);
	return s;
}

} /* namespace graphic */
} /* namespace pola */
