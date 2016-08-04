/*
 * Object3D.h
 *
 *  Created on: 2016年8月4日
 *      Author: lijing
 */

#ifndef POLA_OBJECT3D_H_
#define POLA_OBJECT3D_H_

#include "pola/graphic/math/Vector.h"
#include "pola/graphic/math/Quaternion.h"
#include "pola/graphic/math/Euler.h"
#include "pola/graphic/math/Matrix4.h"
#include "pola/graphic/math/Box3.h"

namespace pola {
namespace graphic {

/*
 *
 */
class Object3D {
public:
	Object3D();
	virtual ~Object3D();

	virtual void setPosition(const graphic::vec3& position);
	const graphic::vec3& getPosition() const;

	virtual void setRotation(const graphic::Euler& rotation);
	const graphic::Euler& getRotation() const;

	virtual void setScale(const graphic::vec3& scale);
	const graphic::vec3& getScale() const;

protected:
	graphic::vec3 mPosition;
	graphic::Euler mRotation;
	graphic::vec3 mScale;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* OBJECT3D_H_ */
