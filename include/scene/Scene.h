/*
 * Scene.h
 *
 *  Created on: 2016年5月19日
 *      Author: lijing
 */

#ifndef POLA_SCENE_H_
#define POLA_SCENE_H_

namespace pola {
namespace scene {

#include <stdint.h>

class Scene {
public:
	Scene();
	virtual ~Scene();

	virtual void setViewport(int32_t width, int32_t height);

private:
	int32_t m_width;
	int32_t m_height;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_SCENE_H_ */
