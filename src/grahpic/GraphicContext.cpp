/*
 * GraphicContext.cpp
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#include "graphic/GraphicContext.h"

namespace pola {
namespace graphic {

GraphicContext::GraphicContext() : m_width(0), m_height(0) {
}

GraphicContext::~GraphicContext() {
}

void GraphicContext::setViewport(int32_t width, int32_t height) {
	m_width = width;
	m_height = height;
}

void GraphicContext::setCurrentCamera(const mat4& projection, const mat4& view) {
	m_projection = projection;
	m_view = view;
}

} /* namespace graphic */
} /* namespace pola */
