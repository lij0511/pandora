/*
 * GLShaderLib.cpp
 *
 *  Created on: 2016年6月18日
 *      Author: lijing
 */

#include "graphic/gl/GLShaderLib.h"

namespace pola {
namespace graphic {

const char* GLShaderLib::VS_MainUnifroms() {
	return "uniform mat4 u_projection;\n"
			"uniform mat4 u_view;\n";
}

const char* GLShaderLib::VS_MainAttributes() {
	return "attribute vec4 a_position;\n"
			"attribute vec2 a_texCoords;\n"
			"attribute vec3 a_normal;\n";
}

const char* GLShaderLib::VS_MainPosition() {
	return "  gl_Position = u_projection * u_view * a_position;\n";
}

const char* GLShaderLib::FS_MainHeader() {
	return "#ifdef GL_ES\n"
			"#define LOWP lowp\n"
			"precision highp float;\n"
			"#else\n"
			"#define LOWP \n"
			"#endif\n";
}

} /* namespace graphic */
} /* namespace pola */
