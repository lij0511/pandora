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
#include "scene/node/BasicMeshSceneNode.h"
#include "graphic/gl/GLCaches.h"
#include "graphic/gl/GLTexture.h"
#include "graphic/material/BasicMaterial.h"
#include "graphic/material/TMaterial.h"
#include "graphic/material/TPhongMaterial.h"
#include "utils/Math.h"

using namespace pola;
using namespace pola::utils;
using namespace pola::scene;
using namespace pola::graphic;

int main(int argc, char *argv[]) {

	DeviceParam param = {500, 500, false, 16};
	Device* device = createDevice(param);

	 Scene* scene = device->getSceneManager()->getActiveScene();
	 scene->setClearColor({0.4f, 0.4f, 0.6f, 1.f});
	MD2AnimatedMesh* mesh = (MD2AnimatedMesh*) MeshLoader::loadMesh("./res/faerie.md2");
	GLTexture* texture = (GLTexture*) scene->graphic()->loadTexture("./res/faerie2.bmp");
	MD2AnimatedMesh* mesh2 = (MD2AnimatedMesh*) MeshLoader::loadMesh("./res/sydney.md2");
	GLTexture* texture2 = (GLTexture*) scene->graphic()->loadTexture("./res/sydney.bmp");
	scene->environment()->addLight(new DirectionalLight({- 1.f, 0.f, 1.f}, {1.0f, 1.0f, 1.0f}));

	Material* m1 = new BasicMaterial({0.f, 0.f, 1.f});
	Material* m2 = new BasicMaterial({1.f, 0.f, 0.f});
	Material* tm1 = texture ? new TPhongMaterial(texture) : nullptr;
	Material* tm2 = texture2 ? new TPhongMaterial(texture2) : nullptr;

	BasicMesh* basicMesh = (BasicMesh*) MeshLoader::loadMesh("./res/tree.obj");
	if (mesh) {
		for (int i = 0; i < 500; i ++) {
			MD2AnimatedMeshSceneNode* node = new MD2AnimatedMeshSceneNode(mesh);
			node->setPosition(graphic::vec3(random(-500, 500), random(-500, 500), random(-500, 500)));
			node->setMaterial(tm1);
			int ani = random(0, MD2_AT_COUNT + 3);
			if (ani < MD2_AT_COUNT) {
				node->setAnimationType((MD2_ANIMATION_TYPE) ani);
			}
			scene->addSceneNode(node);
		}
	}
	if (mesh2) {
		for (int i = 0; i < 100; i ++) {
			MD2AnimatedMeshSceneNode* node = new MD2AnimatedMeshSceneNode(mesh2);
			node->setMaterial(tm2);
			node->setPosition(graphic::vec3(random(-500, 500), random(-500, 500), random(-500, 500)));
			int ani = random(0, MD2_AT_COUNT + 3);
			if (ani < MD2_AT_COUNT) {
				node->setAnimationType((MD2_ANIMATION_TYPE) ani);
			}
			scene->addSceneNode(node);
		}
	}
	if (basicMesh) {
		for (int i = 0; i < 100; i ++) {
			BasicMeshSceneNode* node = new BasicMeshSceneNode(basicMesh);
			node->setMaterial(m1);
			node->setPosition(graphic::vec3(random(-500, 500), random(-500, 500), random(-500, 500)));
			node->setScale({80, 80, 80});
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


