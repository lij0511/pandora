/*
 * ProgramCache.cpp
 *
 *  Created on: 2016年3月30日
 *      Author: lijing
 */

#include "graphic/gl/GLProgramCache.h"
#include "graphic/gl/DefaultGLShader.h"

#include "utils/JenkinsHash.h"

#include "log/Log.h"

namespace pola {
namespace graphic {

ProgramDescription::ProgramDescription(const utils::String& vertexShader, const utils::String& fragmentShader) :
	mVertexShader(vertexShader), mFragmentShader(fragmentShader), mShader(nullptr) {
	if (vertexShader.isEmpty() || fragmentShader.isEmpty()) {
		LOG_ALWAYS_FATAL("VertexShader or FragmengShader is NULL. Fix Me!\n");
	}
}

ProgramDescription::ProgramDescription(DefaultGLShader* shader) : mShader(shader) {
}

bool ProgramDescription::operator==(const ProgramDescription& other) const {
	if ((mShader != nullptr && other.mShader == nullptr) || (mShader == nullptr && other.mShader != nullptr)) {
		return false;
	}
	if (mShader != nullptr) {
		bool comp = texture0 == other.texture0;
		// TODO
		return comp;
	} else {
		return mVertexShader == other.mVertexShader && mFragmentShader == other.mFragmentShader;
	}
};

utils::hash_t ProgramDescription::hash() const {
	utils::hash_t hash = 0;
	if (mShader != nullptr) {
		hash = utils::JenkinsHashMix(hash, texture0);
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
		if (description.mShader != nullptr) {
			program = new GLProgram(description.mShader->getVertexShader().characters(), description.mShader->getFragmentShader().characters());
		} else {
			program = new GLProgram(description.mVertexShader.characters(), description.mFragmentShader.characters());
		}
		mCache.put(description, program);
	}
	return program;
}

}
}
