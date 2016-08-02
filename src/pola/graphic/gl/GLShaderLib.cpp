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
	return "uniform mat4 u_projection;"
			"uniform mat4 u_model;"
			"uniform mat4 u_view;"
			"uniform mat3 u_normal_matrix;";
}

const char* GLShaderLib::VS_MainAttributes() {
	return "attribute vec4 a_position;"
			"attribute vec2 a_uv;"
			"attribute vec3 a_normal;";
}

const char* GLShaderLib::VS_MainPosition() {
	return "  gl_Position = u_projection * u_view * u_model * a_position;";
}

const char* GLShaderLib::VS_Para_TextureMap() {
	return "\n#ifdef TEXTURE_MAP\n"
			"varying vec2 v_uv;"
			"\n#endif\n";
}

const char* GLShaderLib::VS_TextureMap() {
	return "\n#ifdef TEXTURE_MAP\n"
			"v_uv = a_uv;"
			"\n#endif\n";
}

const char* GLShaderLib::FS_MainHeader() {
	return "\n#ifdef GL_ES\n"
			"\n#define LOWP lowp\n"
			"precision highp float;"
			"\n#else\n"
			"\n#define LOWP\n"
			"\n#endif\n";
}

const char* GLShaderLib::FS_DiffuseColor() {
	return "vec4 diffuseColor;\n";
}

const char* GLShaderLib::FS_Para_TextureMap() {
	return "\n#ifdef TEXTURE_MAP\n"
			"uniform sampler2D u_textureMap;"
			"varying vec2 v_uv;"
			"\n#endif\n";
}

const char* GLShaderLib::FS_TextureMap() {
	return "\n#ifdef TEXTURE_MAP\n"
			"	\n#ifdef TEXTURE_MAP_A8\n"
			"	diffuseColor *= texture2D(u_textureMap,  v_uv).a;"
			"	\n#else\n"
			"	diffuseColor *= texture2D(u_textureMap,  v_uv);"
			"	\n#endif\n"
			"\n#endif\n";
}

const char* GLShaderLib::Para_Lighs() {
	/*"struct BlinnPhongMaterial {\n"
				"vec3	diffuseColor;\n"
				"vec3	specularColor;\n"
				"float	specularShininess;\n"
				"float	specularStrength;\n"
				"};\n"*/
	return
			"uniform vec3 u_ambientLight;"
			"\n#if defined(NUM_DIR_LIGHTS) && (NUM_DIR_LIGHTS > 0)\n"
			"struct DirectionalLight {"
			"vec3 direction;"
			"vec3 color;"
			"};"
			"uniform DirectionalLight u_dirLights[NUM_DIR_LIGHTS];"
			"\n#endif\n"
			"\n#if defined(NUM_POINT_LIGHTS) && (NUM_POINT_LIGHTS > 0)\n"
			"struct PointLight {"
			"vec3 position;"
			"vec3 color;"
			"float distance;"
			"};"
			"uniform PointLight u_pointLights[NUM_POINT_LIGHTS];"
			"\n#endif\n";
}

} /* namespace graphic */
} /* namespace pola */
