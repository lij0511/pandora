/*
 * Geometry2D.cpp
 *
 *  Created on: 2016年7月14日
 *      Author: lijing
 */

#include "pola/graphic/geometries/Geometry2D.h"

namespace pola {
namespace graphic {

Geometry2D::Geometry2D(size_t size, int flag) : Geometry(Geometry::Type::GEOMETRY_2D) {
	if (size > 0) {
		setCapacity(size, flag);
	}
}

Geometry2D::~Geometry2D() {
}

void Geometry2D::alloc(size_t size, int flag) {
	mPositions.resize(size);
	if ((flag & FLAG_GEOMETRY_UV) == FLAG_GEOMETRY_UV) {
		mUvs.resize(size);
	}
	if ((flag & FLAG_GEOMETRY_COLOR) == FLAG_GEOMETRY_COLOR) {
		mColors.resize(size);
	}
}

void Geometry2D::setCapacity(size_t size, int flag) {
	if (mPositions.capacity() != size) {
		mPositions.reserve(size);
	}
	if ((flag & FLAG_GEOMETRY_UV) == FLAG_GEOMETRY_UV && mUvs.capacity() != size) {
		mUvs.reserve(size);
	}
	if ((flag & FLAG_GEOMETRY_COLOR) == FLAG_GEOMETRY_COLOR && mColors.capacity() != size) {
		mColors.reserve(size);
	}
}

void Geometry2D::addVerrtex(const Vertex2& v) {
	addPosition(v.pos);
}

void Geometry2D::addVerrtex(const TextureVertex2& v) {
	addPosition(v.pos);
	addUv(v.uv);
}

void Geometry2D::addVerrtex(const ColorTextureVertex2& v) {
	addPosition(v.pos);
	addUv(v.uv);
	addColor(v.color);
}

const pola::graphic::vec2* Geometry2D::positions() const {
	return mPositions.data();
}
pola::graphic::vec2* Geometry2D::positions() {
	return mPositions.data();
}
size_t Geometry2D::positionCount() const {
	return mPositions.size();
}
void Geometry2D::addPosition(const pola::graphic::vec2& pos) {
	mPositions.push_back(pos);
}

const pola::graphic::vec2* Geometry2D::uvs() const {
	return mUvs.data();
}
pola::graphic::vec2* Geometry2D::uvs() {
	return mUvs.data();
}
size_t Geometry2D::uvCount() const {
	return mUvs.size();
}
void Geometry2D::addUv(const pola::graphic::vec2& uv) {
	mUvs.push_back(uv);
}

const pola::graphic::FColor4* Geometry2D::colors() const {
	return mColors.data();
}
pola::graphic::FColor4* Geometry2D::colors() {
	return mColors.data();
}
size_t Geometry2D::colorCount() const {
	return mColors.size();
}
void Geometry2D::addColor(const pola::graphic::FColor4& cor) {
	mColors.push_back(cor);
}

void Geometry2D::computeBoundingBox() {
	mBoundingBox.setFromPoints(positions(), positionCount());
}

} /* namespace graphic */
} /* namespace pola */
