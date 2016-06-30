/*
 * Matrix3.h
 *
 *  Created on: 2016年6月30日
 *      Author: lijing
 */

#ifndef MATRIX3_H_
#define MATRIX3_H_

namespace pola {
namespace scene {

/*
 *
 */
class Matrix3 {
public:
	float data[9];

	Matrix3();
	Matrix3(const Matrix3& v);
	virtual ~Matrix3();

	Matrix3& set(float n11, float n12, float n13, float n21, float n22, float n23, float n31, float n32, float n33);

	Matrix3& loadIdentity();

	Matrix3& load(const Matrix3& v);

	Matrix3& multiply(float s);

	Matrix3& transpose();

	Matrix3& setFromMatrix4(float* mat4);

	Matrix3& loadInverse(const Matrix3& v);

	float operator[](int index) const {
		return data[index];
	}

	float& operator[](int index) {
		return data[index];
	}
};

typedef Matrix3 mat3;

} /* namespace scene */
} /* namespace pola */

#endif /* MATRIX3_H_ */
