/*
 * SkinnedMesh.cpp
 *
 *  Created on: 2016年8月11日
 *      Author: lijing
 */

#include "pola/scene/mesh/SkinnedMesh.h"

namespace pola {
namespace scene {

SkinnedMesh::SkinnedMesh() : mFinalized(false), mLocalGeometry(new graphic::Geometry3D), mGeometry(new graphic::Geometry3D) {
	mGeometry->ref();
	mLocalGeometry->ref();
}

SkinnedMesh::~SkinnedMesh() {
	mGeometry->deref();
	mLocalGeometry->deref();
}

graphic::Geometry* SkinnedMesh::geometry() {
	return mGeometry;
}

graphic::Geometry3D* SkinnedMesh::localGeometry() {
	return mLocalGeometry;
}

SkinnedMesh::Joint* SkinnedMesh::addJoint() {
	if (mFinalized) return nullptr;
	mAllJoints.push_back(new Joint);
	return mAllJoints[mAllJoints.size() - 1];
}

SkinnedMesh::Joint* SkinnedMesh::getJoint(unsigned index) const {
	return mAllJoints.at(index);
}

void SkinnedMesh::finalize() {
	if (mFinalized) return;
	mFinalized = true;
	for (unsigned i = 0; i < mAllJoints.size(); i ++) {
		Joint* joint = mAllJoints[i];
		if (joint->parentName.empty()) {
			mJoints.push_back(joint);
		} else {
			for (unsigned j = 0; j < mAllJoints.size(); j ++) {
				Joint* jt = mAllJoints[j];
				if (jt != joint && jt->name == joint->parentName) {
					jt->children.push_back(joint);
					joint->parent = jt;
					break;
				}
			}
		}
	}
	buildTransforms();

//	skinMesh();
}

void SkinnedMesh::buildTransforms(Joint* joint) {
	if (joint == nullptr) {
		for (unsigned i = 0; i < mJoints.size(); i ++) {
			buildTransforms(mJoints[i]);
		}
	} else {

		if (joint->parent != nullptr) {
			joint->absoluteTransform = joint->parent->absoluteTransform;
			joint->absoluteTransform *= joint->transform;
		} else {
			joint->absoluteTransform = joint->transform;
		}
		joint->absoluteTransformInverse.loadInverse(joint->absoluteTransform);
		for (unsigned i = 0; i < joint->children.size(); i ++) {
			buildTransforms(joint->children[i]);
		}
	}
}

void SkinnedMesh::buildAnimationTransforms(float frame, Joint* joint) {
	if (joint == nullptr) {
		for (unsigned i = 0; i < mJoints.size(); i ++) {
			buildAnimationTransforms(frame, mJoints[i]);
		}
	} else {
		graphic::vec3 position = joint->position;
		graphic::vec3 scale = joint->scale;
		graphic::quat4 rotation = joint->rotation;

		for (unsigned i = 0; i < joint->positionKeyFrames.size(); i ++) {
			if (frame >= joint->positionKeyFrames[i].frame) {
				position = joint->positionKeyFrames[i].position;
			} else {
				break;
			}
		}

		for (unsigned i = 0; i < joint->scaleKeyFrames.size(); i ++) {
			if (frame >= joint->scaleKeyFrames[i].frame) {
				scale = joint->scaleKeyFrames[i].scale;
			} else {
				break;
			}
		}

		for (unsigned i = 0; i < joint->rotationKeyFrames.size(); i ++) {
			if (frame >= joint->rotationKeyFrames[i].frame) {
				rotation = joint->rotationKeyFrames[i].rotation;
			} else {
				break;
			}
		}

		joint->animationTransform.compose(position, rotation, scale);
		if (joint->parent != nullptr) {
			joint->absoluteAnimationTransform = joint->parent->absoluteAnimationTransform;
			joint->absoluteAnimationTransform *= joint->animationTransform;
		} else {
			joint->absoluteAnimationTransform = joint->animationTransform;
		}
		for (unsigned i = 0; i < joint->children.size(); i ++) {
			buildAnimationTransforms(frame, joint->children[i]);
		}
	}
}

void SkinnedMesh::skinMesh() {
	for (unsigned i = 0; i < mJoints.size(); i ++) {
		skinJoint(mJoints[i]);
	}
}

void SkinnedMesh::skinJoint(Joint* joint) {
	if (joint->parent != nullptr) {
		joint->absoluteAnimationTransform = joint->parent->absoluteAnimationTransform;
		joint->absoluteAnimationTransform *= joint->animationTransform;
	} else {
		joint->absoluteAnimationTransform = joint->animationTransform;
	}
	graphic::mat4 m = joint->absoluteAnimationTransform * joint->absoluteTransformInverse;
	graphic::vec3* positions = mGeometry->positions();
	graphic::vec3* localPositions = mLocalGeometry->positions();
	graphic::vec3 v;
	for (unsigned i = 0; i < joint->vertices.size(); i ++) {
		m.transformVector(localPositions[joint->vertices[i].vertex_id], v);
		positions[joint->vertices[i].vertex_id] = v;
//		positions[joint->vertices[i].vertex_id] = localPositions[joint->vertices[i].vertex_id];
	}

	for (unsigned i = 0; i < joint->children.size(); i ++) {
		skinJoint(joint->children[i]);
	}
}

void SkinnedMesh::updateMeshBuffer(float frame, int32_t startFrameLoop, int32_t endFrameLoop) {
	buildAnimationTransforms(frame);
	skinMesh();
}

} /* namespace scene */
} /* namespace pola */
