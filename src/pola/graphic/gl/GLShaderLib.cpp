/*
 * GLShaderLib.cpp
 *
 *  Created on: 2016年6月18日
 *      Author: lijing
 */

#include "pola/graphic/gl/GLShaderLib.h"

namespace pola {
namespace graphic {

const char* GLShaderLib::VS_MainUnifroms() {
	return "uniform mat4 u_projection;\n"
			"uniform mat4 u_model;\n"
			"uniform mat4 u_view;\n"
			"uniform mat3 u_normal_matrix;\n";
}

const char* GLShaderLib::VS_MainAttributes() {
	return "attribute vec4 a_position;\n"
			"attribute vec2 a_uv;\n"
			"attribute vec3 a_normal;\n";
}

const char* GLShaderLib::VS_MainPosition() {
	return "  gl_Position = u_projection * u_view * u_model * a_position;\n";
}

const char* GLShaderLib::VS_Para_TextureMap() {
	return "#ifdef TEXTURE_MAP\n"
			"varying vec2 v_uv;\n"
			"#endif\n";
}

const char* GLShaderLib::VS_TextureMap() {
	return "#ifdef TEXTURE_MAP\n"
			"v_uv = a_uv;\n"
			"#endif\n";
}

const char* GLShaderLib::FS_MainHeader() {
	return "#ifdef GL_ES\n"
			"#define LOWP lowp\n"
			"precision highp float;\n"
			"#else\n"
			"#define LOWP \n"
			"#endif\n";
}

const char* GLShaderLib::FS_DiffuseColor() {
	return "vec4 diffuseColor;\n";
}

const char* GLShaderLib::FS_Para_TextureMap() {
	return "#ifdef TEXTURE_MAP\n"
			"uniform sampler2D u_textureMap;\n"
			"varying vec2 v_uv;\n"
			"#endif\n";
}

const char* GLShaderLib::FS_TextureMap() {
	return "#ifdef TEXTURE_MAP\n"
			"diffuseColor *= texture2D(u_textureMap,  v_uv);\n"
			"#endif\n";
}

const char* GLShaderLib::Para_Lighs() {
	return
			"struct BlinnPhongMaterial {\n"
			"vec3	diffuseColor;\n"
			"vec3	specularColor;\n"
			"float	specularShininess;\n"
			"float	specularStrength;\n"
			"};\n"

			"uniform vec3 u_ambientLight;\n"
			"#if defined(NUM_DIR_LIGHTS) && NUM_DIR_LIGHTS > 0\n"
			"struct DirectionalLight {\n"
			"vec3 direction;\n"
			"vec3 color;\n"
			"};\n"
			"uniform DirectionalLight u_dirLights[NUM_DIR_LIGHTS];\n"
			"#endif\n"
			"#if defined(NUM_POINT_LIGHTS) && NUM_POINT_LIGHTS > 0\n"
			"struct PointLight {\n"
			"vec3 position;\n"
			"vec3 color;\n"
			"};\n"
			"uniform PointLight u_pointLights[NUM_POINT_LIGHTS];\n"
			"#endif\n";
}

} /* namespace graphic */
} /* namespace pola */