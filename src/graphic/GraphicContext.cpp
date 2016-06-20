/*
 * GraphicContext.cpp
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#include "graphic/GraphicContext.h"
#include "graphic/Material.h"
#include "io/FileInputStream.h"

namespace pola {
namespace graphic {

GraphicContext::GraphicContext() : mWidth(0), mHeight(0) {
	mLights = nullptr;
	mDefaultMaterial = new Material;
}

GraphicContext::~GraphicContext() {
	delete mDefaultMaterial;
}

void GraphicContext::setViewport(int32_t width, int32_t height) {
	mWidth = width;
	mHeight = height;
}

Texture* GraphicContext::loadTexture(const char* file) {
	io::FileInputStream is(file);
	return loadTexture(&is);
}
Texture* GraphicContext::loadTexture(io::InputStream* is) {
	return doLoadTexture(is);
}

void GraphicContext::beginFrame(const FColor4& clearColor) {
}

void GraphicContext::endFrame() {
}

void GraphicContext::setLights(Lights* lights) {
	mLights = lights;
}

Lights* GraphicContext::lights() const {
	return mLights;
}

void GraphicContext::setMatrix(MatrixType type, const mat4& matrix) {
	switch (type) {
		case VIEW:
			mView = matrix;
			break;
		case WORLD:
			mWorld = matrix;
			break;
		case PROJECTION:
			mProjection = matrix;
			break;
		default:
			break;
	}
}

} /* namespace graphic */
} /* namespace pola */
