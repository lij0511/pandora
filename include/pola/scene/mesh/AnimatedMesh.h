/*
 * AnimatedMesh.h
 *
 *  Created on: 2016年5月21日
 *      Author: lijing
 */

#ifndef POLA_ANIMATEDMESH_H_
#define POLA_ANIMATEDMESH_H_

#include "pola/scene/mesh/Mesh.h"

namespace pola {
namespace scene {

class AnimatedMesh: public Mesh {
public:

	AnimatedMesh();

	virtual ~AnimatedMesh() {};

	void setFrameCount(size_t frameCount);
	virtual size_t getFrameCount() const;

protected:
	size_t mFrameCount;
};

inline AnimatedMesh::AnimatedMesh() : mFrameCount(0) {
}

inline void AnimatedMesh::setFrameCount(size_t frameCount) {
	mFrameCount = frameCount;
}

inline size_t AnimatedMesh::getFrameCount() const {
	return mFrameCount;
}

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_ANIMATEDMESH_H_ */
