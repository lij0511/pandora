/*
 * AnimatedMeshSceneNode.h
 *
 *  Created on: 2016年5月29日
 *      Author: lijing
 */

#ifndef POLA_ANIMATEDMESHSCENENODE_H_
#define POLA_ANIMATEDMESHSCENENODE_H_

#include "pola/scene/node/MeshSceneNode.h"
#include "pola/scene/mesh/AnimatedMesh.h"

namespace pola {
namespace scene {

class AnimatedMeshSceneNode: public MeshSceneNode {
public:
	AnimatedMeshSceneNode(AnimatedMesh* mesh);
	virtual ~AnimatedMeshSceneNode();

	void setFrameLoop(int32_t startFrame, int32_t endFrame);
	void setFramesPerSecond(float fps);
	void setCurrentFrame(float frame);

	float getCurrentFrame() const;
	int32_t getStartFrameLoop() const;
	int32_t getEndFrameLoop() const;

	virtual void update(p_nsecs_t timeMs);

protected:
	virtual void buildCurrentFrame(p_nsecs_t timeMs);

private:

	int32_t mStartFrameLoop;
	int32_t mEndFrameLoop;
	float mFramesPerSecond;
	float mCurrentFrame;

	p_nsecs_t mLastTimeMs;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_ANIMATEDMESHSCENENODE_H_ */
