/*
 * Skeleton.cpp
 *
 *  Created on: 2016年8月19日
 *      Author: lijing
 */

#include "pola/scene/mesh/Skeleton.h"

namespace pola {
namespace scene {

Bone::Bone(std::string name) : mName(name), mParent(nullptr) {
}
Bone::~Bone() {
	for(std::vector<Bone*>::iterator iter = mChildren.begin(); iter != mChildren.end(); iter ++) {
		delete *iter;
	}
	mChildren.clear();
}

Skeleton::Skeleton() {
}

Skeleton::~Skeleton() {
	for(std::vector<Bone*>::iterator iter = mBones.begin(); iter != mBones.end(); iter ++) {
		delete *iter;
	}
	mAllBones.clear();
	mBones.clear();
}

} /* namespace scene */
} /* namespace pola */
