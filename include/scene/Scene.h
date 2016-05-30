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
#include "scene/node/SceneNode.h"
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

	void addSceneNode(SceneNode* node);
	void removeSceneNode(SceneNode* node);

	void render();

	graphic::GraphicContext* graphic() const;

	Environment* environment();

private:
	graphic::GraphicContext* mGraphic;
	int32_t mWidth;
	int32_t mHeight;

	utils::Vector<SceneNode*> mNodes;

	Environment mEnvironment;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_SCENE_H_ */
