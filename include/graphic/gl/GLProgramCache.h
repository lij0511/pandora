/*
 * ProgramCache.h
 *
 *  Created on: 2016年3月30日
 *      Author: lijing
 */

#ifndef GLPROGRAMCACHE_H_
#define GLPROGRAMCACHE_H_

#include <string.h>

#include "utils/String.h"
#include "utils/LruCache.h"
#include "graphic/gl/GLProgram.h"

namespace pola {
namespace graphic {
class GLShader;

class ProgramDescription {
public:
	ProgramDescription(const utils::String& vertexShader, const utils::String& fragmentShader, utils::hash_t hash);

	bool operator==(const ProgramDescription& other) const {
		return mVertexShader == other.mVertexShader && mFragmentShader == other.mFragmentShader;
	};

	bool operator!=(const ProgramDescription& other) const {
		return *this != other;
	};

	utils::hash_t hash() const;

	const utils::String mVertexShader;
	const utils::String mFragmentShader;

	mutable utils::hash_t mHash;
};

class GLProgramCache : public utils::OnEntryRemoved<const ProgramDescription, GLProgram*>{
public:
	GLProgramCache();
	virtual ~GLProgramCache();

	GLProgram* get(GLShader* shader);

	virtual void operator()(const ProgramDescription& key, GLProgram*& value);

private:
	utils::LruCache<const ProgramDescription, GLProgram*> mCache;
};

inline utils::hash_t hash_type(const graphic::ProgramDescription& key) {
	return key.hash();
}

}
}

#endif /* GLPROGRAMCACHE_H_ */
