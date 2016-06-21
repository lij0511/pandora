/*
 * Camera3D.cpp
 *
 *  Created on: 2016年5月25日
 *      Author: lijing
 */

#include "scene/camera/PerspectiveCamera.h"

namespace pola {
namespace scene {

PerspectiveCamera::PerspectiveCamera(float fovy, float aspect, float near, float far) :
		mFovy(fovy), mAspect(aspect), mZnear(near), mZfar(far) {
	mProjection.makePerspective(mFovy, mAspect, mZnear, mZfar);
}

PerspectiveCamera::~PerspectiveCamera() {
}

void PerspectiveCamera::setSize(int32_t width, int32_t height) {
	Camera::setSize(width, height);
	if (width > 0 && height > 0) {
		mAspect = (float) width / height;
		mProjection.makePerspective(mFovy, mAspect, mZnear, mZfar);
		onPropertyChange();
	}
}

} /* namespace scene */
} /* namespace pola */
