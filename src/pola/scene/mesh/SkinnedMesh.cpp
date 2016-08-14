/*
 * SkinnedMesh.cpp
 *
 *  Created on: 2016年8月11日
 *      Author: lijing
 */

#include "pola/scene/mesh/SkinnedMesh.h"

namespace pola {
namespace scene {

SkinnedMesh::SkinnedMesh() : mFinalized(false), mLocalGeometry(new graphic::Geometry3D), mGeometry(new graphic::Geometry3D) {
}

SkinnedMesh::~SkinnedMesh() {
}

graphic::Geometry* SkinnedMesh::geometry() {
	return mGeometry;
}

graphic::Geometry3D* SkinnedMesh::localGeometry() {
	return mLocalGeometry;
}

SkinnedMesh::Joint* SkinnedMesh::addJoint() {
	if (mFinalized) return nullptr;
	mAllJoints.push_back(new Joint);
	return mAllJoints[mAllJoints.size() - 1];
}

void SkinnedMesh::finalize() {
	if (mFinalized) return;
	mFinalized = true;
	for (unsigned i = 0; i < mAllJoints.size(); i ++) {
		Joint* joint = mAllJoints[i];
		if (joint->parentName.empty()) {
			mJoints.push_back(joint);
		} else {
			for (unsigned j = 0; j < mAllJoints.size(); j ++) {
				Joint* jt = mAllJoints[i];
				if (jt != joint && jt->name == joint->parentName) {
					jt->children.push_back(joint);
					joint->parent = jt;
					break;
				}
			}
		}
	}
}

} /* namespace scene */
} /* namespace pola */
