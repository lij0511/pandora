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

class Mesh;

/*
 *
 */
class Animation : public pola::utils::RefBase<Animation> {
public:
	template<typename T>
	struct KeyFrame {
		float frameTime;
		T frameData;
	};

	Animation(const std::string& name);
	virtual ~Animation();

	const std::string& name() const;

	virtual uint16_t getFrameCount() const = 0;

	virtual void applyFrame(float frameTime, pola::scene::Mesh* mesh) = 0;

	float getDuration() const;

protected:
	std::string mName;
	float mDuration;
};

inline Animation::Animation(const std::string& name) : mName(name), mDuration(0.f) {
}
inline Animation::~Animation() {
}

inline const std::string& Animation::name() const {
	return mName;
}

inline float Animation::getDuration() const {
	return mDuration;
}

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_ANIMATION_H_ */
