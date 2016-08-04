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
		.append(STRINGIFY(
				varying vec4 v_worldPosition;
				uniform vec3 u_lightPos;
				vec4 packDepthToRGBA( const in float value ) {
					const vec4 bit_shift = vec4( 256.0 * 256.0 * 256.0, 256.0 * 256.0, 256.0, 1.0 );
					const vec4 bit_mask = vec4( 0.0, 1.0 / 256.0, 1.0 / 256.0, 1.0 / 256.0 );
					vec4 res = mod( value * bit_shift * vec4( 255 ), vec4( 256 ) ) / vec4( 255 );
					res -= res.xxyz * bit_mask;
					return res;
				}
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
