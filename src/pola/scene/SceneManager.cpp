/*
 * SceneManager.cpp
 *
 *  Created on: 2016年5月30日
 *      Author: lijing
 */

#include "pola/scene/SceneManager.h"

namespace pola {
namespace scene {

SceneManager::SceneManager(graphic::GraphicContext* graphic) {
	mActiveScene = new Scene(graphic);
}

SceneManager::~SceneManager() {
}

Scene* SceneManager::getActiveScene() const {
	return mActiveScene;
}

void SceneManager::switchScene(Scene* scene) {
	// TODO
}

} /* namespace scene */
} /* namespace pola */
