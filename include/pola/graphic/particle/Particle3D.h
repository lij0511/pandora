/*
 * Particle3D.h
 *
 *  Created on: 2016年7月25日
 *      Author: lijing
 */

#ifndef POLA_PARTICLE3D_H_
#define POLA_PARTICLE3D_H_

#include "pola/graphic/math/Vector.h"
#include "pola/graphic/math/Quaternion.h"
#include "pola/graphic/Color.h"

namespace pola {
namespace graphic {

/*
 *
 */
struct Particle3D {
public:
	virtual ~Particle3D() {};

	vec3 position;
	quat4 orientation;
	FColor4 color;
	vec2 uv_lb;
	vec2 uv_tr;

	float width;
	float height;
	float depth;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_PARTICLE3D_H_ */
