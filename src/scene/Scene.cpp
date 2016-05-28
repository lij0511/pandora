/*
 * Scene.cpp
 *
 *  Created on: 2016年5月19日
 *      Author: lijing
 */

#include "scene/Scene.h"

namespace pola {
namespace scene {

Scene::Scene(graphic::GraphicContext* graphic) : m_graphic(graphic), m_width(0), m_height(0) {
}

Scene::~Scene() {
}

void Scene::setViewport(int32_t width, int32_t height) {
	m_width = width;
	m_height = height;
	m_graphic->setViewport(width, height);
}

int32_t Scene::getWidth() const {
	return m_width;
}

int32_t Scene::getHeight() const {
	return m_height;
}

graphic::GraphicContext* Scene::graphic() const {
	return m_graphic;
}

Environment* Scene::environment() {
	return &m_environment;
}

} /* namespace scene */
} /* namespace pola */
