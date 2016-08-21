/*
 * Animations.h
 *
 *  Created on: 2016年8月20日
 *      Author: lijing
 */

#ifndef POLA_ANIMATIONS_H_
#define POLA_ANIMATIONS_H_

#include "pola/scene/animation/Animation.h"
#include "pola/utils/RefBase.h"

#include <vector>

namespace pola {
namespace scene {

/*
 *
 */
class Animations : public pola::utils::RefBase<Animations> {
public:
	Animations();
	virtual ~Animations();

	Animation* findAnimation(const std::string& name) const;
	void addAnimation(Animation* animation);

private:
	std::vector<Animation*> mAnimations;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_ANIMATIONS_H_ */
