/*
 * OrthoCamera.cpp
 *
 *  Created on: 2016年7月14日
 *      Author: lijing
 */

#include "scene/camera/OrthoCamera.h"

namespace pola {
namespace scene {

OrthoCamera::OrthoCamera(float near, float far) : mNear(near), mFar(far) {
}

OrthoCamera::~OrthoCamera() {
}

void OrthoCamera::setSize(int32_t width, int32_t height) {
	Camera::setSize(width, height);
	if (width > 0 && height > 0) {
		mProjection.makeOrtho(0, width, 0, height, mNear, mFar);
		onPropertyChange();
	}
}

} /* namespace scene */
} /* namespace pola */
