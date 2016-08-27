/*
 * Skeleton.h
 *
 *  Created on: 2016年8月19日
 *      Author: lijing
 */

#ifndef POLA_SKELETON_H_
#define POLA_SKELETON_H_

#include "pola/graphic/math/Vector.h"
#include "pola/graphic/math/Matrix4.h"
#include "pola/graphic/math/Quaternion.h"
#include "pola/utils/RefBase.h"

#include <vector>
#include <string>

namespace pola {
namespace scene {

struct VertexWeight {
	uint32_t vertex_id;
	float weight;
};

class Bone {
public:
	Bone(std::string name);
	virtual ~Bone();

protected:
	std::string mName;
	Bone* mParent;
	std::vector<Bone*> mChildren;

	std::vector<VertexWeight> vertices;

	graphic::vec3 mPosition;
	graphic::quat4 mRotation;
	graphic::vec3 mScale;
};

class Skeleton : public pola::utils::RefBase<Skeleton> {
public:
	Skeleton();
	virtual ~Skeleton();

private:
	std::vector<Bone*> mBones;
	std::vector<Bone*> mAllBones;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_SKELETON_H_ */
