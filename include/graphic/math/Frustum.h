/*
 * Frustum.h
 *
 *  Created on: 2016年7月5日
 *      Author: lijing
 */

#ifndef FRUSTUM_H_
#define FRUSTUM_H_

#include "graphic/math/Plane3.h"
#include "graphic/math/Matrix4.h"

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

private:
	Plane3 planes[6];
};

} /* namespace graphic */
} /* namespace pola */

#endif /* FRUSTUM_H_ */
