/*
 * Mesh.cpp
 *
 *  Created on: 2016年8月10日
 *      Author: lijing
 */

#include "pola/scene/mesh/Mesh.h"

namespace pola {
namespace scene {

Mesh::Mesh() : mMaterialId(0) {
}
Mesh::~Mesh() {
}

void Mesh::setMaterialId(uint32_t materialId) {
	mMaterialId = materialId;
}
uint32_t Mesh::materialId() const {
	return mMaterialId;
}

}
}
