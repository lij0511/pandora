/*
 * SphereGeometry.h
 *
 *  Created on: 2016年7月7日
 *      Author: lijing
 */

#ifndef POLA_SPHEREGEOMETRY_H_
#define POLA_SPHEREGEOMETRY_H_

#include "pola/graphic/geometries/Geometry3D.h"

namespace pola {
namespace graphic {

/*
 *
 */
class SphereGeometry: public Geometry3D {
public:
	SphereGeometry(float radius, uint32_t widthSegments, uint32_t heightSegments, float phiStart = 0, float phiLength = M_PI * 2, float thetaStart = 0, float thetaLength = M_PI);
	virtual ~SphereGeometry();
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_SPHEREGEOMETRY_H_ */
