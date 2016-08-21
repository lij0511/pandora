/*
 * FrameAnimation.h
 *
 *  Created on: 2016年8月18日
 *      Author: lijing
 */

#ifndef POLA_FRAMEANIMATION_H_
#define POLA_FRAMEANIMATION_H_

#include "pola/scene/animation/Animation.h"
#include "pola/graphic/math/Vector.h"

#include <vector>

namespace pola {
namespace scene {

/*
 *
 */
class FrameAnimation: public Animation {
public:
	FrameAnimation(const std::string& name);
	virtual ~FrameAnimation();

	virtual uint16_t getFrameCount() const;

	std::vector<graphic::vec3>& positions();
	std::vector<graphic::vec3>& normals();
	std::vector<graphic::vec2>& uvs();

private:
	std::vector<graphic::vec3> mPositions;
	std::vector<graphic::vec3> mNormals;
	std::vector<graphic::vec2> mUvs;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_FRAMEANIMATION_H_ */
