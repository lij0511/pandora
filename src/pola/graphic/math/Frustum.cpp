/*
 * Frustum.cpp
 *
 *  Created on: 2016年7月5日
 *      Author: lijing
 */

#include "pola/graphic/math/Frustum.h"

namespace pola {
namespace graphic {

Frustum::Frustum() {
}

Frustum::~Frustum() {
}

void Frustum::setFromMatrix(const mat4& m) {
	const float* me = m.data;
	float me0 = me[ 0 ], me1 = me[ 1 ], me2 = me[ 2 ], me3 = me[ 3 ];
	float me4 = me[ 4 ], me5 = me[ 5 ], me6 = me[ 6 ], me7 = me[ 7 ];
	float me8 = me[ 8 ], me9 = me[ 9 ], me10 = me[ 10 ], me11 = me[ 11 ];
	float me12 = me[ 12 ], me13 = me[ 13 ], me14 = me[ 14 ], me15 = me[ 15 ];

	planes[ 0 ].setComponents( me3 - me0, me7 - me4, me11 - me8, me15 - me12 ).normalize();
	planes[ 1 ].setComponents( me3 + me0, me7 + me4, me11 + me8, me15 + me12 ).normalize();
	planes[ 2 ].setComponents( me3 + me1, me7 + me5, me11 + me9, me15 + me13 ).normalize();
	planes[ 3 ].setComponents( me3 - me1, me7 - me5, me11 - me9, me15 - me13 ).normalize();
	planes[ 4 ].setComponents( me3 - me2, me7 - me6, me11 - me10, me15 - me14 ).normalize();
	planes[ 5 ].setComponents( me3 + me2, me7 + me6, me11 + me10, me15 + me14 ).normalize();
}

bool Frustum::intersectsBox(const Box3& box) const {
	vec3 p1, p2;
	for (int i = 0; i < 6; i++) {
		const Plane3& plane = planes[i];
		p1.x = plane.normal.x > 0 ? box.min().x : box.max().x;
		p2.x = plane.normal.x > 0 ? box.max().x : box.min().x;
		p1.y = plane.normal.y > 0 ? box.min().y : box.max().y;
		p2.y = plane.normal.y > 0 ? box.max().y : box.min().y;
		p1.z = plane.normal.z > 0 ? box.min().z : box.max().z;
		p2.z = plane.normal.z > 0 ? box.max().z : box.min().z;

		float d1 = plane.distanceToPoint(p1);
		float d2 = plane.distanceToPoint(p2);
		// if both outside plane, no intersection
		if (d1 < 0 && d2 < 0) {
			return false;
		}
	}
	return true;
}

} /* namespace graphic */
} /* namespace pola */
