/*
 * Material.cpp
 *
 *  Created on: 2016年5月23日
 *      Author: lijing
 */

#include <typeinfo>
#include "graphic/Material.h"
#ifdef OGL_RENDERER
#include "graphic/gl/GLProgram.h"
#include "graphic/gl/GLShaderLib.h"
#endif

#include "utils/StringBuffer.h"

namespace pola {
namespace graphic {

Material::Material() : mVertexShader(true), mFragmentShader(true) {
}

Material::~Material() {
}

const utils::String Material::getVertexShader() {
	if (mVertexShader.isEmpty()) {
		mVertexShader = generateVertexShader();
	}
	return mVertexShader;
}

const utils::String Material::getFragmentShader() {
	if (mFragmentShader.isEmpty()) {
		mFragmentShader = generateFragmentShader();
	}
	return mFragmentShader;
}

void Material::bind(Program* program) {
}

const char* Material::getMaterialType() const {
	if (isShaderMaterial()) {
		return nullptr;
	} else {
		return typeid(*this).name();
	}
}

const utils::String Material::generateVertexShader() {
	utils::StringBuffer sb;
#ifdef OGL_RENDERER
	sb.append("void main()\n"
			"{\n");
	sb.append(GLShaderLib::VS_MainPosition());
	sb.append("}\n");
#endif
	utils::String s;
	sb.release(s);
	return s;
}

const utils::String Material::generateFragmentShader() {
	utils::StringBuffer sb(256);
#ifdef OGL_RENDERER
	sb.append(GLShaderLib::FS_MainHeader());
	sb.append("void main()\n"
			"{\n"
			"  gl_FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
			"}\n");
#endif
	utils::String s;
	sb.release(s);
	return s;
}

bool Material::isShaderMaterial() const {
	return false;
}

} /* namespace graphic */
} /* namespace pola */
