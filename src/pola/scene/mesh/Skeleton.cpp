/*
 * Skeleton.cpp
 *
 *  Created on: 2016年8月19日
 *      Author: lijing
 */

#include "pola/scene/mesh/Skeleton.h"

namespace pola {
namespace scene {

Joint::Joint() : parent(nullptr) {
}
Joint::Joint(const std::string& n) : name(n), parent(nullptr) {
}
Joint::~Joint() {
	for(std::vector<Joint*>::iterator iter = children.begin(); iter != children.end(); iter ++) {
		delete *iter;
	}
	children.clear();
}

Skeleton::Skeleton() : mFinalized(false) {
}

Skeleton::~Skeleton() {
	for(std::vector<Joint*>::iterator iter = mJoints.begin(); iter != mJoints.end(); iter ++) {
		delete *iter;
	}
	mAllJoints.clear();
	mJoints.clear();
}

Joint* Skeleton::addJoint() {
	if (mFinalized) return nullptr;
	mAllJoints.push_back(new Joint);
	return mAllJoints[mAllJoints.size() - 1];
}

Joint* Skeleton::getJoint(unsigned index) const {
	return mAllJoints.at(index);
}

void Skeleton::finalize() {
	if (mFinalized) return;
	mFinalized = true;
	for (unsigned i = 0; i < mAllJoints.size(); i ++) {
		Joint* joint = mAllJoints[i];
		if (joint->parentName.empty()) {
			mJoints.push_back(joint);
		} else {
			bool findParent = false;
			for (unsigned j = 0; j < mAllJoints.size(); j ++) {
				Joint* jt = mAllJoints[j];
				if (jt != joint && jt->name == joint->parentName) {
					jt->children.push_back(joint);
					joint->parent = jt;
					findParent = true;
					break;
				}
			}
			if (!findParent) {
				mJoints.push_back(joint);
			}
		}
	}
}

} /* namespace scene */
} /* namespace pola */
