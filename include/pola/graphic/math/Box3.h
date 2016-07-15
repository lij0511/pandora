/*
 * Box3.h
 *
 *  Created on: 2016年7月5日
 *      Author: lijing
 */

#ifndef BOX3_H_
#define BOX3_H_

#include "pola/graphic/math/Vector.h"
#include "pola/graphic/math/Matrix4.h"

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
	void makeEmpty();

	void set(const vec3& min, const vec3& max);

	void applyMatrix(const mat4& m);

	void setFromPoints(Point2F* const points, unsigned size);
	void setFromPoints(Point3F* const points, unsigned size);

	void expandByPoint(const Point2F& point);
	void expandByPoint(const Point3F& point);

	const vec3& min() const;
	const vec3& max() const;

private:
	vec3 mMinEdge;
	vec3 mMaxEdge;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* BOX3_H_ */
