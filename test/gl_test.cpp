/*
 * gltest1.cpp
 *
 *  Created on: 2015年12月10日
 *      Author: lijing
 */

#include "scene/camera/PerspectiveCamera.h"
#include "scene/camera/FPSCameraController.h"
#include "Device.h"
#include "io/FileInputStream.h"
#include "scene/mesh/MeshLoader.h"
#include "scene/mesh/MD2AnimatedMesh.h"
#include "scene/node/MD2AnimatedMeshSceneNode.h"
#include "graphic/gl/GLCaches.h"
#include "graphic/gl/GLTexture.h"
#include "utils/Math.h"

using namespace pola;
using namespace pola::utils;
using namespace pola::scene;
using namespace pola::graphic;

int main(int argc, char *argv[]) {

	DeviceParam param = {500, 500, false, 16};
	Device* device = createDevice(param);

	 Scene* scene = device->getSceneManager()->getActiveScene();
	MD2AnimatedMesh* mesh = (MD2AnimatedMesh*) MeshLoader::loadMesh("./res/faerie.md2");
	GLTexture* texture = (GLTexture*) scene->graphic()->loadTexture("./res/faerie2.bmp");
	MD2AnimatedMesh* mesh2 = (MD2AnimatedMesh*) MeshLoader::loadMesh("./res/sydney.md2");
	GLTexture* texture2 = (GLTexture*) scene->graphic()->loadTexture("./res/sydney.bmp");
	if (mesh) {
		for (int i = 0; i < 150; i ++) {
			MD2AnimatedMeshSceneNode* node = new MD2AnimatedMeshSceneNode(mesh);
			node->setMaterialTexture(0, texture);
			node->setPosition(graphic::vec3(random(-500, 500), random(-500, 500), random(-500, 500)));
			scene->addSceneNode(node);
		}
	}
	if (mesh) {
		for (int i = 0; i < 150; i ++) {
			MD2AnimatedMeshSceneNode* node = new MD2AnimatedMeshSceneNode(mesh2);
			node->setMaterialTexture(0, texture2);
			node->setPosition(graphic::vec3(random(-500, 500), random(-500, 500), random(-500, 500)));
			scene->addSceneNode(node);
		}
	}

//	scene->addCamera(new PerspectiveCameraFPS({0, 0, 1}, {0, 0, 0}));
	Camera* camera = new PerspectiveCamera();
	camera->setCameraController(new FPSCameraController(camera));
//	camera->setPosition(vec3(0, 0, -100));
	scene->addCamera(camera);

	device->run();
	return 1;
}


