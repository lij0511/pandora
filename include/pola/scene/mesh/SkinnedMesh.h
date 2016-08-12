/*
 * SkinnedMesh.h
 *
 *  Created on: 2016年8月11日
 *      Author: lijing
 */

#ifndef POLA_SKINNEDMESH_H_
#define POLA_SKINNEDMESH_H_

#include "pola/graphic/math/Quaternion.h"
#include "pola/graphic/math/Vector.h"
#include "pola/graphic/math/Matrix4.h"
#include "pola/graphic/geometries/Geometry3D.h"
#include "pola/scene/mesh/AnimatedMesh.h"

#include <string>
#include <vector>

namespace pola {
namespace scene {

/*
 *
 */
class SkinnedMesh: public AnimatedMesh {
public:

	struct PositionKeyFrame {
		float frame;
		graphic::vec3 position;
	};
	struct ScaleKeyFrame {
		float frame;
		graphic::vec3 scale;
	};
	struct RotationKeyFrame {
		float frame;
		graphic::quat4 rotation;
	};
	struct VertexWeight {
		uint32_t vertex_id;
		float weight;
	};
	struct Joint {
		std::string name;
		std::vector<Joint> children;
		std::vector<VertexWeight> vertices;
		std::vector<PositionKeyFrame> positionKeyFrames;
		std::vector<ScaleKeyFrame> scaleKeyFrames;
		std::vector<RotationKeyFrame> rotationKeyFrames;
	};

	SkinnedMesh();
	virtual ~SkinnedMesh();

	virtual graphic::Geometry* geometry();

	graphic::Geometry3D* localGeometry();
	Joint& addJoint();

private:
	graphic::Geometry3D* mLocalGeometry;
	std::vector<Joint> mJoints;

	graphic::Geometry3D* mGeometry;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_SKINNEDMESH_H_ */
