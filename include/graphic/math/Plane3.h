/*
 * Plane3.h
 *
 *  Created on: 2016年7月5日
 *      Author: lijing
 */

#ifndef POLA_PLANE3_H_
#define POLA_PLANE3_H_

#include "graphic/math/Vector.h"

namespace pola {
namespace graphic {

/*
 *
 */
struct Plane3 {
	vec3 normal;
	float D;
	Plane3(const vec3& n = {1.f, 0.f, 0.f}) {
		normal = n;
		D = 0;
	}

	Plane3& set(const vec3& n, float d);

	Plane3& setComponents(float x, float y, float z, float w);

	Plane3& setFromNormalAndCoplanarPoint(const vec3& n, const vec3& p);

	Plane3& normalize();

	Plane3& negate();
};

inline Plane3& Plane3::set(const vec3& n, float d) {
	normal = n;
	D = d;
	return *this;
}

Plane3& Plane3::setComponents(float x, float y, float z, float w) {
	normal.x = x;
	normal.y = y;
	normal.z = z;
	D = w;
	return *this;
}

Plane3& Plane3::setFromNormalAndCoplanarPoint(const vec3& n, const vec3& p) {
	normal = n;
	D = - p.dot(normal);
	return *this;
}

Plane3& Plane3::normalize() {
	float inverseNormalLength = 1.0f / normal.length();
	normal *= inverseNormalLength;
	D *= inverseNormalLength;
	return *this;
}

Plane3& Plane3::negate() {
	normal.negate();
	D *= -1;
	return *this;
}

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_PLANE3_H_ */
