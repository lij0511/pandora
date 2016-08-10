/*
 * SceneManager.h
 *
 *  Created on: 2016年5月30日
 *      Author: lijing
 */

#ifndef POLA_SCENEMANAGER_H_
#define POLA_SCENEMANAGER_H_

#include "pola/utils/Vector.h"
#include "pola/scene/Scene.h"
#include "pola/graphic/GraphicContext.h"

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
	std::vector<Scene*> mHistroyScenes;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_SCENEMANAGER_H_ */
