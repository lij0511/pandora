/*
 * SceneManager.h
 *
 *  Created on: 2016年5月30日
 *      Author: lijing
 */

#ifndef POLA_SCENEMANAGER_H_
#define POLA_SCENEMANAGER_H_

#include "utils/Vector.h"
#include "scene/Scene.h"
#include "graphic/GraphicContext.h"

namespace pola {
namespace scene {

class SceneManager {
public:
	SceneManager(graphic::GraphicContext* graphic);
	virtual ~SceneManager();

	Scene* getActiveScene() const;

	void switchScene(Scene* scene);

private:
	Scene* mActiveScene;
	utils::Vector<Scene*> mHistroyScenes;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_SCENEMANAGER_H_ */
