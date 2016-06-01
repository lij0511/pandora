/*
 * Vector.h
 *
 *  Created on: 2015年12月4日
 *      Author: lijing
 */

#ifndef POLA_GRAPHIC_VECTOR_H_
#define POLA_GRAPHIC_VECTOR_H_

#include <math.h>

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

    float lengthSquared() const {
		return x * x + y * y;
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

    Vector3 operator/(float s) const {
        return (Vector3){x / s, y / s, z / s};
    }

    Vector3 operator*(float s) const {
        return (Vector3){x * s, y * s, z * s};
    }

    void normalize() {
    	float len2 = lengthSquared();
    	if (len2 == 0.0f || len2 == 1.0f) {
    		return;
    	}
		float s = 1.0f / sqrt(len2);
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

	Vector3 copyCross(const Vector3& vector) {
		Vector3 v = {x, y, z};
		v.cross(vector);
		return v;
	}

	float dot(const Vector3& vector) const {
		return x * vector.x + y * vector.y + z * vector.z;
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
		double RADTODEG = 180.0 / M_PIl;

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

};

typedef Vector2 vec2;
typedef Vector3 vec3;

}
}

#endif /* POLA_GRAPHIC_VECTOR_H_ */
