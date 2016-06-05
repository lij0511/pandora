/*
 * Euler.h
 *
 *  Created on: 2016年6月5日
 *      Author: lijing
 */

#ifndef POLA_EULER_H_
#define POLA_EULER_H_

#include "graphic/math/Quaternion.h"
#include "graphic/math/Matrix4.h"
#include "utils/Math.h"

namespace pola {
namespace graphic {

struct Euler {
	enum Order {
		XYZ, YZX, ZXY, XZY, YXZ, ZYX,
	};

	float x, y, z;
	Order order;

	inline Euler(float x = 0, float y = 0, float z = 0, Order order = XYZ) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->order = order;
	}

	inline void set(float x, float y, float z, Order order) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->order = order;
	}

	inline void setFromRotationMatrix(const Matrix4& m, Order order = XYZ) {
		const float* te = m.data;
		float m11 = te[ 0 ], m12 = te[ 4 ], m13 = te[ 8 ];
		float m21 = te[ 1 ], m22 = te[ 5 ], m23 = te[ 9 ];
		float m31 = te[ 2 ], m32 = te[ 6 ], m33 = te[ 10 ];

		if (order == XYZ) {
			this->y = asin(utils::fclamp<float>(m13, -1, 1));
			if (abs(m13) < 0.99999) {
				this->x = atan2(-m23, m33);
				this->z = atan2(-m12, m11);
			} else {
				this->x = atan2(m32, m22);
				this->z = 0;
			}
		} else if (order == YXZ) {
			this->x = asin(-utils::fclamp<float>(m23, -1, 1));
			if (abs(m23) < 0.99999) {
				this->y = atan2(m13, m33);
				this->z = atan2(m21, m22);
			} else {
				this->y = atan2(-m31, m11);
				this->z = 0;
			}
		} else if (order == ZXY) {
			this->x = asin(utils::fclamp<float>(m32, -1, 1));
			if (abs(m32) < 0.99999) {
				this->y = atan2(-m31, m33);
				this->z = atan2(-m12, m22);
			} else {
				this->y = 0;
				this->z = atan2(m21, m11);
			}
		} else if (order == ZYX) {
			this->y = asin(-utils::fclamp<float>(m31, -1, 1));
			if (abs(m31) < 0.99999) {
				this->x = atan2(m32, m33);
				this->z = atan2(m21, m11);
			} else {
				this->x = 0;
				this->z = atan2(-m12, m22);
			}
		} else if (order == YZX) {
			this->z = asin(utils::fclamp<float>(m21, -1, 1));
			if (abs(m21) < 0.99999) {
				this->x = atan2(-m23, m22);
				this->y = atan2(-m31, m11);
			} else {
				this->x = 0;
				this->y = atan2(m13, m33);
			}
		} else if (order == XZY) {
			this->z = asin(-utils::fclamp<float>(m12, -1, 1));
			if (abs(m12) < 0.99999) {
				this->x = atan2(m32, m22);
				this->y = atan2(m13, m11);
			} else {
				this->x = atan2(-m23, m33);
				this->y = 0;
			}
		}
		this->order = order;
	}

	inline void setFromQuaternion(const Quaternion& quaternion, Order order = XYZ) {
		Matrix4 m;
		m.makeRotationFromQuaternion(quaternion);
		setFromRotationMatrix(m, order);
	}

	inline void getQuaternion(Quaternion& quaternion) {
		float c1 = cos(x / 2);
		float c2 = cos(y / 2);
		float c3 = cos(z / 2);
		float s1 = sin(x / 2);
		float s2 = sin(y / 2);
		float s3 = sin(z / 2);

		Order order = this->order;

		if (order == XYZ) {
			quaternion.x = s1 * c2 * c3 + c1 * s2 * s3;
			quaternion.y = c1 * s2 * c3 - s1 * c2 * s3;
			quaternion.z = c1 * c2 * s3 + s1 * s2 * c3;
			quaternion.w = c1 * c2 * c3 - s1 * s2 * s3;
		} else if (order == YXZ) {
			quaternion.x = s1 * c2 * c3 + c1 * s2 * s3;
			quaternion.y = c1 * s2 * c3 - s1 * c2 * s3;
			quaternion.z = c1 * c2 * s3 - s1 * s2 * c3;
			quaternion.w = c1 * c2 * c3 + s1 * s2 * s3;
		} else if (order == ZXY) {
			quaternion.x = s1 * c2 * c3 - c1 * s2 * s3;
			quaternion.y = c1 * s2 * c3 + s1 * c2 * s3;
			quaternion.z = c1 * c2 * s3 + s1 * s2 * c3;
			quaternion.w = c1 * c2 * c3 - s1 * s2 * s3;
		} else if (order == ZYX) {
			quaternion.x = s1 * c2 * c3 - c1 * s2 * s3;
			quaternion.y = c1 * s2 * c3 + s1 * c2 * s3;
			quaternion.z = c1 * c2 * s3 - s1 * s2 * c3;
			quaternion.w = c1 * c2 * c3 + s1 * s2 * s3;
		} else if (order == YZX) {
			quaternion.x = s1 * c2 * c3 + c1 * s2 * s3;
			quaternion.y = c1 * s2 * c3 + s1 * c2 * s3;
			quaternion.z = c1 * c2 * s3 - s1 * s2 * c3;
			quaternion.w = c1 * c2 * c3 - s1 * s2 * s3;
		} else if (order == XZY) {
			quaternion.x = s1 * c2 * c3 - c1 * s2 * s3;
			quaternion.y = c1 * s2 * c3 - s1 * c2 * s3;
			quaternion.z = c1 * c2 * s3 + s1 * s2 * c3;
			quaternion.w = c1 * c2 * c3 + s1 * s2 * s3;
		}
	}
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_EULER_H_ */
