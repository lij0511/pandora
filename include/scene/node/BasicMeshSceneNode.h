/*
 * BasicMeshSceneNode.h
 *
 *  Created on: 2016年6月13日
 *      Author: lijing
 */

#ifndef POLA_BASICMESHSCENENODE_H_
#define POLA_BASICMESHSCENENODE_H_

#include "scene/node/MeshSceneNode.h"
#include "scene/mesh/BasicMesh.h"
#include "graphic/Material.h"

namespace pola {
namespace scene {

class BasicMeshSceneNode: public MeshSceneNode {
public:
	BasicMeshSceneNode(BasicMesh* mesh);
	virtual ~BasicMeshSceneNode();

	void setMaterialTexture(uint32_t i, graphic::Texture* texture);

protected:
	virtual void render(graphic::GraphicContext* graphic, nsecs_t timeMs);

private:
	BasicMesh* mMesh;
	graphic::Material mMaterial;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_BASICMESHSCENENODE_H_ */
