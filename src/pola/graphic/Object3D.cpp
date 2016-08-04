/*
 * Object3D.cpp
 *
 *  Created on: 2016年8月4日
 *      Author: lijing
 */

#include "pola/graphic/Object3D.h"

namespace pola {
namespace graphic {

Object3D::Object3D() {
	mScale = {1, 1, 1};
}

Object3D::~Object3D() {
}

void Object3D::setPosition(const graphic::vec3& position) {
	mPosition = position;
}

const graphic::vec3& Object3D::getPosition() const {
	return mPosition;
}

void Object3D::setRotation(const graphic::Euler& rotation) {
	mRotation = rotation;
}

const graphic::Euler& Object3D::getRotation() const {
	return mRotation;
}

void Object3D::setScale(const graphic::vec3& scale) {
	mScale = scale;
}

const graphic::vec3& Object3D::getScale() const {
	return mScale;
}

} /* namespace graphic */
} /* namespace pola */
