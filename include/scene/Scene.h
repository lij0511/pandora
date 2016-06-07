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
#include "graphic/Color.h"
#include "scene/FPS.h"
#include "scene/node/SceneNode.h"
#include "scene/camera/Camera.h"
#include "scene/Environment.h"
#include "input/KeyEvent.h"
#include "input/MouseEvent.h"

namespace pola {
namespace scene {

class Scene {
public:
	Scene(graphic::GraphicContext* graphic);
	virtual ~Scene();

	virtual void setViewport(int32_t width, int32_t height);

	int32_t getWidth() const;
	int32_t getHeight() const;

	void setClearColor(graphic::FColor color);

	void addSceneNode(SceneNode* node);
	void removeSceneNode(SceneNode* node);

	void addCamera(Camera* camera);
	Camera* getCurrentCamera() const;

	void render();

	graphic::GraphicContext* graphic() const;

	Environment* environment();

	bool dispatchKeyEvent(input::KeyEvent& keyEvent);
	bool dispatchMouseEvent(input::MouseEvent& mouseEvent);

private:
	graphic::GraphicContext* mGraphic;
	int32_t mWidth;
	int32_t mHeight;
	graphic::FColor mClearColor;

	utils::Vector<SceneNode*> mNodes;

	Camera* mCurrentCamera;

	Environment mEnvironment;

	FPS fps;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_SCENE_H_ */
