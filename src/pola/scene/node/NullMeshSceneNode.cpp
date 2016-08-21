/*
 * NullMeshSceneNode.cpp
 *
 *  Created on: 2016年8月17日
 *      Author: lijing
 */

#include "NullMeshSceneNode.h"
#include "pola/log/Log.h"

namespace pola {
namespace scene {

NullMeshSceneNode::NullMeshSceneNode(IMesh* mesh) : mMesh(mesh) {
	mMesh->ref();
	LOG_FATAL_IF(mMesh->geometry() != nullptr, "Not null mesh.");
}

NullMeshSceneNode::~NullMeshSceneNode() {
	mMesh->deref();
}

} /* namespace scene */
} /* namespace pola */
