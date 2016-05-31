/*
 * Scene.cpp
 *
 *  Created on: 2016年5月19日
 *      Author: lijing
 */

#include "scene/Scene.h"
#include "scene/FPS.h"
#include "utils/Times.h"

namespace pola {
namespace scene {

Scene::Scene(graphic::GraphicContext* graphic) : mGraphic(graphic), mWidth(0), mHeight(0) {
	mCurrentCamera = nullptr;
}

Scene::~Scene() {
}

void Scene::setViewport(int32_t width, int32_t height) {
	mWidth = width;
	mHeight = height;
	mGraphic->setViewport(width, height);
	if (mCurrentCamera != nullptr) {
		mCurrentCamera->setSize(width, height);
		mGraphic->setMatrix(graphic::GraphicContext::PROJECTION, mCurrentCamera->matrix());
	}
}

int32_t Scene::getWidth() const {
	return mWidth;
}

int32_t Scene::getHeight() const {
	return mHeight;
}

void Scene::addSceneNode(SceneNode* node) {
	for (unsigned i = 0; i < mNodes.size(); i ++) {
		if (mNodes[i] == node) {
			return;
		}
	}
	node->ref();
	mNodes.push(node);
}

void Scene::removeSceneNode(SceneNode* node) {
	for (unsigned i = 0; i < mNodes.size(); i ++) {
		if (mNodes[i] == node) {
			mNodes.removeAt(i);
			node->deref();
			return;
		}
	}
}

void Scene::addCamera(Camera* camera) {
	// TODO
	if (mCurrentCamera != nullptr) {
		delete mCurrentCamera;
	}
	mCurrentCamera = camera;
	mCurrentCamera->setSize(mWidth, mHeight);
	mGraphic->setMatrix(graphic::GraphicContext::PROJECTION, mCurrentCamera->matrix());
}

Camera* Scene::getCurrentCamera() const {
	return mCurrentCamera;
}

void Scene::render() {
	mGraphic->beginFrame();
	nsecs_t timeMs = uptimeMillis();
	mGraphic->setMatrix(graphic::GraphicContext::PROJECTION, mCurrentCamera->matrix());
	for (unsigned i = 0; i < mNodes.size(); i ++) {
		mGraphic->setMatrix(graphic::GraphicContext::VIEW, mNodes[i]->getTransform());
		mNodes[i]->render(mGraphic, timeMs);
	}

	mGraphic->endFrame();
	fps.fps();
}

graphic::GraphicContext* Scene::graphic() const {
	return mGraphic;
}

Environment* Scene::environment() {
	return &mEnvironment;
}

bool Scene::dispatchKeyEvent(input::KeyEvent& keyEvent) {
	if (mCurrentCamera != nullptr && mCurrentCamera->dispatchKeyEvent(keyEvent)) {
		return true;
	}
	return false;
}

} /* namespace scene */
} /* namespace pola */
