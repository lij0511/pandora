/*
 * Mesh.cpp
 *
 *  Created on: 2016年8月19日
 *      Author: lijing
 */

#include "pola/scene/mesh/Mesh.h"

namespace pola {
namespace scene {

Mesh::Mesh() : mGeometry(new graphic::Geometry3D), mSkeleton(nullptr) {
}

Mesh::Mesh(graphic::Geometry3D* geometry) : mGeometry(geometry), mSkeleton(nullptr) {
}

Mesh::~Mesh() {
}

graphic::Geometry* Mesh::geometry() {
	return mGeometry.get();
}

void Mesh::setAnimations(Animations* animations) {
	mAnimations = animations;
}

Animations* Mesh::getAnimations() const {
	return mAnimations.get();
}

bool Mesh::hasAnimation() const {
	return mAnimations != nullptr && mAnimations->getAnimationCount() > 0;
}

Mesh* Mesh::clone() {
	Mesh* mesh = new Mesh(nullptr);
	if (mGeometry != nullptr) {
		mesh->mGeometry = mGeometry->clone();
	}
	mesh->mAnimations = mAnimations;
	mesh->mMaterialId = mMaterialId;
	mesh->mGroups.insert(mesh->mGroups.end(), mGroups.begin(), mGroups.end());
	return mesh;
}

} /* namespace scene */
} /* namespace pola */
