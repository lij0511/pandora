/*
 * AnimatedMeshSceneNode.h
 *
 *  Created on: 2016年5月29日
 *      Author: lijing
 */

#ifndef POLA_ANIMATEDMESHSCENENODE_H_
#define POLA_ANIMATEDMESHSCENENODE_H_

#include "scene/node/MeshSceneNode.h"

namespace pola {
namespace scene {

class AnimatedMeshSceneNode: public MeshSceneNode {
public:
	AnimatedMeshSceneNode();
	virtual ~AnimatedMeshSceneNode();

	void setFrameLoop(int32_t startFrame, int32_t endFrame);
	void setFramesPerMs(float framesPerMs);

	int32_t getCurrentFrame() const;
	int32_t getStartFrameLoop() const;
	int32_t getEndFrameLoop() const;

	virtual void render(graphic::GraphicContext* graphic, nsecs_t timeMs);

protected:
	virtual void buildCurrentFrame(nsecs_t timeMs);

private:

	int32_t mStartFrameLoop;
	int32_t mEndFrameLoop;
	float mFramesPerMs;
	float mCurrentFrame;

	nsecs_t mLastTimeMs;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_ANIMATEDMESHSCENENODE_H_ */
