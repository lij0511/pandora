/*
 * MeshSceneNode.h
 *
 *  Created on: 2016年5月23日
 *      Author: lijing
 */

#ifndef POLA_MESHSCENENODE_H_
#define POLA_MESHSCENENODE_H_

#include "pola/graphic/material/Material.h"
#include "pola/scene/node/SceneNode.h"
#include "pola/scene/mesh/Mesh.h"

namespace pola {
namespace scene {

class MeshSceneNode: public SceneNode {
public:
	MeshSceneNode();
	virtual ~MeshSceneNode();

	void setMaterial(graphic::Material* material);

	virtual Mesh* mesh() = 0;

protected:
	utils::sp<graphic::Material> mMaterial;

};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_MESHSCENENODE_H_ */
