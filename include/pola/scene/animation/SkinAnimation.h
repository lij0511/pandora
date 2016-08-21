/*
 * SkinAnimation.h
 *
 *  Created on: 2016年8月20日
 *      Author: lijing
 */

#ifndef POLA_SKINANIMATION_H_
#define POLA_SKINANIMATION_H_

#include "pola/scene/animation/Animation.h"

namespace pola {
namespace scene {

/*
 *
 */
class SkinAnimation: public Animation {
public:
	SkinAnimation(const std::string& name);
	virtual ~SkinAnimation();
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_SKINANIMATION_H_ */
