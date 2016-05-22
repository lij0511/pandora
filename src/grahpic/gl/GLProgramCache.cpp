/*
 * ProgramCache.cpp
 *
 *  Created on: 2016年3月30日
 *      Author: lijing
 */

#include "graphic/gl/GLProgramCache.h"
#include "graphic/gl/GLShader.h"

#include "utils/JenkinsHash.h"

namespace pola {
namespace graphic {

ProgramDescription::ProgramDescription(const utils::String& vertexShader, const utils::String& fragmentShader, utils::hash_t hash) :
	mVertexShader(vertexShader), mFragmentShader(fragmentShader), mHash(hash) {
}

utils::hash_t ProgramDescription::hash() const {
	utils::hash_t hash = mHash;
	if (hash == 0) {
		size_t vlen = mVertexShader.length();
		size_t flen = mFragmentShader.length();
		if (vlen <= 0 && flen <= 0) return 0;
		const char* vertexShader = mVertexShader.characters();
		while (vlen --) {
			hash = utils::JenkinsHashMix(hash, *vertexShader);
			vertexShader ++;
		}
		const char* fragmentShader = mFragmentShader.characters();
		while (flen --) {
			hash = utils::JenkinsHashMix(hash, *fragmentShader);
			fragmentShader ++;
		}
		hash = utils::JenkinsHashWhiten(hash);
		mHash = hash;
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

GLProgram* GLProgramCache::get(GLShader* shader) {
	ProgramDescription description(shader->getVertexShader(), shader->getFragmentShader(), shader->hash());
	GLProgram* program = mCache.get(description);
	if (!program) {
		program = new GLProgram(description.mVertexShader.characters(), description.mFragmentShader.characters());
		mCache.put(description, program);
	}
	return program;
}

}
}
