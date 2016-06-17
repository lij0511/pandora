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

ProgramDescription::ProgramDescription(const utils::String& vertexShader, const utils::String& fragmentShader) :
	mVertexShader(vertexShader), mFragmentShader(fragmentShader), material_type(nullptr) {
	if (vertexShader.isEmpty() || fragmentShader.isEmpty()) {
		LOG_ALWAYS_FATAL("VertexShader or FragmengShader is NULL. Fix Me!\n");
	}
}

ProgramDescription::ProgramDescription(const char* type) : material_type(type) {
}

bool ProgramDescription::operator==(const ProgramDescription& other) const {
	if ((material_type != nullptr && other.material_type == nullptr) || (material_type == nullptr && other.material_type != nullptr)) {
		return false;
	}
	if (material_type != nullptr) {
		bool comp = material_type == other.material_type;

		comp |= lighting == other.lighting;
		// TODO
		return comp;
	} else {
		return mVertexShader == other.mVertexShader && mFragmentShader == other.mFragmentShader;
	}
};

utils::hash_t ProgramDescription::hash() const {
	utils::hash_t hash = 0;
	if (material_type != nullptr) {
		hash = utils::hash_type(material_type);
		hash = utils::JenkinsHashMix(hash, lighting);
		// TODO
		hash = utils::JenkinsHashWhiten(hash);
	} else {
		hash = utils::JenkinsHashMix(hash, mVertexShader.hash());
		hash = utils::JenkinsHashMix(hash, mFragmentShader.hash());
		hash = utils::JenkinsHashWhiten(hash);
	}
	return hash;
}

GLProgramCache::GLProgramCache() :
	mCache(100) {
}

GLProgramCache::~GLProgramCache() {
}

void GLProgramCache::operator()(const ProgramDescription& key, GLProgram*& value) {
	if (value) {
		delete value;
	}
}

GLProgram* GLProgramCache::get(const ProgramDescription& description) {
	GLProgram* program = mCache.get(description);
	if (!program) {
		program = new GLProgram(description.mVertexShader.characters(), description.mFragmentShader.characters());
		mCache.put(description, program);
	}
	return program;
}

}
}
