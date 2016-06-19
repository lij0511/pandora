/*
 * ProgramCache.cpp
 *
 *  Created on: 2016年3月30日
 *      Author: lijing
 */

#include "graphic/gl/GLProgramCache.h"

#include "utils/JenkinsHash.h"

#include "log/Log.h"

namespace pola {
namespace graphic {

ProgramDescription::ProgramDescription(const char* type) : material_type(type) {
}

bool ProgramDescription::operator==(const ProgramDescription& other) const {
	if (material_type != other.material_type) {
		return false;
	}
	bool comp = true;
	comp &= lights.directionalLightCount() == other.lights.directionalLightCount();
	comp &= lights.pointLightCount() == other.lights.pointLightCount();
	comp &= lights.spotLightCount() == other.lights.spotLightCount();
	// TODO
	if (material_type == nullptr) {
		comp &= (mVertexShader == other.mVertexShader && mFragmentShader == other.mFragmentShader);
		return mVertexShader == other.mVertexShader && mFragmentShader == other.mFragmentShader;
	}
	return comp;
};

utils::hash_t ProgramDescription::hash() const {
	utils::hash_t hash = 0;
	if (material_type != nullptr) {
		hash = utils::hash_type(material_type);
	} else {
		hash = utils::JenkinsHashMix(hash, mVertexShader.hash());
		hash = utils::JenkinsHashMix(hash, mFragmentShader.hash());
	}
	hash = utils::JenkinsHashMix(hash, lights.hash());
	// TODO
	hash = utils::JenkinsHashWhiten(hash);
	return hash;
}

GLProgramCache::GLProgramCache() :
	mCache(300) {
}

GLProgramCache::~GLProgramCache() {
}

void GLProgramCache::operator()(const ProgramDescription& key, GLProgram*& value) {
	if (value) {
		delete value;
	}
}

GLProgram* GLProgramCache::get(const ProgramDescription& description) {
	return mCache.get(description);
}

void GLProgramCache::cache(const ProgramDescription& description, GLProgram* program) {
	mCache.put(description, program);
}

}
}
