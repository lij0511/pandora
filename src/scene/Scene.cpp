/*
 * Scene.cpp
 *
 *  Created on: 2016年5月19日
 *      Author: lijing
 */

#include "scene/Scene.h"

namespace pola {
namespace scene {

Scene::Scene() : m_width(0), m_height(0) {
}

Scene::~Scene() {
}

void Scene::setViewport(int32_t width, int32_t height) {
	m_width = width;
	m_height = height;
}

} /* namespace scene */
} /* namespace pola */
