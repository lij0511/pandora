/*
 * Scene.cpp
 *
 *  Created on: 2016年5月19日
 *      Author: lijing
 */

#include "pola/scene/Scene.h"
#include "pola/scene/FPS.h"
#include "pola/scene/node/MeshSceneNode.h"
#include "pola/utils/Times.h"

// TODO
#include "pola/graphic/gl/GLRenderTarget.h"
#include "pola/graphic/gl/GLTexture.h"
#include "pola/graphic/geometries/RectangleGeometry.h"

namespace pola {
namespace scene {

Scene::Scene(graphic::GraphicContext* graphic) : mGraphic(graphic), mWidth(0), mHeight(0), mEnvironment(), mShadowMap(this) {
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
	}
}

int32_t Scene::getWidth() const {
	return mWidth;
}

int32_t Scene::getHeight() const {
	return mHeight;
}

void Scene::setClearColor(graphic::FColor4 color) {
	mClearColor = color;
}

void Scene::addCamera(Camera* camera) {
	// TODO
	if (mCurrentCamera != nullptr) {
		delete mCurrentCamera;
	}
	mCurrentCamera = camera;
	mCurrentCamera->setSize(mWidth, mHeight);
}

Camera* Scene::getCurrentCamera() const {
	return mCurrentCamera;
}

void Scene::render() {
	mGraphic->beginFrame(mClearColor);
	p_nsecs_t timeMs = uptimeMillis();
	if (mCurrentCamera != nullptr) {
		mCurrentCamera->update(mGraphic, timeMs);
	}

	/* Project RenderNodes */
	projectNodes(this);

	mShadowMap.render(mGraphic, mLightNodes, timeMs);

	if (mCurrentCamera != nullptr) {
		mCurrentCamera->requestPropertyChange();
		mCurrentCamera->update(mGraphic, timeMs);
	}

	mGraphic->setLights(mEnvironment.lights());
	for (unsigned i = 0; i < mViewableNodes.size(); i ++) {
		mGraphic->setMatrix(graphic::GraphicContext::MODEL, mViewableNodes[i]->getWorldTransform());
		mViewableNodes[i]->update(timeMs);
		mGraphic->renderGeometry(mViewableNodes[i]->mesh()->geometry(), mViewableNodes[i]->material());
	}

	// TODO ShadowMap debug
	static graphic::RectangleGeometry r(0, 0, 512, 512);
	SceneNode node;
	node.setPosition({- 200, - 200, -300});
	if (mLightNodes.size() > 0 && mLightNodes[0]->light()->map != nullptr) {
		mGraphic->setMatrix(graphic::GraphicContext::MODEL, node.getWorldTransform());
		graphic::GLTexture* t = ((graphic::GLRenderTarget*)mLightNodes[0]->light()->map)->getTexture();
		graphic::Material m({1.f, 1.f, 1.f, 1.f}, t);
		mGraphic->renderGeometry(&r, &m);
	}
	// TODO

	mLightNodes.clear();
	mViewableNodes.clear();

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

bool Scene::dispatchMouseEvent(input::MouseEvent& mouseEvent) {
	if (mCurrentCamera != nullptr && mCurrentCamera->dispatchMouseEvent(mouseEvent)) {
		return true;
	}
	return false;
}

void Scene::projectNodes(SceneObject* node) {
	if (mCurrentCamera == nullptr || node == nullptr) {
		return;
	}
	MeshSceneNode* m = dynamic_cast<MeshSceneNode*>(node);
	if (m != nullptr) {
		graphic::Box3 boundingBox =  m->mesh()->geometry()->getBoundingBox();
		boundingBox.applyMatrix(m->getWorldTransform());
		if (mCurrentCamera->frustum().intersectsBox(boundingBox)) {
			mViewableNodes.push_back(m);
		}
	} else {
		node->updateTransform();
		LightNode* light = dynamic_cast<LightNode*>(node);
		if (light != nullptr) {
			mLightNodes.push_back(light);
		}
	}
	for (unsigned i = 0; i < node->getChildCount(); i ++) {
		projectNodes(node->getChild(i));
	}
}

} /* namespace scene */
} /* namespace pola */
