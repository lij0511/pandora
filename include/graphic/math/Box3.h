/*
 * Box3.h
 *
 *  Created on: 2016年7月5日
 *      Author: lijing
 */

#ifndef BOX3_H_
#define BOX3_H_

#include "graphic/math/Vector.h"

namespace pola {
namespace graphic {

/*
 *
 */
class Box3 {
public:
	Box3();
	virtual ~Box3();

	bool isEmpty() const;

	void set(const vec3& min, const vec3& max);

	void setFromPoints(vec3* const points, unsigned size);

private:
	vec3 mMinEdge;
	vec3 mMaxEdge;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* BOX3_H_ */
