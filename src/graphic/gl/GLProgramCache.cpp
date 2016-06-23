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

ProgramDescription::ProgramDescription(const char* type)
	: material_type(type), texture_map(false),
	  directional_light_count(0), point_light_count(0), spot_light_count(0),
	  fog(false) {
}

bool ProgramDescription::operator==(const ProgramDescription& other) const {
	if (material_type != other.material_type) {
		return false;
	}
	if (texture_map != other.texture_map) {
		return false;
	}
	bool comp = true;
	comp &= directional_light_count == other.directional_light_count;
	comp &= point_light_count == other.point_light_count;
	comp &= spot_light_count == other.spot_light_count;
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
	hash = utils::JenkinsHashMix(hash, utils::hash_type(texture_map));
	hash = utils::JenkinsHashMix(hash, directional_light_count);
	hash = utils::JenkinsHashMix(hash, point_light_count);
	hash = utils::JenkinsHashMix(hash, spot_light_count);
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
