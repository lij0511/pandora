/*
 * AbsMeshSceneNode.cpp
 *
 *  Created on: 2016年5月23日
 *      Author: lijing
 */

#include "pola/scene/node/AbsMeshSceneNode.h"

namespace pola {
namespace scene {

AbsMeshSceneNode::AbsMeshSceneNode(IMesh* mesh) {
	mMesh = mesh;
	mMesh->ref();
}

AbsMeshSceneNode::~AbsMeshSceneNode() {
	for (std::vector<graphic::Material*>::iterator iter = mMaterials.begin(); iter != mMaterials.end(); iter ++) {
		(*iter)->deref();
	}
	mMaterials.clear();
	mMesh->deref();
}

void AbsMeshSceneNode::setMaterial(uint16_t index, graphic::Material* material) {
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

IMesh* AbsMeshSceneNode::mesh() {
	return mMesh;
}

graphic::Material* AbsMeshSceneNode::material(uint16_t index) const {
	if (mMaterials.empty()) return nullptr;
	return index < mMaterials.size() ? mMaterials[index] : mMaterials[0];
}

void AbsMeshSceneNode::render(graphic::GraphicContext* graphic, p_nsecs_t timeMs) {
	render(graphic, nullptr, timeMs);
}
void AbsMeshSceneNode::render(graphic::GraphicContext* graphic, graphic::Material* m, p_nsecs_t timeMs) {
	IMesh* ms = mesh();
	if (ms->groupCount() > 0) {
		for (unsigned i = 0; i < ms->groupCount(); i ++) {
			IMesh::Group group = ms->group(i);
			graphic->renderGeometry(ms->geometry(), group.start, group.end, m != nullptr ? m : material(group.materialId));
		}
	} else {
		graphic->renderGeometry(ms->geometry(), 0, 0, m != nullptr ? m : material(ms->materialId()));
	}
}

} /* namespace scene */
} /* namespace pola */
