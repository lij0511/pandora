/*
 * MeshSceneNode.h
 *
 *  Created on: 2016年5月23日
 *      Author: lijing
 */

#ifndef POLA_MESHSCENENODE_H_
#define POLA_MESHSCENENODE_H_

#include "pola/graphic/GraphicContext.h"
#include "pola/graphic/material/Material.h"
#include "pola/scene/node/SceneNode.h"
#include "pola/scene/mesh/Mesh.h"

#include <vector>

namespace pola {
namespace scene {

class MeshSceneNode: public SceneNode {
public:
	MeshSceneNode();
	virtual ~MeshSceneNode();

	void setMaterial(uint32_t index, graphic::Material* material);

	virtual Mesh* mesh(uint32_t index) = 0;
	virtual uint32_t meshCount() const;
	virtual graphic::Material* material(uint32_t index) const;

	virtual void render(graphic::GraphicContext* graphic, p_nsecs_t timeMs);
	virtual void render(graphic::GraphicContext* graphic, graphic::Material* m, p_nsecs_t timeMs);

protected:
	std::vector<graphic::Material*> mMaterials;

};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_MESHSCENENODE_H_ */
