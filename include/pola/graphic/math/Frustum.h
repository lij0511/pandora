/*
 * Frustum.h
 *
 *  Created on: 2016年7月5日
 *      Author: lijing
 */

#ifndef POLA_FRUSTUM_H_
#define POLA_FRUSTUM_H_

#include "pola/graphic/math/Plane3.h"
#include "pola/graphic/math/Matrix4.h"
#include "pola/graphic/math/Box3.h"

namespace pola {
namespace graphic {

/*
 *
 */
class Frustum {
public:
	Frustum();
	virtual ~Frustum();

	void setFromMatrix(const mat4& m);

	bool intersectsBox(const Box3& boundingBox) const;

private:
	Plane3 planes[6];
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_FRUSTUM_H_ */
