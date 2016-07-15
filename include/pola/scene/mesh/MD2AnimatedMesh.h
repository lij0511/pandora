/*
 * MD2AnimatedMesh.h
 *
 *  Created on: 2016年5月24日
 *      Author: lijing
 */

#ifndef MD2ANIMATEDMESH_H_
#define MD2ANIMATEDMESH_H_

#include "pola/scene/mesh/AnimatedMesh.h"
#include "pola/graphic/geometries/Geometry3D.h"

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
	MD2_AT_STAND = 0,
	MD2_AT_RUN,
	MD2_AT_ATTACK,
	MD2_AT_PAIN_A,
	MD2_AT_PAIN_B,
	MD2_AT_PAIN_C,
	MD2_AT_JUMP,
	MD2_AT_FLIP,
	MD2_AT_SALUTE,
	MD2_AT_FALLBACK,
	MD2_AT_WAVE,
	MD2_AT_POINT,
	MD2_AT_CROUCH_STAND,
	MD2_AT_CROUCH_WALK,
	MD2_AT_CROUCH_ATTACK,
	MD2_AT_CROUCH_PAIN,
	MD2_AT_CROUCH_DEATH,
	MD2_AT_DEATH_FALLBACK,
	MD2_AT_DEATH_FALLFORWARD,
	MD2_AT_DEATH_FALLBACKSLOW,
	MD2_AT_BOOM,

	//! Not an animation, but amount of animation types.
	MD2_AT_COUNT
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

	size_t getFrameCount() const;

	virtual graphic::Geometry* geometry();

	utils::Vector<utils::Vector<FrameItem>> frameList;
	utils::Vector<FrameTransform> frameTransforms;
	size_t frameCount;

private:
	int32_t mCurentFrame;
	int32_t mStartFrameLoop;
	int32_t mEndFrameLoop;
	graphic::Geometry3D* mGeometry;
};

} /* namespace scene */
} /* namespace pola */

#endif /* MD2ANIMATEDMESH_H_ */
