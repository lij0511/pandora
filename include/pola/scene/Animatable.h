/*
 * Animatable.h
 *
 *  Created on: 2016年8月18日
 *      Author: lijing
 */

#ifndef POLA_ANIMATABLE_H_
#define POLA_ANIMATABLE_H_

#include "pola/utils/Times.h"

namespace pola {
namespace scene {

/*
 *
 */
class Animatable {
public:
	virtual ~Animatable() {};

	virtual bool animate(p_nsecs_t timeMs) = 0;
};

} /* namespace scene */
} /* namespace pola */

#endif /* ANIMATABLE_H_ */
