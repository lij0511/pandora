/*
 * MD2AnimatedMesh.cpp
 *
 *  Created on: 2016年5月24日
 *      Author: lijing
 */

#include <unistd.h>

#include "pola/scene/mesh/MD2AnimatedMesh.h"

namespace pola {
namespace scene {

const int32_t MD2_FRAME_SHIFT	= 2;
const float MD2_FRAME_SHIFT_RECIPROCAL = 1.f / (1 << MD2_FRAME_SHIFT);

const int32_t Q2_VERTEX_NORMAL_TABLE_SIZE = 162;

static const float Q2_VERTEX_NORMAL_TABLE[Q2_VERTEX_NORMAL_TABLE_SIZE][3] = {
	{-0.525731f, 0.000000f, 0.850651f},
	{-0.442863f, 0.238856f, 0.864188f},
	{-0.295242f, 0.000000f, 0.955423f},
	{-0.309017f, 0.500000f, 0.809017f},
	{-0.162460f, 0.262866f, 0.951056f},
	{0.000000f, 0.000000f, 1.000000f},
	{0.000000f, 0.850651f, 0.525731f},
	{-0.147621f, 0.716567f, 0.681718f},
	{0.147621f, 0.716567f, 0.681718f},
	{0.000000f, 0.525731f, 0.850651f},
	{0.309017f, 0.500000f, 0.809017f},
	{0.525731f, 0.000000f, 0.850651f},
	{0.295242f, 0.000000f, 0.955423f},
	{0.442863f, 0.238856f, 0.864188f},
	{0.162460f, 0.262866f, 0.951056f},
	{-0.681718f, 0.147621f, 0.716567f},
	{-0.809017f, 0.309017f, 0.500000f},
	{-0.587785f, 0.425325f, 0.688191f},
	{-0.850651f, 0.525731f, 0.000000f},
	{-0.864188f, 0.442863f, 0.238856f},
	{-0.716567f, 0.681718f, 0.147621f},
	{-0.688191f, 0.587785f, 0.425325f},
	{-0.500000f, 0.809017f, 0.309017f},
	{-0.238856f, 0.864188f, 0.442863f},
	{-0.425325f, 0.688191f, 0.587785f},
	{-0.716567f, 0.681718f, -0.147621f},
	{-0.500000f, 0.809017f, -0.309017f},
	{-0.525731f, 0.850651f, 0.000000f},
	{0.000000f, 0.850651f, -0.525731f},
	{-0.238856f, 0.864188f, -0.442863f},
	{0.000000f, 0.955423f, -0.295242f},
	{-0.262866f, 0.951056f, -0.162460f},
	{0.000000f, 1.000000f, 0.000000f},
	{0.000000f, 0.955423f, 0.295242f},
	{-0.262866f, 0.951056f, 0.162460f},
	{0.238856f, 0.864188f, 0.442863f},
	{0.262866f, 0.951056f, 0.162460f},
	{0.500000f, 0.809017f, 0.309017f},
	{0.238856f, 0.864188f, -0.442863f},
	{0.262866f, 0.951056f, -0.162460f},
	{0.500000f, 0.809017f, -0.309017f},
	{0.850651f, 0.525731f, 0.000000f},
	{0.716567f, 0.681718f, 0.147621f},
	{0.716567f, 0.681718f, -0.147621f},
	{0.525731f, 0.850651f, 0.000000f},
	{0.425325f, 0.688191f, 0.587785f},
	{0.864188f, 0.442863f, 0.238856f},
	{0.688191f, 0.587785f, 0.425325f},
	{0.809017f, 0.309017f, 0.500000f},
	{0.681718f, 0.147621f, 0.716567f},
	{0.587785f, 0.425325f, 0.688191f},
	{0.955423f, 0.295242f, 0.000000f},
	{1.000000f, 0.000000f, 0.000000f},
	{0.951056f, 0.162460f, 0.262866f},
	{0.850651f, -0.525731f, 0.000000f},
	{0.955423f, -0.295242f, 0.000000f},
	{0.864188f, -0.442863f, 0.238856f},
	{0.951056f, -0.162460f, 0.262866f},
	{0.809017f, -0.309017f, 0.500000f},
	{0.681718f, -0.147621f, 0.716567f},
	{0.850651f, 0.000000f, 0.525731f},
	{0.864188f, 0.442863f, -0.238856f},
	{0.809017f, 0.309017f, -0.500000f},
	{0.951056f, 0.162460f, -0.262866f},
	{0.525731f, 0.000000f, -0.850651f},
	{0.681718f, 0.147621f, -0.716567f},
	{0.681718f, -0.147621f, -0.716567f},
	{0.850651f, 0.000000f, -0.525731f},
	{0.809017f, -0.309017f, -0.500000f},
	{0.864188f, -0.442863f, -0.238856f},
	{0.951056f, -0.162460f, -0.262866f},
	{0.147621f, 0.716567f, -0.681718f},
	{0.309017f, 0.500000f, -0.809017f},
	{0.425325f, 0.688191f, -0.587785f},
	{0.442863f, 0.238856f, -0.864188f},
	{0.587785f, 0.425325f, -0.688191f},
	{0.688191f, 0.587785f, -0.425325f},
	{-0.147621f, 0.716567f, -0.681718f},
	{-0.309017f, 0.500000f, -0.809017f},
	{0.000000f, 0.525731f, -0.850651f},
	{-0.525731f, 0.000000f, -0.850651f},
	{-0.442863f, 0.238856f, -0.864188f},
	{-0.295242f, 0.000000f, -0.955423f},
	{-0.162460f, 0.262866f, -0.951056f},
	{0.000000f, 0.000000f, -1.000000f},
	{0.295242f, 0.000000f, -0.955423f},
	{0.162460f, 0.262866f, -0.951056f},
	{-0.442863f, -0.238856f, -0.864188f},
	{-0.309017f, -0.500000f, -0.809017f},
	{-0.162460f, -0.262866f, -0.951056f},
	{0.000000f, -0.850651f, -0.525731f},
	{-0.147621f, -0.716567f, -0.681718f},
	{0.147621f, -0.716567f, -0.681718f},
	{0.000000f, -0.525731f, -0.850651f},
	{0.309017f, -0.500000f, -0.809017f},
	{0.442863f, -0.238856f, -0.864188f},
	{0.162460f, -0.262866f, -0.951056f},
	{0.238856f, -0.864188f, -0.442863f},
	{0.500000f, -0.809017f, -0.309017f},
	{0.425325f, -0.688191f, -0.587785f},
	{0.716567f, -0.681718f, -0.147621f},
	{0.688191f, -0.587785f, -0.425325f},
	{0.587785f, -0.425325f, -0.688191f},
	{0.000000f, -0.955423f, -0.295242f},
	{0.000000f, -1.000000f, 0.000000f},
	{0.262866f, -0.951056f, -0.162460f},
	{0.000000f, -0.850651f, 0.525731f},
	{0.000000f, -0.955423f, 0.295242f},
	{0.238856f, -0.864188f, 0.442863f},
	{0.262866f, -0.951056f, 0.162460f},
	{0.500000f, -0.809017f, 0.309017f},
	{0.716567f, -0.681718f, 0.147621f},
	{0.525731f, -0.850651f, 0.000000f},
	{-0.238856f, -0.864188f, -0.442863f},
	{-0.500000f, -0.809017f, -0.309017f},
	{-0.262866f, -0.951056f, -0.162460f},
	{-0.850651f, -0.525731f, 0.000000f},
	{-0.716567f, -0.681718f, -0.147621f},
	{-0.716567f, -0.681718f, 0.147621f},
	{-0.525731f, -0.850651f, 0.000000f},
	{-0.500000f, -0.809017f, 0.309017f},
	{-0.238856f, -0.864188f, 0.442863f},
	{-0.262866f, -0.951056f, 0.162460f},
	{-0.864188f, -0.442863f, 0.238856f},
	{-0.809017f, -0.309017f, 0.500000f},
	{-0.688191f, -0.587785f, 0.425325f},
	{-0.681718f, -0.147621f, 0.716567f},
	{-0.442863f, -0.238856f, 0.864188f},
	{-0.587785f, -0.425325f, 0.688191f},
	{-0.309017f, -0.500000f, 0.809017f},
	{-0.147621f, -0.716567f, 0.681718f},
	{-0.425325f, -0.688191f, 0.587785f},
	{-0.162460f, -0.262866f, 0.951056f},
	{0.442863f, -0.238856f, 0.864188f},
	{0.162460f, -0.262866f, 0.951056f},
	{0.309017f, -0.500000f, 0.809017f},
	{0.147621f, -0.716567f, 0.681718f},
	{0.000000f, -0.525731f, 0.850651f},
	{0.425325f, -0.688191f, 0.587785f},
	{0.587785f, -0.425325f, 0.688191f},
	{0.688191f, -0.587785f, 0.425325f},
	{-0.955423f, 0.295242f, 0.000000f},
	{-0.951056f, 0.162460f, 0.262866f},
	{-1.000000f, 0.000000f, 0.000000f},
	{-0.850651f, 0.000000f, 0.525731f},
	{-0.955423f, -0.295242f, 0.000000f},
	{-0.951056f, -0.162460f, 0.262866f},
	{-0.864188f, 0.442863f, -0.238856f},
	{-0.951056f, 0.162460f, -0.262866f},
	{-0.809017f, 0.309017f, -0.500000f},
	{-0.864188f, -0.442863f, -0.238856f},
	{-0.951056f, -0.162460f, -0.262866f},
	{-0.809017f, -0.309017f, -0.500000f},
	{-0.681718f, 0.147621f, -0.716567f},
	{-0.681718f, -0.147621f, -0.716567f},
	{-0.850651f, 0.000000f, -0.525731f},
	{-0.688191f, 0.587785f, -0.425325f},
	{-0.587785f, 0.425325f, -0.688191f},
	{-0.425325f, 0.688191f, -0.587785f},
	{-0.425325f, -0.688191f, -0.587785f},
	{-0.587785f, -0.425325f, -0.688191f},
	{-0.688191f, -0.587785f, -0.425325f},
};

struct MD2AnimationType {
	int32_t begin;
	int32_t end;
	int32_t fps;
};

static const MD2AnimationType MD2AnimationTypeList[21] = {
	{  0,  39,  9}, // STAND
	{ 40,  45, 10}, // RUN
	{ 46,  53, 10}, // ATTACK
	{ 54,  57,  7}, // PAIN_A
	{ 58,  61,  7}, // PAIN_B
	{ 62,  65,  7}, // PAIN_C
	{ 66,  71,  7}, // JUMP
	{ 72,  83,  7}, // FLIP
	{ 84,  94,  7}, // SALUTE
	{ 95, 111, 10}, // FALLBACK
	{112, 122,  7}, // WAVE
	{123, 134,  6}, // POINT
	{135, 153, 10}, // CROUCH_STAND
	{154, 159,  7}, // CROUCH_WALK
	{160, 168, 10}, // CROUCH_ATTACK
	{169, 172,  7}, // CROUCH_PAIN
	{173, 177,  5}, // CROUCH_DEATH
	{178, 183,  7}, // DEATH_FALLBACK
	{184, 189,  7}, // DEATH_FALLFORWARD
	{190, 197,  7}, // DEATH_FALLBACKSLOW
	{198, 198,  5}, // BOOM
};

MD2AnimatedMesh::MD2AnimatedMesh() :
	mCurentFrame(-1), mStartFrameLoop(-1), mEndFrameLoop(-1), mGeometry(new graphic::Geometry3D) {
	mGeometry->ref();
}

MD2AnimatedMesh::~MD2AnimatedMesh() {
	mGeometry->deref();
}

void MD2AnimatedMesh::getFrameLoop(MD2_ANIMATION_TYPE animationType, int32_t& outBegin, int32_t& outEnd, int32_t& outFPS) const {
	if (animationType < 0 || animationType >= MD2_AT_COUNT)
		return;

	outBegin = MD2AnimationTypeList[animationType].begin << MD2_FRAME_SHIFT;
	outEnd = MD2AnimationTypeList[animationType].end << MD2_FRAME_SHIFT;

	// correct to anim between last->first frame
	outEnd += MD2_FRAME_SHIFT == 0 ? 1 : (1 << MD2_FRAME_SHIFT) - 1;
	outFPS = MD2AnimationTypeList[animationType].fps << MD2_FRAME_SHIFT;
}

void MD2AnimatedMesh::updateMeshBuffer(int32_t frame, int32_t startFrameLoop, int32_t endFrameLoop) {

	if (mCurentFrame == frame && mStartFrameLoop == startFrameLoop && mEndFrameLoop == endFrameLoop) {
		return;
	}
	mCurentFrame = frame;
	mStartFrameLoop = startFrameLoop;
	mEndFrameLoop = endFrameLoop;
	uint32_t firstFrame, secondFrame;
	float div;

	// TA: resolve missing ipol in loop between end-start

	if (endFrameLoop - startFrameLoop == 0) {
		firstFrame = frame >> MD2_FRAME_SHIFT;
		secondFrame = frame >> MD2_FRAME_SHIFT;
		div = 1.0f;
	} else {
		// key frames
		uint32_t s = startFrameLoop >> MD2_FRAME_SHIFT;
		uint32_t e = endFrameLoop >> MD2_FRAME_SHIFT;

		firstFrame = frame >> MD2_FRAME_SHIFT;
		secondFrame = firstFrame + 1 > e ? s : firstFrame + 1;

		firstFrame = fmin(mFrameCount - 1, firstFrame);
		secondFrame = fmin(mFrameCount - 1, secondFrame);

		//div = (frame % (1<<MD2_FRAME_SHIFT)) / (f32)(1<<MD2_FRAME_SHIFT);
		frame &= (1 << MD2_FRAME_SHIFT) - 1;
		div = frame * MD2_FRAME_SHIFT_RECIPROCAL;
	}

	graphic::vec3* positions = mGeometry->positions();
	graphic::vec3* normals = mGeometry->normals();
	const FrameItem* first = frameList[firstFrame].data();
	const FrameItem* second = frameList[secondFrame].data();
	// interpolate both frames
	const size_t count = frameList[firstFrame].size();
	if (first == second) {
		for (uint32_t i = 0; i < count; ++i) {
			float x = first[0].pos[0] * frameTransforms[firstFrame].scale[0] + frameTransforms[firstFrame].translate[0];
			float y = first[0].pos[1] * frameTransforms[firstFrame].scale[1] + frameTransforms[firstFrame].translate[1];
			float z = first[0].pos[2] * frameTransforms[firstFrame].scale[2] + frameTransforms[firstFrame].translate[2];
			*positions = {x, y, z};
			*normals = {Q2_VERTEX_NORMAL_TABLE[first[0].normal_index][0], Q2_VERTEX_NORMAL_TABLE[first[0].normal_index][2], Q2_VERTEX_NORMAL_TABLE[first[0].normal_index][1]};

			positions ++;
			normals ++;
			first ++;
		}
	} else {
		for (uint32_t i = 0; i < count; ++i) {
			graphic::vec3 one = {first[0].pos[0] * frameTransforms[firstFrame].scale[0] + frameTransforms[firstFrame].translate[0],
					first[0].pos[1] * frameTransforms[firstFrame].scale[1] + frameTransforms[firstFrame].translate[1],
					first[0].pos[2] * frameTransforms[firstFrame].scale[2] + frameTransforms[firstFrame].translate[2]};
			graphic::vec3 two = {second[0].pos[0] * frameTransforms[secondFrame].scale[0] + frameTransforms[secondFrame].translate[0],
					second[0].pos[1] * frameTransforms[secondFrame].scale[1] + frameTransforms[secondFrame].translate[1],
					second[0].pos[2] * frameTransforms[secondFrame].scale[2] + frameTransforms[secondFrame].translate[2]};
			*positions = two.getInterpolated(one, div);
			const graphic::vec3 n1(
					Q2_VERTEX_NORMAL_TABLE[first[0].normal_index][0],
					Q2_VERTEX_NORMAL_TABLE[first[0].normal_index][2],
					Q2_VERTEX_NORMAL_TABLE[first[0].normal_index][1]);
			const graphic::vec3 n2(
					Q2_VERTEX_NORMAL_TABLE[second[0].normal_index][0],
					Q2_VERTEX_NORMAL_TABLE[second[0].normal_index][2],
					Q2_VERTEX_NORMAL_TABLE[second[0].normal_index][1]);
			*normals = n2.getInterpolated(n1, div);

			positions ++;
			normals ++;
			first ++;
			second ++;
		}
	}

}

size_t MD2AnimatedMesh::getFrameCount() const {
	return mFrameCount << MD2_FRAME_SHIFT;
}

graphic::Geometry* MD2AnimatedMesh::geometry() {
	return mGeometry;
}

} /* namespace scene */
} /* namespace pola */
