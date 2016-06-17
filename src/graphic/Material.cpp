/*
 * Material.cpp
 *
 *  Created on: 2016年5月23日
 *      Author: lijing
 */

#include <typeinfo>
#include "graphic/Material.h"

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

const char* Material::getMaterialType() const {
	if (isShaderMaterial()) {
		return nullptr;
	} else {
		return typeid(*this).name();
	}
}

bool Material::isShaderMaterial() const {
	return false;
}

} /* namespace graphic */
} /* namespace pola */
