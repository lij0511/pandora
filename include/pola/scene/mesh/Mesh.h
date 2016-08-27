/*
 * Mesh.h
 *
 *  Created on: 2016年8月19日
 *      Author: lijing
 */

#ifndef POLA_MESH_H_
#define POLA_MESH_H_

#include "pola/graphic/geometries/Geometry3D.h"
#include "pola/graphic/geometries/Geometry2D.h"

#include "pola/scene/mesh/IMesh.h"
#include "pola/scene/mesh/Skeleton.h"

#include "pola/scene/animation/Animations.h"

namespace pola {
namespace scene {

/*
 *
 */
class Mesh: public IMesh {
public:
	Mesh();
	Mesh(graphic::Geometry3D* geometry);
	virtual ~Mesh();

	virtual graphic::Geometry* geometry();

	void setAnimations(Animations* animations);
	Animations* getAnimations() const;
	virtual bool hasAnimation() const;
	virtual Mesh* clone();

private:
	pola::utils::sp<graphic::Geometry> mGeometry;

	Skeleton* mSkeleton;

	pola::utils::sp<Animations> mAnimations;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_MESH_H_ */
