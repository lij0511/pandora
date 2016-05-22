/*
 * GLCaches.h
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#ifndef POLA_GLCACHES_H_
#define POLA_GLCACHES_H_

#include "graphic/gl/GLProgramCache.h"

namespace pola {
namespace graphic {

class GLCaches {
private:
	GLCaches();
public:
	static GLCaches& get();
	virtual ~GLCaches();

	GLProgramCache programCache;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_GLCACHES_H_ */
