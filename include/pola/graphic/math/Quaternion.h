/*
 * Quaternion.h
 *
 *  Created on: 2016年6月3日
 *      Author: lijing
 */

#ifndef POLA_QUATERNION_H_
#define POLA_QUATERNION_H_

#include <cmath>

namespace pola {
namespace graphic {

struct Quaternion {
	float x;
	float y;
	float z;
	float w;

	Quaternion(float x = 0, float y = 0, float z = 0, float w = 1) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	void set(float xx, float yy, float zz, float ww) {
		x = xx;
		y = yy;
		z = zz;
		w = ww;
	}

	void set(const vec3& axis, float angle) {
		float halfAngle = angle * 0.5f;
		float sinHalfAngle = sinf(halfAngle);

		vec3 normal(axis);
		normal.normalize();
		x = normal.x * sinHalfAngle;
		y = normal.y * sinHalfAngle;
		z = normal.z * sinHalfAngle;
		w = cosf(halfAngle);
	}

	float lengthSquared() const {
		return x * x + y * y + z * z + w * w;
	}

	float length() const {
		return sqrt(lengthSquared());
	}

	float dot(const Quaternion& v) const {
		return x * v.x + y * v.y + z * v.z + w * v.w;
	}

	void normalize() {
		float len = length();
		if (len != 0 && len != 1.0f) {
			float s = 1.0f / len;
			x *= s;
			y *= s;
			z *= s;
			w *= s;
		}
	}

	void operator+=(const Quaternion& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
	}

	void operator-=(const Quaternion& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
	}

	void operator+=(const float v) {
		x += v;
		y += v;
		z += v;
		w += v;
	}

	void operator-=(const float v) {
		x -= v;
		y -= v;
		z -= v;
		w -= v;
	}

	void operator/=(float s) {
		x /= s;
		y /= s;
		z /= s;
		w /= s;
	}

	void operator*=(float s) {
		x *= s;
		y *= s;
		z *= s;
		w *= s;
	}

	Quaternion operator+(const Quaternion& v) const {
		return (Quaternion){x + v.x, y + v.y, z + v.z, w + v.w};
	}

	Quaternion operator-(const Quaternion& v) const {
		return (Quaternion){x - v.x, y - v.y, z - v.z, w - v.w};
	}

	Quaternion operator/(float s) const {
		return (Quaternion){x / s, y / s, z / s, w / s};
	}

	Quaternion operator*(float s) const {
		return (Quaternion){x * s, y * s, z * s, w * s};
	}

	bool operator==(const Quaternion& v) {
		return x == v.x && y == v.y && z == v.z && w == v.w;
	}

	bool operator!=(const Quaternion& v) {
		return !(*this == v);
	}

};

typedef Quaternion quat4;

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_QUATERNION_H_ */
