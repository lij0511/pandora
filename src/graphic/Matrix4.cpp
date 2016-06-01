
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "graphic/Matrix4.h"

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

void Matrix4::loadPerspective(float fovy, float aspect, float near, float far) {
	loadIdentity();

	const double h = 1.0 / (tan(fovy*0.5));
	const float w = (h / aspect);

	data[0] = w;
	data[1] = 0;
	data[2] = 0;
	data[3] = 0;

	data[4] = 0;
	data[5] = h;
	data[6] = 0;
	data[7] = 0;

	data[8] = 0;
	data[9] = 0;
	data[10] = ((far + near) / (near - far));
	data[11] = - 1;

	data[12] = 0;
	data[13] = 0;
	data[14] = 2 * near * far / (near - far);
	data[15] = 0;

}

void Matrix4::loadPerspectiveLH(float fovy, float aspect, float near, float far) {
	loadIdentity();

	const double h = 1.0 / (tan(fovy*0.5));
	const float w = h / aspect;

	data[0] = w;
	data[1] = 0;
	data[2] = 0;
	data[3] = 0;

	data[4] = 0;
	data[5] = h;
	data[6] = 0;
	data[7] = 0;

	data[8] = 0;
	data[9] = 0;
	data[10] = (far / (far - near));
	data[11] = 1;

	data[12] = 0;
	data[13] = 0;
	data[14] = - near*far / (far - near);
	data[15] = 0;

}

void Matrix4::loadFrustum(float left, float right, float bottom, float top,
        float near, float far) {
	const float r_width  = 1.0f / (right - left);
	const float r_height = 1.0f / (top - bottom);
	const float r_depth  = 1.0f / (near - far);
	const float x = 2.0f * (near * r_width);
	const float y = 2.0f * (near * r_height);
	const float A = (right + left) * r_width;
	const float B = (top + bottom) * r_height;
	const float C = (far + near) * r_depth;
	const float D = 2.0f * (far * near * r_depth);
	data[0] = x;
	data[5] = y;
	data[8] = A;
	data[ 9] = B;
	data[10] = C;
	data[14] = D;
	data[11] = -1.0f;
	data[ 1] = 0.0f;
	data[ 2] = 0.0f;
	data[ 3] = 0.0f;
	data[ 4] = 0.0f;
	data[ 6] = 0.0f;
	data[ 7] = 0.0f;
	data[12] = 0.0f;
	data[13] = 0.0f;
	data[15] = 0.0f;

}

void Matrix4::loadLookAt(vec3& position, vec3& target, vec3& upper) {
	loadIdentity();

	vec3 nvec = target - position;
	nvec.normalize();

	vec3 uvec = nvec.copyCross(upper);
	uvec.normalize();

	vec3 vvec = uvec.copyCross(nvec);
	vvec.normalize();

	memset(data, 0, sizeof(float) * 16);

	data[0] = uvec.x;
	data[4] = uvec.y;
	data[8] = uvec.z;
//	data[12] = - position.dot(uvec);

	data[1] = vvec.x;
	data[5] = vvec.y;
	data[9] = vvec.z;
//	data[13] = - position.dot(vvec);

	data[2] = - nvec.x;
	data[6] = - nvec.y;
	data[10] = - nvec.z;
//	data[14] = - position.dot(nvec);

	data[15] = 1;

	translate(- position.x, - position.y, - position.z);
}

void Matrix4::loadLookAtLH(vec3& position, vec3& target, vec3& upper) {
	loadIdentity();

	vec3 zaxis = target - position;
	zaxis.normalize();

	vec3 xaxis = upper.copyCross(zaxis);
	xaxis.normalize();

	vec3 yaxis = zaxis.copyCross(xaxis);
	yaxis.normalize();

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

void Matrix4::decomposeScale(float& sx, float& sy) const {
    float len;
    len = data[0] * data[0] + data[4] * data[4];
    sx = copysignf(sqrtf(len), data[0]);
    len = data[5] * data[5] + data[1] * data[1];
    sy = copysignf(sqrtf(len), data[5]);
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

}
};
