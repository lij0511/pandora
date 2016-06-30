/*
 * Matrix3.cpp
 *
 *  Created on: 2016年6月30日
 *      Author: lijing
 */

#include <stdlib.h>
#include <string.h>
#include "graphic/math/Matrix3.h"

namespace pola {
namespace scene {

Matrix3::Matrix3() {
	loadIdentity();
}

Matrix3::Matrix3(const Matrix3& v) {
	load(v);
}

Matrix3::~Matrix3() {
}

Matrix3& Matrix3::set(float n11, float n12, float n13, float n21, float n22, float n23, float n31, float n32, float n33) {
	float* te = this->data;
	te[ 0 ] = n11; te[ 1 ] = n21; te[ 2 ] = n31;
	te[ 3 ] = n12; te[ 4 ] = n22; te[ 5 ] = n32;
	te[ 6 ] = n13; te[ 7 ] = n23; te[ 8 ] = n33;
	return *this;
}

Matrix3& Matrix3::loadIdentity() {
	set(1, 0, 0, 0, 1, 0, 0, 0, 1);
	return *this;
}

Matrix3& Matrix3::load(const Matrix3& v) {
	memcpy(data, v.data, sizeof(data));
	return *this;
}

Matrix3& Matrix3::multiply(float s) {
	float* te = this->data;
	te[ 0 ] *= s; te[ 3 ] *= s; te[ 6 ] *= s;
	te[ 1 ] *= s; te[ 4 ] *= s; te[ 7 ] *= s;
	te[ 2 ] *= s; te[ 5 ] *= s; te[ 8 ] *= s;
	return *this;
}

Matrix3& Matrix3::transpose() {
	float tmp;
	float* m = this->data;
	tmp = m[ 1 ]; m[ 1 ] = m[ 3 ]; m[ 3 ] = tmp;
	tmp = m[ 2 ]; m[ 2 ] = m[ 6 ]; m[ 6 ] = tmp;
	tmp = m[ 5 ]; m[ 5 ] = m[ 7 ]; m[ 7 ] = tmp;
	return *this;
}

Matrix3& Matrix3::setFromMatrix4(float* mat4) {
	this->set(
			mat4[ 0 ], mat4[ 4 ], mat4[  8 ],
			mat4[ 1 ], mat4[ 5 ], mat4[  9 ],
			mat4[ 2 ], mat4[ 6 ], mat4[ 10 ]
		);
	return *this;
}

Matrix3& Matrix3::loadInverse(const Matrix3& v) {
	const float* me = v.data;
	float* te = this->data;

	float n11 = me[ 0 ], n21 = me[ 1 ], n31 = me[ 2 ],
		n12 = me[ 3 ], n22 = me[ 4 ], n32 = me[ 5 ],
		n13 = me[ 6 ], n23 = me[ 7 ], n33 = me[ 8 ],

		t11 = n33 * n22 - n32 * n23,
		t12 = n32 * n13 - n33 * n12,
		t13 = n23 * n12 - n22 * n13,

		det = n11 * t11 + n21 * t12 + n31 * t13;

	if (det == 0) {
		return this->loadIdentity();
	}

	te[ 0 ] = t11;
	te[ 1 ] = n31 * n23 - n33 * n21;
	te[ 2 ] = n32 * n21 - n31 * n22;

	te[ 3 ] = t12;
	te[ 4 ] = n33 * n11 - n31 * n13;
	te[ 5 ] = n31 * n12 - n32 * n11;

	te[ 6 ] = t13;
	te[ 7 ] = n21 * n13 - n23 * n11;
	te[ 8 ] = n22 * n11 - n21 * n12;

	return multiply(1 / det);
}

} /* namespace scene */
} /* namespace pola */
