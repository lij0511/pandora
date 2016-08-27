/*
 * Animatable.h
 *
 *  Created on: 2016年8月18日
 *      Author: lijing
 */

#ifndef POLA_ANIMATABLE_H_
#define POLA_ANIMATABLE_H_

#include "pola/utils/Times.h"
#include "pola/log/Log.h"

namespace pola {
namespace scene {

/*
 *
 */
class Animatable {
public:
	Animatable();
	virtual ~Animatable() {};

	virtual bool animate(p_nsecs_t timeMs);

protected:
	float mDuration;
	float mCurrentFrame;
	p_nsecs_t mLastTimeMs;
};

inline Animatable::Animatable() : mDuration(0.f),
		mCurrentFrame(0.f),
		mLastTimeMs(0) {
}

inline bool Animatable::animate(p_nsecs_t timeMs) {
	if (mLastTimeMs == 0) {
		mLastTimeMs = timeMs;
	}
	p_nsecs_t interval = timeMs - mLastTimeMs;
	mLastTimeMs = timeMs;
	mCurrentFrame += interval * 1.f / 1000.f;
	if (mCurrentFrame > mDuration) {
		// TODO Loop mode?
		mCurrentFrame = 0;
	}
	return true;
}

} /* namespace scene */
} /* namespace pola */

#endif /* ANIMATABLE_H_ */
