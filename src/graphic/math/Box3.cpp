/*
 * Box3.cpp
 *
 *  Created on: 2016年7月5日
 *      Author: lijing
 */

#include "graphic/math/Box3.h"

namespace pola {
namespace graphic {

Box3::Box3() : mMinEdge({0.f, 0.f, 0.f}), mMaxEdge(0.f, 0.f, 0.f) {
}

Box3::~Box3() {
}

bool Box3::isEmpty() const {
	return (mMaxEdge.x < mMinEdge.x) || (mMaxEdge.y < mMinEdge.y) || (mMaxEdge.z < mMinEdge.z);
}

void Box3::set(const vec3& min, const vec3& max) {
	mMinEdge = min;
	mMaxEdge = max;
}

void Box3::setFromPoints(vec3* const points, unsigned size) {
	for (unsigned i = 0; i < size; i ++) {
		const vec3& point = points[i];
		mMinEdge.min(point);
		mMaxEdge.max(point);
	}
}

} /* namespace graphic */
} /* namespace pola */
