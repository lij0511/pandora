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

class ProgramDescription {
public:
	ProgramDescription(const char* material_type);

	bool operator==(const ProgramDescription& other) const;

	bool operator!=(const ProgramDescription& other) const {
		return *this != other;
	};

	utils::hash_t hash() const;

	utils::String mVertexShader;
	utils::String mFragmentShader;

	const char* material_type;
	bool lighting = false;

};

class GLProgramCache : public utils::OnEntryRemoved<const ProgramDescription, GLProgram*>{
public:
	GLProgramCache();
	virtual ~GLProgramCache();

	GLProgram* get(const ProgramDescription& description);
	void cache(const ProgramDescription& description, GLProgram* program);

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
