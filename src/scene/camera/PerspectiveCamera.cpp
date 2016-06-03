/*
 * Camera3D.cpp
 *
 *  Created on: 2016年5月25日
 *      Author: lijing
 */

#include "scene/camera/PerspectiveCamera.h"

namespace pola {
namespace scene {

PerspectiveCamera::PerspectiveCamera(const graphic::vec3& pos, const graphic::vec3& lookAt) :
		Camera(pos), mTarget(lookAt), mUpper(0.0f, 1.0f, 0.0f), mZnear(
				0.1f), mZfar(3000.0f) {
	mFovy = M_PI / 2.5f;
	mAspect = 1.0f;
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
//		const double DEG2RAD = 3.1415926 / 180;
//		double tangent = tan(m_fovy / 2 * DEG2RAD);
//		double h = m_znear * tangent;
//		double w = height * m_aspect;
//		m_projection.loadFrustum(- w, w, -h, h, m_znear, m_zfar);
//		m_projection.loadFrustum(-width, width, -height, height, m_znear, m_zfar);
		mDirty = true;
	}
}

void PerspectiveCamera::setTarget(const graphic::vec3& target) {
	mTarget = target;
	mDirty = true;
}

void PerspectiveCamera::setUpper(const graphic::vec3& upper) {
	mUpper = upper;
	mDirty = true;
}

void PerspectiveCamera::recalculateMatrix() {
	mView.loadLookAt(mPosition, mTarget, mUpper);
//	mView.setPosition(mPosition);
//	mView.setPosition(mPosition);
	graphic::mat4 m;
//	m.loadInverse(mView);
	m.load(mView);
	mMatrix.loadMultiply(mProjection, m);
}

} /* namespace scene */
} /* namespace pola */
