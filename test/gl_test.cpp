/*
 * gltest1.cpp
 *
 *  Created on: 2015年12月10日
 *      Author: lijing
 */

#include "scene/camera/PerspectiveCameraFPS.h"
#include "Device.h"
#include "io/FileInputStream.h"
#include "scene/mesh/MeshLoader.h"
#include "scene/mesh/MD2AnimatedMesh.h"
#include "scene/node/MD2AnimatedMeshSceneNode.h"
#include "graphic/gl/GLCaches.h"
#include "graphic/gl/GLTexture.h"

using namespace pola;
using namespace pola::utils;
using namespace pola::scene;
using namespace pola::graphic;

int main(int argc, char *argv[]) {

	DeviceParam param = {500, 500, false, 16};
	Device* device = createDevice(param);

	 Scene* scene = device->getSceneManager()->getActiveScene();
	MD2AnimatedMesh* mesh = (MD2AnimatedMesh*) MeshLoader::loadMesh("/home/lijing/work/workspace/irrlicht-1.8.3/media/faerie.md2");
	if (mesh) {
		MD2AnimatedMeshSceneNode* node = new MD2AnimatedMeshSceneNode(mesh);
		scene->addSceneNode(node);
		node = new MD2AnimatedMeshSceneNode(mesh);
		node->setPosition({50, 0, 0});
		node->setAnimationType(MD2_AT_JUMP);
		scene->addSceneNode(node);
	}
	graphic::vec3 pos = {0, 0, 50};

	scene->addCamera(new PerspectiveCameraFPS(pos, {0, 0, 49}));

	// TODO
	GLTexture* texture = (GLTexture*) scene->graphic()->loadTexture("/home/lijing/work/workspace/irrlicht-1.8.3/media/faerie2.bmp");
	if (texture != nullptr && texture->generateTexture()) {
		graphic::GLCaches::get().bindTexture(texture->id);
	}

	device->run();
	return 1;
}


