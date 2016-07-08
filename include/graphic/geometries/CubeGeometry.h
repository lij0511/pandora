/*
 * CubeGeometry.h
 *
 *  Created on: 2016年7月8日
 *      Author: lijing
 */

#ifndef POLA_CUBEGEOMETRY_H_
#define POLA_CUBEGEOMETRY_H_

#include "graphic/Geometry.h"

namespace pola {
namespace graphic {

/*
 *
 */
class CubeGeometry : public Geometry {
public:
	CubeGeometry(float w, float h, float d);
	virtual ~CubeGeometry();
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_CUBEGEOMETRY_H_ */
