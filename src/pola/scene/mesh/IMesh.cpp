/*
 * Mesh.cpp
 *
 *  Created on: 2016年8月10日
 *      Author: lijing
 */

#include "pola/scene/mesh/IMesh.h"

namespace pola {
namespace scene {

IMesh::IMesh() : mMaterialId(0) {
}
IMesh::~IMesh() {
	if (mChildren.size() > 0) {
		for (unsigned i = 0; i < mChildren.size(); i ++) {
			mChildren[i]->deref();
		}
		mChildren.clear();
	}
}

bool IMesh::animate(p_nsecs_t timeMs) {
	return false;
}

void IMesh::addGroup(uint32_t start, uint32_t end, uint16_t materialId) {
	mGroups.push_back({start, end, materialId});
}
void IMesh::addGroup(const IMesh::Group& group) {
	mGroups.push_back(group);
}

uint8_t IMesh::groupCount() const {
	return mGroups.size();
}
IMesh::Group IMesh::group(uint8_t index) const {
	return mGroups[index];
}

void IMesh::setMaterialId(uint16_t mId) {
	mMaterialId = mId;
}
uint16_t IMesh::materialId() const {
	return mMaterialId;
}

bool IMesh::intersectsBox(const graphic::Frustum& frustum, const graphic::mat4& transform) {
	graphic::Box3 boundingBox = geometry()->getBoundingBox();
	boundingBox.applyMatrix(transform);
	return frustum.intersectsBox(boundingBox);
}

void IMesh::addChild(IMesh* mesh) {
	mChildren.push_back(mesh);
	mesh->ref();
}
size_t IMesh::getChildCount() const {
	return mChildren.size();
}
IMesh* IMesh::getChild(unsigned index) {
	return mChildren.at(index);
}
}
}
