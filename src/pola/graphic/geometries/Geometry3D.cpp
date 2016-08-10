/*
 * Geometry.cpp
 *
 *  Created on: 2016年7月6日
 *      Author: lijing
 */

#include "pola/graphic/geometries/Geometry3D.h"

namespace pola {
namespace graphic {

Geometry3D::Geometry3D(size_t size, int flag) : Geometry(Geometry::Type::GEOMETRY_3D) {
	if (size > 0) {
		setCapacity(size, flag);
	}
}

Geometry3D::~Geometry3D() {
}

void Geometry3D::alloc(size_t size, int flag) {
	mPositions.resize(size);
	if ((flag & FLAG_GEOMETRY_NORMAL) == FLAG_GEOMETRY_NORMAL) {
		mNormals.resize(size);
	}
	if ((flag & FLAG_GEOMETRY_UV) == FLAG_GEOMETRY_UV) {
		mUvs.resize(size);
	}
	if ((flag & FLAG_GEOMETRY_COLOR) == FLAG_GEOMETRY_COLOR) {
		mColors.resize(size);
	}
}

void Geometry3D::setCapacity(size_t size, int flag) {
	if (mPositions.capacity() != size) {
		mPositions.reserve(size);
	}
	if ((flag & FLAG_GEOMETRY_NORMAL) == FLAG_GEOMETRY_NORMAL && mNormals.capacity() != size) {
		mNormals.reserve(size);
	}
	if ((flag & FLAG_GEOMETRY_UV) == FLAG_GEOMETRY_UV && mUvs.capacity() != size) {
		mUvs.reserve(size);
	}
	if ((flag & FLAG_GEOMETRY_COLOR) == FLAG_GEOMETRY_COLOR && mColors.capacity() != size) {
		mColors.reserve(size);
	}
}

void Geometry3D::addVerrtex(const Vertex3& v) {
	addPosition(v.pos);
}

void Geometry3D::addVerrtex(const TextureVertex3& v) {
	addPosition(v.pos);
	addUv(v.uv);
}

void Geometry3D::addVerrtex(const NormalTextureVertex3& v) {
	addPosition(v.pos);
	addNormal(v.normal);
	addUv(v.uv);
}

void Geometry3D::addVerrtex(const NormalColorTextureVertex3& v) {
	addPosition(v.pos);
	addNormal(v.normal);
	addUv(v.uv);
	addColor(v.color);
}

const pola::graphic::vec3* Geometry3D::positions() const {
	return mPositions.data();
}
pola::graphic::vec3* Geometry3D::positions() {
	return mPositions.data();
}
size_t Geometry3D::positionCount() const {
	return mPositions.size();
}
void Geometry3D::addPosition(const pola::graphic::vec3& pos) {
	mPositions.push_back(pos);
}

const pola::graphic::vec3* Geometry3D::normals() const {
	return mNormals.data();
}
pola::graphic::vec3* Geometry3D::normals() {
	return mNormals.data();
}
size_t Geometry3D::normalCount() const {
	return mNormals.size();
}
void Geometry3D::addNormal(const pola::graphic::vec3& nor) {
	mNormals.push_back(nor);
}

const pola::graphic::vec2* Geometry3D::uvs() const {
	return mUvs.data();
}
pola::graphic::vec2* Geometry3D::uvs() {
	return mUvs.data();
}
size_t Geometry3D::uvCount() const {
	return mUvs.size();
}
void Geometry3D::addUv(const pola::graphic::vec2& uv) {
	mUvs.push_back(uv);
}

const pola::graphic::FColor4* Geometry3D::colors() const {
	return mColors.data();
}
pola::graphic::FColor4* Geometry3D::colors() {
	return mColors.data();
}
size_t Geometry3D::colorCount() const {
	return mColors.size();
}
void Geometry3D::addColor(const pola::graphic::FColor4& cor) {
	mColors.push_back(cor);
}

void Geometry3D::computeBoundingBox() {
	mBoundingBox.setFromPoints(positions(), positionCount());
}

bool Geometry3D::bufferd() {
	return false;
}

} /* namespace graphic */
} /* namespace pola */
