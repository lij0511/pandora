/*
 * AnimatedMeshSceneNode.cpp
 *
 *  Created on: 2016年5月29日
 *      Author: lijing
 */

#include "scene/node/AnimatedMeshSceneNode.h"

namespace pola {
namespace scene {

AnimatedMeshSceneNode::AnimatedMeshSceneNode() :
	mStartFrameLoop(0), mEndFrameLoop(0), mFramesPerMs(0.025f), mCurrentFrame(0), mLastTimeMs(0) {
}

AnimatedMeshSceneNode::~AnimatedMeshSceneNode() {
}

void AnimatedMeshSceneNode::setFrameLoop(int32_t startFrame, int32_t endFrame) {
	if (startFrame >= 0 && endFrame >= 0 && endFrame >= startFrame) {
		mStartFrameLoop = startFrame;
		mEndFrameLoop = endFrame;
	}
}

int32_t AnimatedMeshSceneNode::getCurrentFrame() const {
	return mCurrentFrame;
}

int32_t AnimatedMeshSceneNode::getStartFrameLoop() const {
	return mStartFrameLoop;
}

int32_t AnimatedMeshSceneNode::getEndFrameLoop() const {
	return mEndFrameLoop;
}

void AnimatedMeshSceneNode::setFramesPerMs(float framesPerMs) {
	mFramesPerMs = framesPerMs;
}

void AnimatedMeshSceneNode::render(graphic::GraphicContext* graphic, nsecs_t timeMs) {
	buildCurrentFrame(timeMs);
}

void AnimatedMeshSceneNode::buildCurrentFrame(nsecs_t timeMs) {
	if (mLastTimeMs == 0) {
		mLastTimeMs = timeMs;
	}

	nsecs_t interval = timeMs - mLastTimeMs;
	mLastTimeMs = timeMs;

	if (mStartFrameLoop == mEndFrameLoop) {
		mCurrentFrame = mStartFrameLoop;
	} else {
		// play animation looped
		mCurrentFrame += interval * mFramesPerMs;

		// We have no interpolation between EndFrame and StartFrame,
		// the last frame must be identical to first one with our current solution.
		if (mFramesPerMs > 0.f) //forwards...
		{
			if (mCurrentFrame > mEndFrameLoop)
				mCurrentFrame = mStartFrameLoop + fmod(mCurrentFrame - mStartFrameLoop, (float) (mEndFrameLoop - mStartFrameLoop));
		}
		else //backwards...
		{
			if (mCurrentFrame < mStartFrameLoop)
				mCurrentFrame = mEndFrameLoop - fmod(mEndFrameLoop - mCurrentFrame, (float) (mEndFrameLoop - mStartFrameLoop));
		}
	}

}

} /* namespace scene */
} /* namespace pola */
