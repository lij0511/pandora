/*
 * RectangleGeometry.cpp
 *
 *  Created on: 2016年7月14日
 *      Author: lijing
 */

#include "pola/graphic/geometries/RectangleGeometry.h"

namespace pola {
namespace graphic {

RectangleGeometry::RectangleGeometry(float x, float y, float w, float h) : Geometry2D(4, FLAG_GEOMETRY_DEFAULT | FLAG_GEOMETRY_UV) {
	addPosition({x, y});
	addPosition({x + w, y});
	addPosition({x, y + h});
	addPosition({x + w, y + h});

	addUv({0.f, 1.f});
	addUv({1.f, 1.f});
	addUv({0.f, 0.f});
	addUv({1.f, 0.f});

	setIndicesCapacity(6);
	addIndex(0);
	addIndex(1);
	addIndex(3);
	addIndex(3);
	addIndex(2);
	addIndex(0);

	computeBoundingBox();
}

RectangleGeometry::~RectangleGeometry() {
}

} /* namespace graphic */
} /* namespace pola */
