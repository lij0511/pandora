/*
 * MeshSceneNode.h
 *
 *  Created on: 2016年5月23日
 *      Author: lijing
 */

#ifndef POLA_MESHSCENENODE_H_
#define POLA_MESHSCENENODE_H_

#include "graphic/material/Material.h"
#include "scene/node/SceneNode.h"

namespace pola {
namespace scene {

class MeshSceneNode: public SceneNode {
public:
	MeshSceneNode();
	virtual ~MeshSceneNode();

	void setMaterial(graphic::Material* material);

protected:
	utils::sp<graphic::Material> mMaterial;

};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_MESHSCENENODE_H_ */
