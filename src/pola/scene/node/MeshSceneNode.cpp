/*
 * MeshSceneNode.cpp
 *
 *  Created on: 2016年5月23日
 *      Author: lijing
 */

#include "pola/scene/node/MeshSceneNode.h"

namespace pola {
namespace scene {

MeshSceneNode::MeshSceneNode() {
}

MeshSceneNode::~MeshSceneNode() {
	for (std::vector<graphic::Material*>::iterator iter = mMaterials.begin(); iter != mMaterials.end(); iter ++) {
		(*iter)->deref();
	}
	mMaterials.clear();
}

void MeshSceneNode::setMaterial(uint32_t index, graphic::Material* material) {
	if (index > mMaterials.size()) {
		index = 0;
	}
	if (mMaterials.size() > index) {
		if (material != mMaterials[index]) {
			if (mMaterials[index] != nullptr) {
				mMaterials[index]->deref();
			}
			if (material != nullptr) {
				material->ref();
			}
			mMaterials[index] = material;
		}
	} else if (material != nullptr) {
		material->ref();
		mMaterials.push_back(material);
	}
}

graphic::Material* MeshSceneNode::material(uint32_t index) const {
	if (mMaterials.empty()) return nullptr;
	return index < mMaterials.size() ? mMaterials[index] : mMaterials[0];
}

void MeshSceneNode::render(graphic::GraphicContext* graphic, p_nsecs_t timeMs) {
	render(graphic, nullptr, timeMs);
}
void MeshSceneNode::render(graphic::GraphicContext* graphic, graphic::Material* m, p_nsecs_t timeMs) {
	Mesh* ms = mesh();
	if (ms->groupCount() > 0) {
		for (unsigned i = 0; i < ms->groupCount(); i ++) {
			Mesh::Group group = ms->group(i);
			graphic->renderGeometry(ms->geometry(), group.start, group.end, m != nullptr ? m : material(group.materialId));
		}
	} else {
		graphic->renderGeometry(ms->geometry(), 0, 0, m != nullptr ? m : material(0));
	}
}

} /* namespace scene */
} /* namespace pola */
