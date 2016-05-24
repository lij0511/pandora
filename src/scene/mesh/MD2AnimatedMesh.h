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

/*
 *
 */
class MD2AnimatedMesh: public AnimatedMesh {
public:
	MD2AnimatedMesh();
	virtual ~MD2AnimatedMesh();

	virtual size_t getFrameCount() const;

	virtual size_t getMeshBufferCount() const;
	virtual MeshBuffer* getMeshBuffer(uint16_t index);

	MeshBuffer meshBuffer;

	utils::Vector<utils::Vector<FrameItem>> frameList;
	utils::Vector<FrameTransform> frameTransforms;
	size_t frameCount;
};

} /* namespace scene */
} /* namespace pola */

#endif /* MD2ANIMATEDMESH_H_ */
