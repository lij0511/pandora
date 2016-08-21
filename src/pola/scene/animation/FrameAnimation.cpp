/*
 * FrameAnimation.cpp
 *
 *  Created on: 2016年8月18日
 *      Author: lijing
 */

#include "pola/scene/animation/FrameAnimation.h"

namespace pola {
namespace scene {

FrameAnimation::FrameAnimation(const std::string& name) : Animation(name) {
}

FrameAnimation::~FrameAnimation() {
}

uint16_t FrameAnimation::getFrameCount() const {
	return mPositions.size();
}

std::vector<graphic::vec3>& FrameAnimation::positions() {
	return mPositions;
}
std::vector<graphic::vec3>& FrameAnimation::normals() {
	return mNormals;
}
std::vector<graphic::vec2>& FrameAnimation::uvs() {
	return mUvs;
}

} /* namespace scene */
} /* namespace pola */
