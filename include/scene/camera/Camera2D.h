/*
 * Camera2D.h
 *
 *  Created on: 2016年5月25日
 *      Author: lijing
 */

#ifndef CAMERA2D_H_
#define CAMERA2D_H_

#include "scene/Camera.h"

namespace pola {
namespace scene {

/*
 *
 */
class Camera2D: public Camera {
public:
	Camera2D();
	virtual ~Camera2D();

	virtual void setSize(int32_t width, int32_t height);
private:
	void recalculateMatrix();
};

} /* namespace scene */
} /* namespace pola */

#endif /* CAMERA2D_H_ */
