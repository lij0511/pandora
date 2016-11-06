/*
 * Vector.cpp
 *
 *  Created on: 2016年5月18日
 *      Author: lijing
 */

#include "pola/graphic/math/Vector.h"

namespace pola {
namespace graphic {

const Vector2 Vector2::ZERO(0.0f, 0.0f);
const Vector2 Vector2::ONE(1.0f, 1.0f);
const Vector2 Vector2::UNIT_X(1.0f, 0.0f);
const Vector2 Vector2::UNIT_Y(0.0f, 1.0f);
const Vector2 Vector2::ANCHOR_MIDDLE(0.5f, 0.5f);
const Vector2 Vector2::ANCHOR_BOTTOM_LEFT(0.0f, 0.0f);
const Vector2 Vector2::ANCHOR_TOP_LEFT(0.0f, 1.0f);
const Vector2 Vector2::ANCHOR_BOTTOM_RIGHT(1.0f, 0.0f);
const Vector2 Vector2::ANCHOR_TOP_RIGHT(1.0f, 1.0f);
const Vector2 Vector2::ANCHOR_MIDDLE_RIGHT(1.0f, 0.5f);
const Vector2 Vector2::ANCHOR_MIDDLE_LEFT(0.0f, 0.5f);
const Vector2 Vector2::ANCHOR_MIDDLE_TOP(0.5f, 1.0f);
const Vector2 Vector2::ANCHOR_MIDDLE_BOTTOM(0.5f, 0.0f);

const Vector3 Vector3::ZERO(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::ONE(1.0f, 1.0f, 1.0f);
const Vector3 Vector3::UNIT_X(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UNIT_Y(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::UNIT_Z(0.0f, 0.0f, 1.0f);

const Vector4 Vector4::ZERO = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::ONE = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
const Vector4 Vector4::UNIT_X = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::UNIT_Y = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
const Vector4 Vector4::UNIT_Z = Vector4(0.0f, 0.0f, 1.0f, 0.0f);
const Vector4 Vector4::UNIT_W = Vector4(0.0f, 0.0f, 0.0f, 1.0f);

}
}
