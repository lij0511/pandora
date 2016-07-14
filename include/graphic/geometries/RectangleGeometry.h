/*
 * RectangleGeometry.h
 *
 *  Created on: 2016年7月14日
 *      Author: lijing
 */

#ifndef POLA_RECTANGLEGEOMETRY_H_
#define POLA_RECTANGLEGEOMETRY_H_

#include "graphic/geometries/Geometry2D.h"

namespace pola {
namespace graphic {

class RectangleGeometry: public Geometry2D {
public:
	RectangleGeometry(float x, float y, float w, float h);
	virtual ~RectangleGeometry();
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_RECTANGLEGEOMETRY_H_ */
