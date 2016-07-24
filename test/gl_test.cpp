/*
 * gltest1.cpp
 *
 *  Created on: 2015年12月10日
 *      Author: lijing
 */

#include "pola/scene/camera/OrthoCamera.h"
#include "pola/scene/camera/PerspectiveCamera.h"
#include "pola/scene/camera/DefaultCameraController.h"
#include "pola/scene/camera/FPSCameraController.h"
#include "pola/Device.h"
#include "pola/io/FileInputStream.h"
#include "pola/scene/mesh/MeshLoader.h"
#include "pola/scene/mesh/MD2AnimatedMesh.h"
#include "pola/scene/node/MD2AnimatedMeshSceneNode.h"
#include "pola/scene/node/BasicMeshSceneNode.h"
#include "pola/graphic/gl/GLCaches.h"
#include "pola/graphic/gl/GLTexture.h"
#include "pola/graphic/material/LambertMaterial.h"
#include "pola/graphic/material/PhongMaterial.h"
#include "pola/utils/Math.h"
#include "pola/graphic/geometries/SphereGeometry.h"
#include "pola/graphic/geometries/CubeGeometry.h"
#include "pola/graphic/geometries/RectangleGeometry.h"

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
	DirectionalLight* light = new DirectionalLight({- 1.f, 0.f, 0.f}, {1.f, 1.f, 1.f});
	scene->environment()->addLight(light);
	scene->environment()->setAmbientLight({0.2f, 0.2f, 0.2f});
//	scene->environment()->addLight(new DirectionalLight({1.f, 0.f, 0.f}, {1.f, 1.f, 1.f}));

	Material* m1 = new LambertMaterial({1.f, 0.f, 0.f});
	Material* m2 = new PhongMaterial({1.f, 0.f, 0.f});
	Material* tm1 = new LambertMaterial({1.0f, 1.0f, 1.0f}, texture);
	Material* tm2 = new PhongMaterial({1.0f, 1.0f, 1.0f}, texture2);

	BasicMesh* basicMesh = (BasicMesh*) MeshLoader::loadMesh("./res/tree.obj");
	/*int i = 0;
	while (i < 30) {
		if (basicMesh != nullptr) {
			delete basicMesh;
		}
		basicMesh = (BasicMesh*) MeshLoader::loadMesh("./res/tree.obj");
		i ++;
	}*/
	if (mesh) {
		for (int i = 0; i < 100; i ++) {
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

	BasicMesh* m = new BasicMesh(new SphereGeometry(30.f, 20, 20));
	for (int i = 0; i < 100; i ++) {
		BasicMeshSceneNode* node = new BasicMeshSceneNode(m);
		node->setMaterial(m1);
		node->setPosition(graphic::vec3(random(-500, 500), random(-500, 500), random(-500, 500)));
		scene->addSceneNode(node);
	}

	m = new BasicMesh(new CubeGeometry(30.f, 30.f, 30.f));
	for (int i = 0; i < 100; i ++) {
		BasicMeshSceneNode* node = new BasicMeshSceneNode(m);
		node->setMaterial(m1);
		node->setPosition(graphic::vec3(random(-500, 500), random(-500, 500), random(-500, 500)));
		scene->addSceneNode(node);
	}

//	m = new BasicMesh(new RectangleGeometry(0, 0, 100, 100));
//	BasicMeshSceneNode* node = new BasicMeshSceneNode(m);
//	node->setMaterial(tm1);
//	scene->addSceneNode(node);

//	scene->addCamera(new PerspectiveCameraFPS({0, 0, 1}, {0, 0, 0}));
	Camera* camera = new PerspectiveCamera();
//	Camera* camera = new OrthoCamera(-1, 1);
	camera->setCameraController(new DefaultCameraController(camera));
//	camera->setCameraController(new FPSCameraController(camera));
//	camera->setPosition(vec3(0, 0, -100));
	scene->addCamera(camera);

	while (device->run()) {
		scene->render();
		device->swapBuffers();
	}
	return 1;
}


