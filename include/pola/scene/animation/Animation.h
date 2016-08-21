/*
 * Animation.h
 *
 *  Created on: 2016年8月18日
 *      Author: lijing
 */

#ifndef POLA_ANIMATION_H_
#define POLA_ANIMATION_H_

#include "pola/utils/Times.h"
#include "pola/utils/RefBase.h"

#include <string>

namespace pola {
namespace scene {

/*
 *
 */
class Animation : public pola::utils::RefBase<Animation> {
public:
	Animation(const std::string& name);
	virtual ~Animation();

	const std::string& name() const;

	float getFramesPerSecond() const;
	void setFramesPerSecond(float fps);

	virtual uint16_t getFrameCount() const = 0;

private:
	std::string mName;
	float mFramesPerSecond;
};

inline Animation::Animation(const std::string& name) : mName(name), mFramesPerSecond(25.f) {
}
inline Animation::~Animation() {
}

inline const std::string& Animation::name() const {
	return mName;
}

inline float Animation::getFramesPerSecond() const {
	return mFramesPerSecond;
}
inline void Animation::setFramesPerSecond(float fps) {
	mFramesPerSecond = fps;
}

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_ANIMATION_H_ */
