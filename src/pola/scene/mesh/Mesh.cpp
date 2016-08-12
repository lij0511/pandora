/*
 * Mesh.cpp
 *
 *  Created on: 2016年8月10日
 *      Author: lijing
 */

#include "pola/scene/mesh/Mesh.h"

namespace pola {
namespace scene {

Mesh::Mesh() {
}
Mesh::~Mesh() {
}

void Mesh::addGroup(uint32_t start, uint32_t end, uint32_t materialId) {
	mGroups.push_back({start, end, materialId});
}
void Mesh::addGroup(const Mesh::Group& group) {
	mGroups.push_back(group);
}

uint8_t Mesh::groupCount() const {
	return mGroups.size();
}
Mesh::Group Mesh::group(uint8_t index) const {
	return mGroups[index];
}
}
}
