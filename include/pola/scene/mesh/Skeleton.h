/*
 * Skeleton.h
 *
 *  Created on: 2016年8月19日
 *      Author: lijing
 */

#ifndef POLA_SKELETON_H_
#define POLA_SKELETON_H_

#include "pola/graphic/math/Math.h"
#include "pola/utils/RefBase.h"

#include <vector>
#include <string>

namespace pola {
namespace scene {

struct VertexWeight {
	uint32_t vertex_id;
	float weight;
};

class Joint {
public:
	Joint();
	Joint(const std::string& name);
	virtual ~Joint();

	std::string name;
	std::string parentName;
	Joint* parent;
	std::vector<Joint*> children;

	std::vector<VertexWeight> vertices;

	graphic::vec3 position;
	graphic::quat4 rotation;
	graphic::vec3 scale;
};

class Skeleton : public pola::utils::RefBase<Skeleton> {
public:
	Skeleton();
	virtual ~Skeleton();

	Joint* addJoint();
	Joint* getJoint(unsigned index) const;

	void finalize();

private:
	bool mFinalized;
	std::vector<Joint*> mJoints;
	std::vector<Joint*> mAllJoints;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_SKELETON_H_ */
