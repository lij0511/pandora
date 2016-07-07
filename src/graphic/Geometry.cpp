/*
 * Geometry.cpp
 *
 *  Created on: 2016年7月6日
 *      Author: lijing
 */

#include "graphic/Geometry.h"

namespace pola {
namespace graphic {

Geometry::Geometry(size_t size, int flag) {
	if (size > 0) {
		mPositions.setCapacity(size);
		if ((flag & FLAG_GEOMETRY_NORMAL) == FLAG_GEOMETRY_NORMAL) {
			mNormals.setCapacity(size);
		}
		if ((flag & FLAG_GEOMETRY_UV) == FLAG_GEOMETRY_UV) {
			mUvs.setCapacity(size);
		}
		if ((flag & FLAG_GEOMETRY_COLOR) == FLAG_GEOMETRY_COLOR) {
			mColors.setCapacity(size);
		}
	}
}

Geometry::~Geometry() {
}

void Geometry::alloc(size_t size, int flag) {
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

void Geometry::addVerrtex(const Vertex3& v) {
	addPosition(v.pos);
}

void Geometry::addVerrtex(const TextureVertex3& v) {
	addPosition(v.pos);
	addUv(v.uv);
}

void Geometry::addVerrtex(const NormalTextureVertex3& v) {
	addPosition(v.pos);
	addNormal(v.normal);
	addUv(v.uv);
}

void Geometry::addVerrtex(const NormalColorTextureVertex3& v) {
	addPosition(v.pos);
	addNormal(v.normal);
	addUv(v.uv);
	addColor(v.color);
}

const pola::graphic::vec3* Geometry::positions() const {
	return mPositions.array();
}
pola::graphic::vec3* Geometry::positions() {
	return mPositions.editArray();
}
size_t Geometry::positionCount() const {
	return mPositions.size();
}
void Geometry::addPosition(const pola::graphic::vec3& pos) {
	mPositions.push(pos);
}

const pola::graphic::vec3* Geometry::normals() const {
	return mNormals.array();
}
pola::graphic::vec3* Geometry::normals() {
	return mNormals.editArray();
}
size_t Geometry::normalCount() const {
	return mNormals.size();
}
void Geometry::addNormal(const pola::graphic::vec3& nor) {
	mNormals.push(nor);
}

const pola::graphic::vec2* Geometry::uvs() const {
	return mUvs.array();
}
pola::graphic::vec2* Geometry::uvs() {
	return mUvs.editArray();
}
size_t Geometry::uvCount() const {
	return mUvs.size();
}
void Geometry::addUv(const pola::graphic::vec2& uv) {
	mUvs.push(uv);
}

const pola::graphic::FColor4* Geometry::colors() const {
	return mColors.array();
}
pola::graphic::FColor4* Geometry::colors() {
	return mColors.editArray();
}
size_t Geometry::colorCount() const {
	return mColors.size();
}
void Geometry::addColor(const pola::graphic::FColor4& cor) {
	mColors.push(cor);
}

const uint16_t* Geometry::indices() const {
	return mIndices.array();
}
uint16_t* Geometry::indices() {
	return mIndices.editArray();
}
size_t Geometry::indexCount() const {
	return mIndices.size();
}
void Geometry::addIndex(uint16_t index) {
	mIndices.push(index);
}

bool Geometry::bufferd() {
	return false;
}

} /* namespace graphic */
} /* namespace pola */
