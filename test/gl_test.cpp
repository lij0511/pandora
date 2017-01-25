/*
 * gltest1.cpp
 *
 *  Created on: 2015年12月10日
 *      Author: lijing
 */

#include "pola/graphic/ImageFactory.h"
#include "pola/scene/camera/OrthoCamera.h"
#include "pola/scene/camera/PerspectiveCamera.h"
#include "pola/scene/camera/DefaultCameraController.h"
#include "pola/scene/camera/FPSCameraController.h"
#include "pola/Device.h"
#include "pola/io/FileInputStream.h"
#include "pola/scene/mesh/MeshLoader.h"
#include "pola/scene/mesh/MD2AnimatedMesh.h"
#include "pola/scene/node/MD2MeshSceneNode.h"
#include "pola/scene/node/IMeshSceneNode.h"
#include "pola/scene/node/MeshSceneNode.h"
#include "pola/scene/mesh/BasicMesh.h"
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
	Texture* texture = scene->graphic()->loadTexture("./res/faerie2.bmp");
	Texture* texture2 = scene->graphic()->loadTexture("./res/sydney.bmp");
	DirectionalLight* dlight = new DirectionalLight({- 1.f, 0.f, 0.f}, {1.f, 1.f, 1.f});
//	dlight->castShadow = true;
	PointLight* plight = new PointLight({0.f, 0.f, 0.f}, 500, {1.f, 1.f, 1.f});

//	scene->environment()->addLight(dlight);
//	scene->environment()->addLight(plight);
//	scene->environment()->addLight(new PointLight({0.f, 0.f, 0.f}, 500, {0.f, 1.f, 0.f}));
//	scene->environment()->setAmbientLight({0.2f, 0.2f, 0.2f});
//	scene->environment()->addLight(new DirectionalLight({1.f, 0.f, 0.f}, {1.f, 1.f, 1.f}));
//	scene->addChild(new LightNode(dlight));
	scene->addChild(new LightNode(plight));
	scene->addChild(new LightNode(new PointLight({0.f, 0.f, 0.f}, 500, {1.f, 1.f, 1.f})));

	Material* m1 = new LambertMaterial({1.f, 1.f, 1.f});
	Material* m2 = new LambertMaterial({1.f, 0.f, 0.f});
	Material* tm1 = new LambertMaterial({1.0f, 1.0f, 1.0f}, texture);
	Material* tm2 = new LambertMaterial({1.0f, 1.0f, 1.0f}, texture2);

	pola::utils::sp<MeshLoader::MeshInfo> result;
	if ((result = MeshLoader::loadMesh("./res/faerie.md2")) != nullptr) {
		for (int i = 0; i < 100; i ++) {
			MeshSceneNode* node = (MeshSceneNode*) scene->addMesh(result->mesh.get(), scene);
			node->setPosition(graphic::vec3(random(-500, 500), random(-500, 500), random(-500, 500)));
			node->setMaterial(0, tm1);
			int ani = random(0, 25);
			node->setAnimation(ani);
		}
	}
	if ((result = MeshLoader::loadMesh("./res/sydney.md2")) != nullptr) {
		for (int i = 0; i < 100; i ++) {
			MeshSceneNode* node = (MeshSceneNode*) scene->addMesh(result->mesh.get(), scene);
			node->setMaterial(0, tm2);
			node->setPosition(graphic::vec3(random(-500, 500), random(-500, 500), random(-500, 500)));
			int ani = random(0, 25);
			node->setAnimation(ani);
		}
	}
	if ((result = MeshLoader::loadMesh("./res/tree.obj")) != nullptr) {
		for (int i = 0; i < 100; i ++) {
			SceneNode* node = scene->addMesh(result->mesh.get(), scene);
			node->setMaterial(0, m1);
			node->setPosition(graphic::vec3(random(-500, 500), random(-500, 500), random(-500, 500)));
			node->setScale({80, 80, 80});
		}
	}

	BasicMesh* m = new BasicMesh(new SphereGeometry(30.f, 20, 20));
	for (int i = 0; i < 100; i ++) {
		SceneNode* node = scene->addMesh(m, scene);
		node->setMaterial(0, m1);
		node->setPosition(graphic::vec3(random(-500, 500), random(-500, 500), random(-500, 500)));
	}

	m = new BasicMesh(new CubeGeometry(30.f, 30.f, 30.f));
	for (int i = 0; i < 100; i ++) {
		SceneNode* node = scene->addMesh(m, scene);
		node->setMaterial(0, m1);
		node->setPosition(graphic::vec3(random(-500, 500), random(-500, 500), random(-500, 500)));
		scene->addChild(node);
	}

//	scene->addCamera(new PerspectiveCameraFPS({0, 0, 1}, {0, 0, 0}));
	Camera* camera = new PerspectiveCamera();
//	Camera* camera = new OrthoCamera(-1, 1);
	camera->setCameraController(new DefaultCameraController(camera));
//	camera->setCameraController(new FPSCameraController(camera));
//	camera->setPosition(vec3(0, 0, -100));
	scene->addCamera(camera);

	BasicMesh* light = new BasicMesh(new SphereGeometry(5.f, 4, 4));
	SceneNode* lightNode = scene->addMesh(light, scene);
	lightNode->setMaterial(0, new Material({1.f, 1.f, 1.f, 1.f}));

	int x = 0;
	while (device->run()) {
		plight->position = {float(- x), 0.f, - 300};
		lightNode->setPosition({float(- x), 0.f, - 300});
		scene->render();
		device->swapBuffers();
		if (++x > 500) {
			x = -500;
		}
	}
	return 1;
}


