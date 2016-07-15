/*
 * Box3.cpp
 *
 *  Created on: 2016年7月5日
 *      Author: lijing
 */

#include "pola/graphic/math/Box3.h"
#include <float.h>

namespace pola {
namespace graphic {

Box3::Box3() {
	makeEmpty();
}

Box3::~Box3() {
}

bool Box3::isEmpty() const {
	return (mMaxEdge.x < mMinEdge.x) || (mMaxEdge.y < mMinEdge.y) || (mMaxEdge.z < mMinEdge.z);
}

void Box3::makeEmpty() {
	mMinEdge.x = mMinEdge.y = mMinEdge.z = FLT_MAX;
	mMaxEdge.x = mMaxEdge.y = mMaxEdge.z = FLT_MIN;
}

void Box3::set(const vec3& min, const vec3& max) {
	mMinEdge = min;
	mMaxEdge = max;
}

void Box3::applyMatrix(const mat4& m) {
	if (isEmpty()) return;
	Point3F points[8];

	const vec3& min = mMinEdge;
	const vec3& max = mMaxEdge;
	// NOTE: I am using a binary pattern to specify all 2^3 combinations below
	points[ 0 ] = {min.x, min.y, min.z};
	points[0].applyMatrix4(m.data); // 000
	points[ 1 ] = {min.x, min.y, max.z};
	points[1].applyMatrix4(m.data); // 001
	points[ 2 ] = {min.x, max.y, min.z};
	points[2].applyMatrix4(m.data); // 010
	points[ 3 ] = {min.x, max.y, max.z};
	points[3].applyMatrix4(m.data); // 011
	points[ 4 ] = {max.x, min.y, min.z};
	points[4].applyMatrix4(m.data); // 100
	points[ 5 ] = {max.x, min.y, max.z};
	points[5].applyMatrix4(m.data); // 101
	points[ 6 ] = {max.x, max.y, min.z};
	points[6].applyMatrix4(m.data); // 110
	points[ 7 ] = {max.x, max.y, max.z};
	points[7].applyMatrix4(m.data);	// 111

	setFromPoints( points, 8 );
}

void Box3::setFromPoints(Point3F* const points, unsigned size) {
	makeEmpty();
	for (unsigned i = 0; i < size; i ++) {
		const vec3& point = points[i];
		expandByPoint(point);
	}
}

void Box3::setFromPoints(Point2F* const points, unsigned size) {
	makeEmpty();
	for (unsigned i = 0; i < size; i ++) {
		const vec2& point = points[i];
		expandByPoint(point);
	}
}

void Box3::expandByPoint(const Point2F& point) {
	expandByPoint({point.x, point.y, 0.f});
}
void Box3::expandByPoint(const Point3F& point) {
	mMinEdge.min(point);
	mMaxEdge.max(point);
}

const vec3& Box3::min() const {
	return mMinEdge;
}
const vec3& Box3::max() const {
	return mMaxEdge;
}

} /* namespace graphic */
} /* namespace pola */
