/*
 * Animations.cpp
 *
 *  Created on: 2016年8月20日
 *      Author: lijing
 */

#include "pola/scene/animation/Animations.h"

namespace pola {
namespace scene {

Animations::Animations() {
}

Animations::~Animations() {
}

Animation* Animations::findAnimation(const std::string& name) const {
	for (unsigned i = 0; i < mAnimations.size(); i ++) {
		if (name == mAnimations[i]->name()) {
			return mAnimations[i];
		}
	}
	return nullptr;
}

Animation* Animations::getAnimation(unsigned index) const {
	if (index < mAnimations.size()) {
		return mAnimations[index];
	}
	return nullptr;
}

void Animations::addAnimation(Animation* animation) {
	for (unsigned i = 0; i < mAnimations.size(); i ++) {
		if (animation->name() == mAnimations[i]->name()) {
			if (animation != mAnimations[i]) {
				mAnimations[i]->deref();
				animation->ref();
				mAnimations[i] = animation;
			}
			return;
		}
	}
	animation->ref();
	mAnimations.push_back(animation);
}

size_t Animations::getAnimationCount() const {
	return mAnimations.size();
}

} /* namespace scene */
} /* namespace pola */
