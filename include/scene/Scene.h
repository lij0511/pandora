/*
 * Scene.h
 *
 *  Created on: 2016年5月19日
 *      Author: lijing
 */

#ifndef POLA_SCENE_H_
#define POLA_SCENE_H_

#include <stdint.h>

#include "graphic/GraphicContext.h"
#include "scene/Environment.h"

namespace pola {
namespace scene {

class Scene {
public:
	Scene(graphic::GraphicContext* graphic);
	virtual ~Scene();

	virtual void setViewport(int32_t width, int32_t height);

	int32_t getWidth() const;
	int32_t getHeight() const;

	graphic::GraphicContext* graphic() const;

	Environment* environment();

private:
	graphic::GraphicContext* m_graphic;
	int32_t m_width;
	int32_t m_height;

	Environment m_environment;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_SCENE_H_ */
