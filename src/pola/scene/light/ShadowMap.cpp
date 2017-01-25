/*
 * ShadowMap.cpp
 *
 *  Created on: 2016年8月4日
 *      Author: lijing
 */

#include "pola/scene/light/ShadowMap.h"
#include "pola/scene/Scene.h"

namespace pola {
namespace scene {

ShadowMap::ShadowMap(Scene* scene) : mScene(scene) {
}

ShadowMap::~ShadowMap() {
}

ShadowMap& ShadowMap::operator=(const ShadowMap& other) {
	return *this;
}
ShadowMap::ShadowMap(const ShadowMap& other) {
	mScene = nullptr;
}

void ShadowMap::render(graphic::GraphicContext* graphic, const std::vector<LightNode*>& lightNodes, p_nsecs_t timeMs) {
	graphic->setLights(nullptr);

	Environment* environment = mScene->environment();
	environment->lights()->clear();

	for (unsigned index = 0; index < lightNodes.size(); index ++) {
		environment->addLight(lightNodes[index]->light());
		renderShadowMap(graphic, lightNodes[index], timeMs);
	}

	graphic->setRenderTarget(nullptr);
}

void ShadowMap::renderShadowMap(graphic::GraphicContext* graphic, LightNode* lightNode, p_nsecs_t timeMs) {
	graphic::Light* light = lightNode->light();
	if (!light->lightOn() || !light->castShadow) {
		return;
	}
	Camera* shadowCamera = lightNode->shadowCamera();
	if (light->map == nullptr) {
		light->map = graphic->createRenderTarget(light->mapSize.width, light->mapSize.height);
	}
	graphic->setRenderTarget(light->map);
	graphic->clear({1.f, 1.f, 1.f, 1.f});

	graphic::vec3 pos;
	pos.setFromMatrixPosition(lightNode->getWorldTransform().data);
	shadowCamera->setPosition(pos);
	if (light->isDirectionalLight()) {
		shadowCamera->lookAt(pos + ((graphic::DirectionalLight*) light)->direction);
	} else if (light->isSpotLight()) {

	}
	shadowCamera->update(graphic, timeMs);

	static float m[] = {0.5f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.5f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.5f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f};
	light->matrix.load(m);
	light->matrix.multiply(graphic->getMatrix(graphic::GraphicContext::PROJECTION));
	light->matrix.multiply(graphic->getMatrix(graphic::GraphicContext::VIEW));


	projectNodes(lightNode->shadowCamera(), mScene);

	for (unsigned i = 0; i < mViewableNodes.size(); i ++) {
		graphic->setMatrix(graphic::GraphicContext::MODEL, mViewableNodes[i]->getWorldTransform());
		mViewableNodes[i]->update(timeMs);
		mViewableNodes[i]->render(graphic, &mShadowMapMaterial, timeMs);
	}

	mViewableNodes.clear();
}

void ShadowMap::projectNodes(Camera* shadowCamera, SceneNode* node) {
	if (node == nullptr) {
		return;
	}
	if (node != nullptr && node->viewable(shadowCamera->frustum())) {
		mViewableNodes.push_back(node);
	}
	for (unsigned i = 0; i < node->getChildCount(); i ++) {
		projectNodes(shadowCamera, node->getChild(i));
	}
}

} /* namespace scene */
} /* namespace pola */
