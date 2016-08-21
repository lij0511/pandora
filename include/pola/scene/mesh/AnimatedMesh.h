/*
 * AnimatedMesh.h
 *
 *  Created on: 2016年5月21日
 *      Author: lijing
 */

#ifndef POLA_ANIMATEDMESH_H_
#define POLA_ANIMATEDMESH_H_

#include "pola/scene/mesh/IMesh.h"

namespace pola {
namespace scene {

class AnimatedMesh: public IMesh {
public:

	AnimatedMesh();

	virtual ~AnimatedMesh() {};

	void setFrameCount(size_t frameCount);
	virtual size_t getFrameCount() const;

	void setFramesPerSecond(float fps);
	float getFramesPerSecond() const;

	virtual void updateMeshBuffer(float frame, int32_t startFrameLoop, int32_t endFrameLoop);

protected:
	size_t mFrameCount;
	float mFramesPerSecond;
};

inline AnimatedMesh::AnimatedMesh() : mFrameCount(0), mFramesPerSecond(1.f) {
}

inline void AnimatedMesh::setFrameCount(size_t frameCount) {
	mFrameCount = frameCount;
}

inline size_t AnimatedMesh::getFrameCount() const {
	return mFrameCount;
}

inline void AnimatedMesh::setFramesPerSecond(float fps) {
	mFramesPerSecond = fps;
}

inline float AnimatedMesh::getFramesPerSecond() const {
	return mFramesPerSecond;
}

inline void AnimatedMesh::updateMeshBuffer(float frame, int32_t startFrameLoop, int32_t endFrameLoop) {
}

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_ANIMATEDMESH_H_ */
