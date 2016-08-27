/*
 * MeshSceneNode.cpp
 *
 *  Created on: 2016年8月24日
 *      Author: lijing
 */

#include "pola/scene/node/MeshSceneNode.h"

namespace pola {
namespace scene {

MeshSceneNode::MeshSceneNode(Mesh* mesh) {
	if (mesh->getAnimations() != nullptr) {
		mAnimation = mesh->getAnimations()->getAnimation(0);
		if (mAnimation != nullptr && mesh->getStrongCount() > 0) {
			mesh = mesh->clone();
		}
		if (mAnimation != nullptr) {
			mDuration = mAnimation->getDuration();
		}
	}
	mMesh = mesh;
	mMesh->ref();
}

MeshSceneNode::~MeshSceneNode() {
	for (std::vector<graphic::Material*>::iterator iter = mMaterials.begin(); iter != mMaterials.end(); iter ++) {
		(*iter)->deref();
	}
	mMaterials.clear();
	mMesh->deref();
}

void MeshSceneNode::setMaterial(uint16_t index, graphic::Material* material) {
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

IMesh* MeshSceneNode::mesh() {
	return mMesh;
}

graphic::Material* MeshSceneNode::material(uint16_t index) const {
	if (mMaterials.empty()) return nullptr;
	return index < mMaterials.size() ? mMaterials[index] : mMaterials[0];
}

void MeshSceneNode::update(p_nsecs_t timeMs) {
	if (mAnimation != nullptr && animate(timeMs)) {
		mAnimation->applyFrame(mCurrentFrame, mMesh);
	}
}

void MeshSceneNode::setAnimation(unsigned index) {
	Animations* animations = mMesh->getAnimations();
	if (animations != nullptr) {
		Animation* animation = animations->getAnimation(index);
		if (animation != nullptr) {
			mAnimation = animation;
			mDuration = mAnimation->getDuration();
		}
	}
}
void MeshSceneNode::setAnimation(const std::string& name) {
	Animations* animations = mMesh->getAnimations();
	if (animations != nullptr) {
		Animation* animation = animations->findAnimation(name);
		if (animation != nullptr) {
			mAnimation = animation;
			mDuration = mAnimation->getDuration();
		}
	}
}

void MeshSceneNode::render(graphic::GraphicContext* graphic, p_nsecs_t timeMs) {
	render(graphic, nullptr, timeMs);
}
void MeshSceneNode::render(graphic::GraphicContext* graphic, graphic::Material* m, p_nsecs_t timeMs) {
	Mesh* ms = mMesh;
	if (ms->groupCount() > 0) {
		for (unsigned i = 0; i < ms->groupCount(); i ++) {
			Mesh::Group group = ms->group(i);
			graphic->renderGeometry(ms->geometry(), group.start, group.end, m != nullptr ? m : material(group.materialId));
		}
	} else {
		graphic->renderGeometry(ms->geometry(), 0, 0, m != nullptr ? m : material(ms->materialId()));
	}
}

} /* namespace scene */
} /* namespace pola */
