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
	mDirty = true;
}

PerspectiveCamera::~PerspectiveCamera() {
}

void PerspectiveCamera::setSize(int32_t width, int32_t height) {
	Camera::setSize(width, height);
	if (width > 0 && height > 0) {
		mAspect = (float) width / height;
		mProjection.makePerspective(mFovy, mAspect, mZnear, mZfar);
		mDirty = true;
	}
}

void PerspectiveCamera::recalculateMatrix() {
//	mView.lookAt(mPosition, mTarget, mUpper);
	graphic::quat4 q;
//	mView.setPosition(mPosition);
	graphic::mat4 m;
	mView.compose(mPosition, q, graphic::vec3(1, 1, 1));
	m.compose(graphic::vec3(0, 0, 0), q, graphic::vec3(1, 1, 1));
	graphic::mat4 m1;
//	m1.loadMultiply(m, mView);
	m1.load(mView);
//	m.loadInverse(mView);
//	m.load(mView);
	mMatrix.loadMultiply(mProjection, m1);
}

} /* namespace scene */
} /* namespace pola */
