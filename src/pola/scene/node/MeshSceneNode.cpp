/*
 * MeshSceneNode.cpp
 *
 *  Created on: 2016年5月23日
 *      Author: lijing
 */

#include "pola/scene/node/MeshSceneNode.h"

namespace pola {
namespace scene {

MeshSceneNode::MeshSceneNode() : mMaterial(nullptr) {
}

MeshSceneNode::~MeshSceneNode() {
}

void MeshSceneNode::setMaterial(graphic::Material* material) {
	mMaterial = material;
}

} /* namespace scene */
} /* namespace pola */
