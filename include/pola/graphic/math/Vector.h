/*
 * Vector.h
 *
 *  Created on: 2015年12月4日
 *      Author: lijing
 */

#ifndef POLA_GRAPHIC_VECTOR_H_
#define POLA_GRAPHIC_VECTOR_H_

#include <cmath>
#include "pola/utils/TypeHelpers.h"

namespace pola {
namespace graphic {

struct Vector2 {
	float x;
	float y;

	Vector2(float x = 0, float y = 0) {
		this->x = x;
		this->y = y;
	}

	float lengthSquared() const {
		return x * x + y * y;
	}

	float length() const {
		return sqrt(x * x + y * y);
	}

	void operator+=(const Vector2& v) {
		x += v.x;
		y += v.y;
	}

	void operator-=(const Vector2& v) {
		x -= v.x;
		y -= v.y;
	}

	void operator+=(const float v) {
		x += v;
		y += v;
	}

	void operator-=(const float v) {
		x -= v;
		y -= v;
	}

	void operator/=(float s) {
		x /= s;
		y /= s;
	}

	void operator*=(float s) {
		x *= s;
		y *= s;
	}

	Vector2 operator+(const Vector2& v) const {
		return (Vector2){x + v.x, y + v.y};
	}

	Vector2 operator-(const Vector2& v) const {
		return (Vector2){x - v.x, y - v.y};
	}

	Vector2 operator/(float s) const {
		return (Vector2){x / s, y / s};
	}

	Vector2 operator*(float s) const {
		return (Vector2){x * s, y * s};
	}

	bool operator==(const Vector2& v) {
		return x == v.x && y == v.y;
	}

	bool operator!=(const Vector2& v) {
		return !(*this == v);
	}

	void normalize() {
		float s = 1.0f / length();
		x *= s;
		y *= s;
	}

	Vector2 copyNormalized() const {
		Vector2 v = {x, y};
		v.normalize();
		return v;
	}

	float dot(const Vector2& v) const {
		return x * v.x + y * v.y;
	}

	//! Creates an interpolated vector between this vector and another vector.
	/** \param other The other vector to interpolate with.
	\param d Interpolation value between 0.0f (all the other vector) and 1.0f (all this vector).
	Note that this is the opposite direction of interpolation to getInterpolated_quadratic()
	\return An interpolated vector.  This vector is not modified. */
	Vector2 getInterpolated(const Vector2& other, float d) const {
		const float inv = 1.0 - d;
		return Vector2((other.x*inv + x*d), (other.y*inv + y*d));
	}

	/** equals to Vector2(0,0) */
	static const Vector2 ZERO;
	/** equals to Vector2(1,1) */
	static const Vector2 ONE;
	/** equals to Vector2(1,0) */
	static const Vector2 UNIT_X;
	/** equals to Vector2(0,1) */
	static const Vector2 UNIT_Y;
	/** equals to Vector2(0.5, 0.5) */
	static const Vector2 ANCHOR_MIDDLE;
	/** equals to Vector2(0, 0) */
	static const Vector2 ANCHOR_BOTTOM_LEFT;
	/** equals to Vector2(0, 1) */
	static const Vector2 ANCHOR_TOP_LEFT;
	/** equals to Vector2(1, 0) */
	static const Vector2 ANCHOR_BOTTOM_RIGHT;
	/** equals to Vector2(1, 1) */
	static const Vector2 ANCHOR_TOP_RIGHT;
	/** equals to Vector2(1, 0.5) */
	static const Vector2 ANCHOR_MIDDLE_RIGHT;
	/** equals to Vector2(0, 0.5) */
	static const Vector2 ANCHOR_MIDDLE_LEFT;
	/** equals to Vector2(0.5, 1) */
	static const Vector2 ANCHOR_MIDDLE_TOP;
	/** equals to Vector2(0.5, 0) */
	static const Vector2 ANCHOR_MIDDLE_BOTTOM;
};

struct Vector3 {
    float x;
    float y;
    float z;

    Vector3(float x = 0, float y = 0, float z = 0) {
    	this->x = x;
    	this->y = y;
    	this->z = z;
    }

    void set(float xx, float yy, float zz) {
    	x = xx;
    	y = yy;
    	z = zz;
    }

    float lengthSquared() const {
		return x * x + y * y + z * z;
	}

    float length() const {
		return sqrt(x * x + y * y + z * z);
	}

	void operator+=(const Vector3& v) {
		x += v.x;
		y += v.y;
		z += v.z;
	}

	void operator-=(const Vector3& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}

	void operator+=(const float v) {
		x += v;
		y += v;
		z += v;
	}

	void operator-=(const float v) {
		x -= v;
		y -= v;
		z -= v;
	}

	void operator/=(float s) {
		x /= s;
		y /= s;
		z /= s;
	}

	void operator*=(float s) {
		x *= s;
		y *= s;
		z *= s;
	}

    Vector3 operator+(const Vector3& v) const {
        return (Vector3){x + v.x, y + v.y, z + v.z};
    }

    Vector3 operator-(const Vector3& v) const {
        return (Vector3){x - v.x, y - v.y, z - v.z};
    }

    Vector3 operator-() const {
    	return Vector3(- x,  - y, - z);
    }

    Vector3 operator/(float s) const {
        return (Vector3){x / s, y / s, z / s};
    }

    Vector3 operator*(float s) const {
        return (Vector3){x * s, y * s, z * s};
    }

    bool operator==(const Vector3& v) {
		return x == v.x && y == v.y && z == v.z;
	}

	bool operator!=(const Vector3& v) {
		return !(*this == v);
	}

    void normalize() {
    	float len = lengthSquared();
    	if (len == 0.0f || len == 1.0f) {
    		return;
    	}
		float s = 1.0f / sqrt(len);
		x *= s;
		y *= s;
		z *= s;
	}

	Vector3 copyNormalized() const {
		Vector3 v = {x, y, z};
		v.normalize();
		return v;
	}

	void cross(const Vector3& vector) {
		float x = this->y * vector.z - this->z * vector.y;
		float y = this->z * vector.x - this->x * vector.z;
		float z = this->x * vector.y - this->y * vector.x;
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3 copyCross(const Vector3& vector) const {
		Vector3 v = {x, y, z};
		v.cross(vector);
		return v;
	}

	void negate() {
		x = - x;
		y = - y;
		z = - z;
	}

	float dot(const Vector3& vector) const {
		return x * vector.x + y * vector.y + z * vector.z;
	}

	void min(const Vector3& v) {
		x = fminf(x, v.x);
		y = fminf(y, v.y);
		z = fminf(z, v.z);
	}

	void max(const Vector3& v) {
		x = fmaxf(x, v.x);
		y = fmaxf(y, v.y);
		z = fmaxf(z, v.z);
	}

	void applyQuaternion(float xx, float yy, float zz, float ww) {
		float qx = xx, qy = yy, qz = zz, qw = ww;

		// calculate quat * vector

		float ix =  qw * x + qy * z - qz * y;
		float iy =  qw * y + qz * x - qx * z;
		float iz =  qw * z + qx * y - qy * x;
		float iw = - qx * x - qy * y - qz * z;

		// calculate result * inverse quat

		x = ix * qw + iw * - qx + iy * - qz - iz * - qy;
		y = iy * qw + iw * - qy + iz * - qx - ix * - qz;
		z = iz * qw + iw * - qz + ix * - qy - iy * - qx;
	}

	void applyMatrix4(const float m[]) {
		const float* e = m;
		float x = this->x;
		float y = this->y;
		float z = this->z;
		this->x = e[ 0 ] * x + e[ 4 ] * y + e[ 8 ]  * z + e[ 12 ];
		this->y = e[ 1 ] * x + e[ 5 ] * y + e[ 9 ]  * z + e[ 13 ];
		this->z = e[ 2 ] * x + e[ 6 ] * y + e[ 10 ] * z + e[ 14 ];
	}

	void setFromMatrixPosition(const float m[]) {
		this->x = m[12];
		this->y = m[13];
		this->z = m[14];
	}

	//! Creates an interpolated vector between this vector and another vector.
	/** \param other The other vector to interpolate with.
	\param d Interpolation value between 0.0f (all the other vector) and 1.0f (all this vector).
	Note that this is the opposite direction of interpolation to getInterpolated_quadratic()
	\return An interpolated vector.  This vector is not modified. */
	Vector3 getInterpolated(const Vector3& other, float d) const {
		const float inv = 1.0 - d;
		return Vector3((other.x*inv + x*d), (other.y*inv + y*d), (other.z*inv + z*d));
	}

	Vector3 getHorizontalAngle() const {
		Vector3 angle;
		static double RADTODEG = 180.0 / M_PI;

		const double tmp = (atan2(x, z) * RADTODEG);
		angle.y = tmp;

		if (angle.y < 0)
			angle.y += 360;
		if (angle.y >= 360)
			angle.y -= 360;

		const double z1 = sqrt(x*x + z*z);

		angle.x = (atan2(z1, y) * RADTODEG - 90.0);

		if (angle.x < 0)
			angle.x += 360;
		if (angle.x >= 360)
			angle.x -= 360;
		return angle;
	}

	/** equals to Vector3(0,0,0) */
	static const Vector3 ZERO;
	/** equals to Vector3(1,1,1) */
	static const Vector3 ONE;
	/** equals to Vector3(1,0,0) */
	static const Vector3 UNIT_X;
	/** equals to Vector3(0,1,0) */
	static const Vector3 UNIT_Y;
	/** equals to Vector3(0,0,1) */
	static const Vector3 UNIT_Z;
};

struct Vector4 {
    float x;
    float y;
    float z;
    float w;

    Vector4(float x = 0, float y = 0, float z = 0, float w = 0) {
    	this->x = x;
    	this->y = y;
    	this->z = z;
    	this->w = w;
    }

    float lengthSquared() const {
		return x * x + y * y + z * z + w * w;
	}

    float length() const {
		return sqrt(x * x + y * y + z * z + w * w);
	}

	void operator+=(const Vector4& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
	}

	void operator-=(const Vector4& v) {
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

    Vector4 operator+(const Vector4& v) const {
        return (Vector4){x + v.x, y + v.y, z + v.z, w + v.w};
    }

    Vector4 operator-(const Vector4& v) const {
        return (Vector4){x - v.x, y - v.y, z - v.z, w - v.w};
    }

    Vector4 operator/(float s) const {
        return (Vector4){x / s, y / s, z / s, w / s};
    }

    Vector4 operator*(float s) const {
        return (Vector4){x * s, y * s, z * s, w * s};
    }

    bool operator==(const Vector4& v) {
		return x == v.x && y == v.y && z == v.z && w == v.w;
	}

	bool operator!=(const Vector4& v) {
		return !(*this == v);
	}

    void normalize() {
    	float len = lengthSquared();
    	if (len == 0.0f || len == 1.0f) {
    		return;
    	}
		float s = 1.0f / sqrt(len);
		x *= s;
		y *= s;
		z *= s;
		w *= s;
	}

    Vector4 copyNormalized() const {
    	Vector4 v = {x, y, z, w};
		v.normalize();
		return v;
	}

	void negate() {
		x = - x;
		y = - y;
		z = - z;
		w = - w;
	}

	float dot(const Vector4& vector) const {
		return x * vector.x + y * vector.y + z * vector.z + w * vector.w;
	}

	void min(const Vector4& v) {
		x = fminf(x, v.x);
		y = fminf(y, v.y);
		z = fminf(z, v.z);
		w = fminf(w, v.w);
	}

	void max(const Vector4& v) {
		x = fmaxf(x, v.x);
		y = fmaxf(y, v.y);
		z = fmaxf(z, v.z);
		w = fmaxf(w, v.w);
	}

	/** equals to Vector4(0,0,0,0) */
	static const Vector4 ZERO;
	/** equals to Vector4(1,1,1,1) */
	static const Vector4 ONE;
	/** equals to Vector4(1,0,0,0) */
	static const Vector4 UNIT_X;
	/** equals to Vector4(0,1,0,0) */
	static const Vector4 UNIT_Y;
	/** equals to Vector4(0,0,1,0) */
	static const Vector4 UNIT_Z;
	/** equals to Vector4(0,0,0,1) */
	static const Vector4 UNIT_W;
};

typedef Vector2 vec2;
typedef Vector3 vec3;
typedef Vector4 vec4;

typedef Vector2 Point2F;
typedef Vector3 Point3F;

}

}

#endif /* POLA_GRAPHIC_VECTOR_H_ */
