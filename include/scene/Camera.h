/*
 * Camera.h
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#ifndef POLA_CAMERA_H_
#define POLA_CAMERA_H_

#include "graphic/Matrix4.h"
#include "graphic/Vector.h"
#include "input/KeyEvent.h"

namespace pola {
namespace scene {

class Camera {
public:
	Camera();
	virtual ~Camera();

	virtual void setSize(int32_t width, int32_t height);

	const graphic::mat4& matrix() const;

	virtual bool dispatchKeyEvent(input::KeyEvent& keyEvent);
protected:
	graphic::mat4 m_matrix;
	int32_t m_width;
	int32_t m_height;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_CAMERA_H_ */
