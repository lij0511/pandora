/*
 * FrameAnimation.cpp
 *
 *  Created on: 2016年8月18日
 *      Author: lijing
 */

#include "pola/scene/animation/FrameAnimation.h"
#include "pola/scene/mesh/Mesh.h"

#include "pola/log/Log.h"

namespace pola {
namespace scene {

FrameAnimation::FrameAnimation(const std::string& name) : Animation(name) {
}

FrameAnimation::~FrameAnimation() {
}

uint16_t FrameAnimation::getFrameCount() const {
	return mKeyFrames.size();
}

FrameAnimation::KeyFrameData& FrameAnimation::addKeyFrame(float frameTime) {
	LOG_FATAL_IF(frameTime < 0, "frameTime should not be less than 0.");
	mDuration += frameTime;
	mKeyFrames.push_back({frameTime});
	return mKeyFrames.back().frameData;
}

void FrameAnimation::addKeyFrame(float frameTime, const KeyFrameData& frameData) {
	LOG_FATAL_IF(frameTime < 0, "frameTime should not be less than 0.");
	mDuration += frameTime;
	mKeyFrames.push_back({frameTime, frameData});
}

void FrameAnimation::applyFrame(float frameTime, Mesh* mesh) {
	if (frameTime < 0) return;
	if (mKeyFrames.empty()) return;
	unsigned i = 0;
	while (1) {
		if (frameTime >= mKeyFrames[i].frameTime && i < mKeyFrames.size() - 1) {
			i ++;
			frameTime -= mKeyFrames[i].frameTime;
		} else {
			break;
		}
	}
	if (i == mKeyFrames.size() - 1 && frameTime > mKeyFrames[i].frameTime) {
		frameTime = mKeyFrames[i].frameTime;
	}
	graphic::Geometry3D* geometry = (graphic::Geometry3D*) mesh->geometry();
	if (frameTime == 0) {
		KeyFrame<KeyFrameData>& firstKeyFrame = mKeyFrames[i];
		memcpy(geometry->positions(), firstKeyFrame.frameData.positions.data(), sizeof(graphic::vec3) * geometry->positionCount());
		if (geometry->normalCount() <= firstKeyFrame.frameData.normals.size()) {
			memcpy(geometry->normals(), firstKeyFrame.frameData.normals.data(), sizeof(graphic::vec3) * geometry->normalCount());
		}
		if (geometry->uvCount() <= firstKeyFrame.frameData.uvs.size()) {
			memcpy(geometry->uvs(), firstKeyFrame.frameData.uvs.data(), sizeof(graphic::vec2) * geometry->uvCount());
		}
	} else {
		KeyFrame<KeyFrameData>& firstKeyFrame = mKeyFrames[i];
		KeyFrame<KeyFrameData>& secondKeyFrame = (i == mKeyFrames.size() - 1) ? mKeyFrames[0] : mKeyFrames[i + 1];
		float d = frameTime / firstKeyFrame.frameTime;
		if (geometry->positionCount() <= firstKeyFrame.frameData.positions.size()) {
			graphic::vec3* positions = geometry->positions();
			graphic::vec3* normals = geometry->normals();
			graphic::vec2* uvs = geometry->uvs();
			for (uint32_t k = 0; k < geometry->positionCount(); ++ k) {
				positions[k] = secondKeyFrame.frameData.positions[k].getInterpolated(firstKeyFrame.frameData.positions[k], d);
				if (firstKeyFrame.frameData.normals.size() > 0) {
					normals[k] = secondKeyFrame.frameData.normals[k].getInterpolated(firstKeyFrame.frameData.normals[k], d);
				}
				if (firstKeyFrame.frameData.uvs.size() > 0) {
					uvs[k] = secondKeyFrame.frameData.uvs[k].getInterpolated(firstKeyFrame.frameData.uvs[k], d);
				}
			}
		}
	}
}

} /* namespace scene */
} /* namespace pola */
