/*
 * FrameAnimation.h
 *
 *  Created on: 2016年8月18日
 *      Author: lijing
 */

#ifndef POLA_FRAMEANIMATION_H_
#define POLA_FRAMEANIMATION_H_

#include "pola/graphic/math/Vector.h"
#include "pola/scene/animation/Animation.h"

#include <vector>

namespace pola {
namespace scene {

class Mesh;

/*
 *
 */
class FrameAnimation: public Animation {
public:
	struct KeyFrameData {
		std::vector<graphic::vec3> positions;
		std::vector<graphic::vec3> normals;
		std::vector<graphic::vec2> uvs;
	};

	FrameAnimation(const std::string& name);
	virtual ~FrameAnimation();

	virtual uint16_t getFrameCount() const;

	KeyFrameData& addKeyFrame(float frameTime);
	void addKeyFrame(float frameTime, const KeyFrameData& frameData);

	virtual void applyFrame(float frameTime, pola::scene::Mesh* mesh);

private:
	std::vector<KeyFrame<KeyFrameData> > mKeyFrames;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_FRAMEANIMATION_H_ */
