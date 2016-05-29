/*
 * MD2AnimatedMesh.h
 *
 *  Created on: 2016年5月24日
 *      Author: lijing
 */

#ifndef MD2ANIMATEDMESH_H_
#define MD2ANIMATEDMESH_H_

#include "scene/mesh/AnimatedMesh.h"

namespace pola {
namespace scene {

struct FrameTransform {
	float scale[3];
	float translate[3];
};

struct FrameItem {
	uint8_t pos[3];
	uint8_t normal_index;
};

//! Types of standard md2 animations
enum MD2_ANIMATION_TYPE {
	MAT_STAND = 0,
	MAT_RUN,
	MAT_ATTACK,
	MAT_PAIN_A,
	MAT_PAIN_B,
	MAT_PAIN_C,
	MAT_JUMP,
	MAT_FLIP,
	MAT_SALUTE,
	MAT_FALLBACK,
	MAT_WAVE,
	MAT_POINT,
	MAT_CROUCH_STAND,
	MAT_CROUCH_WALK,
	MAT_CROUCH_ATTACK,
	MAT_CROUCH_PAIN,
	MAT_CROUCH_DEATH,
	MAT_DEATH_FALLBACK,
	MAT_DEATH_FALLFORWARD,
	MAT_DEATH_FALLBACKSLOW,
	MAT_BOOM,

	//! Not an animation, but amount of animation types.
	MAT_COUNT
};

/*
 *
 */
class MD2AnimatedMesh: public AnimatedMesh {
public:
	MD2AnimatedMesh();
	virtual ~MD2AnimatedMesh();

	virtual void getFrameLoop(MD2_ANIMATION_TYPE animationType, int32_t& outBegin, int32_t& outEnd, int32_t& outFPS) const;

	void updateMeshBuffer(int32_t frame, int32_t startFrameLoop, int32_t endFrameLoop);

	virtual size_t getFrameCount() const;

	virtual size_t getMeshBufferCount() const;
	virtual graphic::MeshBuffer* getMeshBuffer(uint16_t index);

	graphic::MeshBuffer meshBuffer;

	utils::Vector<utils::Vector<FrameItem>> frameList;
	utils::Vector<FrameTransform> frameTransforms;
	size_t frameCount;

private:
	int32_t mCurentFrame;
	int32_t mStartFrameLoop;
	int32_t mEndFrameLoop;
};

} /* namespace scene */
} /* namespace pola */

#endif /* MD2ANIMATEDMESH_H_ */
