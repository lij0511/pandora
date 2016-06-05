
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "graphic/math/Matrix4.h"

namespace pola {
namespace graphic {

///////////////////////////////////////////////////////////////////////////////
// Matrix
///////////////////////////////////////////////////////////////////////////////

const Matrix4& Matrix4::identity() {
    static Matrix4 sIdentity;
    return sIdentity;
}

void Matrix4::loadIdentity() {
    data[0]       = 1.0f;
    data[1]        = 0.0f;
    data[2]             = 0.0f;
    data[3] = 0.0f;

    data[4]        = 0.0f;
    data[5]       = 1.0f;
    data[6]             = 0.0f;
    data[7] = 0.0f;

    data[8]             = 0.0f;
    data[9]             = 0.0f;
    data[10]       = 1.0f;
    data[11]            = 0.0f;

    data[12]   = 0.0f;
    data[13]   = 0.0f;
    data[14]   = 0.0f;
    data[15] = 1.0f;

}

bool Matrix4::isIdentity() const {
	if (data[12] != 0 || data[13] != 0 || data[14] != 0 || data[15] != 1)
		return false;
	if (data[0] != 1 || data[1] != 0 || data[2] != 0 || data[3] != 0)
		return false;
	if (data[4] != 0 || data[5] != 1 || data[6] != 0 || data[7] != 0)
		return false;
	if (data[8] != 0 || data[9] != 0 || data[10] != 1 || data[11] != 0)
		return false;
	return true;
}

void Matrix4::load(const float* v) {
    memcpy(data, v, sizeof(data));
}

void Matrix4::load(const Matrix4& v) {
    memcpy(data, v.data, sizeof(data));
}

void Matrix4::loadInverse(const Matrix4& v) {
    double scale = 1.0 /
            (v.data[0] * ((double) v.data[5]  * v.data[15] -
                    (double) v.data[13] * v.data[7]) +
             v.data[4] * ((double) v.data[13] * v.data[3] -
                     (double) v.data[1] * v.data[15]) +
             v.data[12] * ((double) v.data[1] * v.data[7] -
                     (double) v.data[5] * v.data[3]));

    data[0] = (v.data[5] * v.data[15] -
            v.data[13] * v.data[7])  * scale;
    data[4] = (v.data[12] * v.data[7] -
            v.data[4]  * v.data[15]) * scale;
    data[12] = (v.data[4] * v.data[13] -
            v.data[12] * v.data[5])  * scale;

    data[1] = (v.data[13] * v.data[3] -
            v.data[1]  * v.data[15]) * scale;
    data[5] = (v.data[0] * v.data[15] -
            v.data[12] * v.data[3])  * scale;
    data[13] = (v.data[12] * v.data[1] -
            v.data[0]  * v.data[13]) * scale;

    data[3] = (v.data[1] * v.data[7] -
            v.data[5] * v.data[3]) * scale;
    data[7] = (v.data[4] * v.data[3] -
            v.data[0] * v.data[7]) * scale;
    data[15] = (v.data[0] * v.data[5] -
            v.data[4] * v.data[1]) * scale;
}

void Matrix4::copyTo(float* v) const {
    memcpy(v, data, sizeof(data));
}

float Matrix4::getTranslateX() const {
    return data[12];
}

float Matrix4::getTranslateY() const {
    return data[13];
}

void Matrix4::multiply(float v) {
    for (int i = 0; i < 16; i++) {
        data[i] *= v;
    }
}

void Matrix4::loadTranslate(float x, float y, float z) {
    loadIdentity();

    data[12] = x;
    data[13] = y;
    data[14] = z;

}

void Matrix4::loadScale(float sx, float sy, float sz) {
    loadIdentity();

    data[0] = sx;
    data[5] = sy;
    data[10] = sz;

}

void Matrix4::loadSkew(float sx, float sy) {
    loadIdentity();

    data[0]       = 1.0f;
    data[4]        = sx;
    data[12]   = 0.0f;

    data[1]        = sy;
    data[5]       = 1.0f;
    data[13]   = 0.0f;

    data[3] = 0.0f;
    data[7] = 0.0f;
    data[15] = 1.0f;

}

void Matrix4::loadRotate(float angle) {
    angle *= float(M_PI / 180.0f);
    float c = cosf(angle);
    float s = sinf(angle);

    loadIdentity();

    data[0]     = c;
    data[4]      = -s;

    data[1]      = s;
    data[5]     = c;
}

void Matrix4::loadRotate(float angle, float x, float y, float z) {
    data[3]  = 0.0f;
    data[7]  = 0.0f;
    data[11]             = 0.0f;
    data[12]    = 0.0f;
    data[13]    = 0.0f;
    data[14]    = 0.0f;
    data[15]  = 1.0f;

    angle *= float(M_PI / 180.0f);
    float c = cosf(angle);
    float s = sinf(angle);

    const float length = sqrtf(x * x + y * y + z * z);
    float recipLen = 1.0f / length;
    x *= recipLen;
    y *= recipLen;
    z *= recipLen;

    const float nc = 1.0f - c;
    const float xy = x * y;
    const float yz = y * z;
    const float zx = z * x;
    const float xs = x * s;
    const float ys = y * s;
    const float zs = z * s;

    data[0] = x * x * nc +  c;
    data[4]  =    xy * nc - zs;
    data[8]       =    zx * nc + ys;
    data[1]  =    xy * nc + zs;
    data[5] = y * y * nc +  c;
    data[9]       =    yz * nc - xs;
    data[2]       =    zx * nc - ys;
    data[6]       =    yz * nc + xs;
    data[10] = z * z * nc +  c;

}

void Matrix4::loadMultiply(const Matrix4& u, const Matrix4& v) {
    for (int i = 0 ; i < 4 ; i++) {
        float x = 0;
        float y = 0;
        float z = 0;
        float w = 0;

        for (int j = 0 ; j < 4 ; j++) {
            const float e = v.get(i, j);
            x += u.get(j, 0) * e;
            y += u.get(j, 1) * e;
            z += u.get(j, 2) * e;
            w += u.get(j, 3) * e;
        }

        set(i, 0, x);
        set(i, 1, y);
        set(i, 2, z);
        set(i, 3, w);
    }

}

void Matrix4::loadOrtho(float left, float right, float bottom, float top, float near, float far) {
    loadIdentity();

    data[0] = 2.0f / (right - left);
    data[5] = 2.0f / (top - bottom);
    data[10] = -2.0f / (far - near);
    data[12] = -(right + left) / (right - left);
    data[13] = -(top + bottom) / (top - bottom);
    data[14] = -(far + near) / (far - near);

}

void Matrix4::loadLookAt(const vec3& position, const vec3& target, const vec3& upper) {
	loadIdentity();
	/*vec3 zaxis = position - target;
	zaxis.normalize();

	vec3 xaxis = upper.copyCross(zaxis);
	xaxis.normalize();

	vec3 yaxis = zaxis.copyCross(xaxis);
//	yaxis.normalize();

	memset(data, 0, sizeof(float) * 16);

	data[0] = xaxis.x;
	data[1] = yaxis.x;
	data[2] = zaxis.x;

	data[4] = xaxis.y;
	data[5] = yaxis.y;
	data[6] = - zaxis.y;

	data[8] = xaxis.z;
	data[9] = yaxis.z;
	data[10] = zaxis.z;

	data[12] = - xaxis.dot(position);
	data[13] = - yaxis.dot(position);
	data[14] = - zaxis.dot(position);

	data[15] = 1;*/

	vec3 zaxis = target - position;
	zaxis.normalize();

	vec3 xaxis = zaxis.copyCross(upper);
	xaxis.normalize();

	vec3 yaxis = xaxis.copyCross(zaxis);
//	yaxis.normalize();

	data[0] = xaxis.x;
	data[1] = yaxis.x;
	data[2] = - zaxis.x;

	data[4] = xaxis.y;
	data[5] = yaxis.y;
	data[6] = - zaxis.y;

	data[8] = xaxis.z;
	data[9] = yaxis.z;
	data[10] = - zaxis.z;

	data[15] = 1;

	data[12] = position.dot(xaxis);
	data[13] = position.dot(yaxis);
	data[14] = position.dot(zaxis);
//	data[12] = position.x;
//	data[13] = position.y;
//	data[14] = position.z;
//	translate(- position.x, - position.y, - position.z);
}

void Matrix4::loadLookAtLH(vec3& position, vec3& target, vec3& upper) {
	loadIdentity();

	vec3 zaxis = position - target;
	zaxis.normalize();

	vec3 xaxis = upper.copyCross(zaxis);
	xaxis.normalize();

	vec3 yaxis = zaxis.copyCross(xaxis);
//	yaxis.normalize();

	data[0] = xaxis.x;
	data[1] = yaxis.x;
	data[2] = zaxis.x;
	data[3] = 0;

	data[4] = xaxis.y;
	data[5] = yaxis.y;
	data[6] = zaxis.y;
	data[7] = 0;

	data[8] = xaxis.z;
	data[9] = yaxis.z;
	data[10] = zaxis.z;
	data[11] = 0;

	data[12] = - xaxis.dot(position);
	data[13] = - yaxis.dot(position);
	data[14] = - zaxis.dot(position);
	data[15] = 1;

}

float Matrix4::mapZ(const Vector3& orig) const {
    // duplicates logic for mapPoint3d's z coordinate
    return orig.x * data[2] + orig.y * data[6] + orig.z * data[10] + data[14];
}

void Matrix4::mapPoint3d(Vector3& vec) const {
    const Vector3 orig(vec);
    vec.x = orig.x * data[0] + orig.y * data[4] + orig.z * data[8] + data[12];
    vec.y = orig.x * data[1] + orig.y * data[5] + orig.z * data[9] + data[13];
    vec.z = orig.x * data[2] + orig.y * data[6] + orig.z * data[10] + data[14];
}

#define MUL_ADD_STORE(a, b, c) a = (a) * (b) + (c)

void Matrix4::mapPoint(float& x, float& y) const {
    float dx = x * data[0] + y * data[4] + data[12];
    float dy = x * data[1] + y * data[5] + data[13];
    float dz = x * data[3] + y * data[7] + data[15];
    if (dz) dz = 1.0f / dz;

    x = dx * dz;
    y = dy * dz;
}

void Matrix4::setRotationRadians(const Vector3& rotation) {
	const double cr = cos(rotation.x);
	const double sr = sin(rotation.x);
	const double cp = cos(rotation.y);
	const double sp = sin(rotation.y);
	const double cy = cos(rotation.z);
	const double sy = sin(rotation.z);

	data[0] = (cp * cy);
	data[1] = (cp * sy);
	data[2] = (-sp);

	const double srsp = sr * sp;
	const double crsp = cr * sp;

	data[4] = (srsp * cy - cr * sy);
	data[5] = (srsp * sy + cr * cy);
	data[6] = (sr * cp);

	data[8] = (crsp * cy + sr * sy);
	data[9] = (crsp * sy - sr * cy);
	data[10] = (cr * cp);
}

void Matrix4::setRotationDegrees(const Vector3& degrees) {
	setRotationRadians(degrees * M_PI / 180.0f);
}

void Matrix4::transformVector(Vector3& vec) {
	Vector3 in = vec;
	transformVector(in, vec);
}

void Matrix4::transformVector(const Vector3& in, Vector3& out) {
	out.x = in.x*data[0] + in.y*data[4] + in.z*data[8] + data[12];
	out.y = in.x*data[1] + in.y*data[5] + in.z*data[9] + data[13];
	out.z = in.x*data[2] + in.y*data[6] + in.z*data[10] + data[14];
}

void Matrix4::setPosition(const Vector3& position) {
	data[12] = position.x;
	data[13] = position.y;
	data[14] = position.z;
}

void Matrix4::setScale(const Vector3& scale) {
	float* te = data;
	float x = scale.x, y = scale.y, z = scale.z;
	te[ 0 ] *= x; te[ 4 ] *= y; te[ 8 ] *= z;
	te[ 1 ] *= x; te[ 5 ] *= y; te[ 9 ] *= z;
	te[ 2 ] *= x; te[ 6 ] *= y; te[ 10 ] *= z;
	te[ 3 ] *= x; te[ 7 ] *= y; te[ 11 ] *= z;
}

void Matrix4::makeRotationFromQuaternion(const Quaternion& quaternion) {
	float* te = data;

	float x = quaternion.x, y = quaternion.y, z = quaternion.z, w = quaternion.w;
	float x2 = x + x, y2 = y + y, z2 = z + z;
	float xx = x * x2, xy = x * y2, xz = x * z2;
	float yy = y * y2, yz = y * z2, zz = z * z2;
	float wx = w * x2, wy = w * y2, wz = w * z2;

	te[ 0 ] = 1 - ( yy + zz );
	te[ 4 ] = xy - wz;
	te[ 8 ] = xz + wy;

	te[ 1 ] = xy + wz;
	te[ 5 ] = 1 - ( xx + zz );
	te[ 9 ] = yz - wx;

	te[ 2 ] = xz - wy;
	te[ 6 ] = yz + wx;
	te[ 10 ] = 1 - ( xx + yy );

	// last column
	te[ 3 ] = 0;
	te[ 7 ] = 0;
	te[ 11 ] = 0;

	// bottom row
	te[ 12 ] = 0;
	te[ 13 ] = 0;
	te[ 14 ] = 0;
	te[ 15 ] = 1;
}

void Matrix4::compose(const Vector3& position, const Quaternion& quaternion, const Vector3& scale) {
	this->makeRotationFromQuaternion(quaternion);
	this->setScale(scale);
	this->setPosition(position);
}

void Matrix4::decompose(Vector3& position, Quaternion& quaternion, Vector3& scale) {
	float* te = data;
	float sx = Vector3( te[ 0 ], te[ 1 ], te[ 2 ] ).length();
	float sy = Vector3( te[ 4 ], te[ 5 ], te[ 6 ] ).length();
	float sz = Vector3( te[ 8 ], te[ 9 ], te[ 10 ] ).length();

	// if determine is negative, we need to invert one scale
	float det = determinant();
	if ( det < 0 ) {
		sx = - sx;
	}
	position.x = te[ 12 ];
	position.y = te[ 13 ];
	position.z = te[ 14 ];

	Matrix4 matrix(*this);
	float invSX = 1 / sx;
	float invSY = 1 / sy;
	float invSZ = 1 / sz;

	matrix.data[ 0 ] *= invSX;
	matrix.data[ 1 ] *= invSX;
	matrix.data[ 2 ] *= invSX;

	matrix.data[ 4 ] *= invSY;
	matrix.data[ 5 ] *= invSY;
	matrix.data[ 6 ] *= invSY;

	matrix.data[ 8 ] *= invSZ;
	matrix.data[ 9 ] *= invSZ;
	matrix.data[ 10 ] *= invSZ;
	matrix.getRotation(quaternion);

	scale.x = sx;
	scale.y = sy;
	scale.z = sz;
}

void Matrix4::getRotation(Quaternion& rotaion) {
	float* te = data;
	float m11 = te[ 0 ], m12 = te[ 4 ], m13 = te[ 8 ],
	m21 = te[ 1 ], m22 = te[ 5 ], m23 = te[ 9 ],
	m31 = te[ 2 ], m32 = te[ 6 ], m33 = te[ 10 ],
	trace = m11 + m22 + m33,
	s;

	if ( trace > 0 ) {
		s = 0.5 / sqrt( trace + 1.0 );
		rotaion.w = 0.25 / s;
		rotaion.x = ( m32 - m23 ) * s;
		rotaion.y = ( m13 - m31 ) * s;
		rotaion.z = ( m21 - m12 ) * s;
	} else if ( m11 > m22 && m11 > m33 ) {
		s = 2.0 * sqrt( 1.0 + m11 - m22 - m33 );
		rotaion.w = ( m32 - m23 ) / s;
		rotaion.x = 0.25 * s;
		rotaion.y = ( m12 + m21 ) / s;
		rotaion.z = ( m13 + m31 ) / s;
	} else if ( m22 > m33 ) {
		s = 2.0 * sqrt( 1.0 + m22 - m11 - m33 );
		rotaion.w = ( m13 - m31 ) / s;
		rotaion.x = ( m12 + m21 ) / s;
		rotaion.y = 0.25 * s;
		rotaion.z = ( m23 + m32 ) / s;
	} else {
		s = 2.0 * sqrt( 1.0 + m33 - m11 - m22 );
		rotaion.w = ( m21 - m12 ) / s;
		rotaion.x = ( m13 + m31 ) / s;
		rotaion.y = ( m23 + m32 ) / s;
		rotaion.z = 0.25 * s;
	}
}

void Matrix4::makeFrustum(float left, float right, float bottom, float top,
        float near, float far) {
	float* te = data;
	float x = 2 * near / ( right - left );
	float y = 2 * near / ( top - bottom );

	float a = ( right + left ) / ( right - left );
	float b = ( top + bottom ) / ( top - bottom );
	float c = - ( far + near ) / ( far - near );
	float d = - 2 * far * near / ( far - near );

	te[ 0 ] = x;	te[ 4 ] = 0;	te[ 8 ] = a;	te[ 12 ] = 0;
	te[ 1 ] = 0;	te[ 5 ] = y;	te[ 9 ] = b;	te[ 13 ] = 0;
	te[ 2 ] = 0;	te[ 6 ] = 0;	te[ 10 ] = c;	te[ 14 ] = d;
	te[ 3 ] = 0;	te[ 7 ] = 0;	te[ 11 ] = - 1;	te[ 15 ] = 0;
}

void Matrix4::makePerspective(float fovy, float aspect, float near, float far) {
	float ymax = near * tan(fovy * 0.5);
	float ymin = - ymax;
	float xmin = ymin * aspect;
	float xmax = ymax * aspect;

	makeFrustum( xmin, xmax, ymin, ymax, near, far );
}

void Matrix4::lookAt(const vec3& eye, const vec3& target, const vec3& upper) {
	loadIdentity();

	vec3 zaxis = eye - target;
	zaxis.normalize();
	if (zaxis.lengthSquared() == 0) {
		zaxis.z = 1;
	}

	vec3 xaxis = upper.copyCross(zaxis);
	xaxis.normalize();
	if ( xaxis.lengthSquared() == 0 ) {
		zaxis.x += 0.0001;
		xaxis = upper.copyCross(zaxis);
		xaxis.normalize();
	}

	vec3 yaxis = zaxis.copyCross(xaxis);
//	yaxis.normalize();

	data[0] = xaxis.x;
	data[1] = xaxis.y;
	data[2] = xaxis.z;

	data[4] = yaxis.x;
	data[5] = yaxis.y;
	data[6] = yaxis.z;

	data[8] = zaxis.x;
	data[9] = zaxis.y;
	data[10] = zaxis.z;

	data[12] = xaxis.dot(eye);
	data[13] = yaxis.dot(eye);
	data[14] = zaxis.dot(eye);
}

float Matrix4::determinant() {
	float* te = data;
	float n11 = te[ 0 ], n12 = te[ 4 ], n13 = te[ 8 ], n14 = te[ 12 ];
	float n21 = te[ 1 ], n22 = te[ 5 ], n23 = te[ 9 ], n24 = te[ 13 ];
	float n31 = te[ 2 ], n32 = te[ 6 ], n33 = te[ 10 ], n34 = te[ 14 ];
	float n41 = te[ 3 ], n42 = te[ 7 ], n43 = te[ 11 ], n44 = te[ 15 ];
	return (
			n41 * (
				+ n14 * n23 * n32
				 - n13 * n24 * n32
				 - n14 * n22 * n33
				 + n12 * n24 * n33
				 + n13 * n22 * n34
				 - n12 * n23 * n34
			) +
			n42 * (
				+ n11 * n23 * n34
				 - n11 * n24 * n33
				 + n14 * n21 * n33
				 - n13 * n21 * n34
				 + n13 * n24 * n31
				 - n14 * n23 * n31
			) +
			n43 * (
				+ n11 * n24 * n32
				 - n11 * n22 * n34
				 - n14 * n21 * n32
				 + n12 * n21 * n34
				 + n14 * n22 * n31
				 - n12 * n24 * n31
			) +
			n44 * (
				- n13 * n22 * n31
				 - n11 * n23 * n32
				 + n11 * n22 * n33
				 + n13 * n21 * n32
				 - n12 * n21 * n33
				 + n12 * n23 * n31
			)

		);
}
}
};
