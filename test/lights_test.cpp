/*
 * gltest1.cpp
 *
 *  Created on: 2015年12月10日
 *      Author: lijing
 */

#include "scene/camera/PerspectiveCamera.h"
#include "scene/camera/DefaultCameraController.h"
#include "Device.h"
#include "io/FileInputStream.h"
#include "scene/mesh/MeshLoader.h"
#include "scene/mesh/MD2AnimatedMesh.h"
#include "scene/node/MD2AnimatedMeshSceneNode.h"
#include "scene/node/BasicMeshSceneNode.h"
#include "graphic/gl/GLCaches.h"
#include "graphic/gl/GLTexture.h"
#include "graphic/material/LambertMaterial.h"
#include "graphic/material/PhongMaterial.h"
#include "graphic/geometries/SphereGeometry.h"
#include "graphic/geometries/CubeGeometry.h"
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
	DirectionalLight* light = new DirectionalLight({- 1.f, 0.f, 0.f}, {1.f, 1.f, 1.f});
	scene->environment()->addLight(light);
	scene->environment()->setAmbientLight({0.2f, 0.2f, 0.2f});
//	scene->environment()->addLight(new DirectionalLight({1.f, 0.f, 0.f}, {1.f, 1.f, 1.f}));

	Material* tm1 = new LambertMaterial({1.0f, 1.0f, 1.0f}, texture);

	/*if (mesh) {
		MD2AnimatedMeshSceneNode* node = new MD2AnimatedMeshSceneNode(mesh);
		node->setPosition(graphic::vec3(0, 0, - 100));
		node->setMaterial(tm1);
		scene->addSceneNode(node);
	}*/
//	BasicMesh* m = new BasicMesh(new SphereGeometry(30.f, 20, 20));
	BasicMesh* m = new BasicMesh(new CubeGeometry(30.f, 30.f, 30.f));
	BasicMeshSceneNode* node = new BasicMeshSceneNode(m);
	node->setMaterial(new PhongMaterial({1.0f, 1.0f, 1.0f}));
	node->setPosition(graphic::vec3(0, 0, - 100));
	scene->addSceneNode(node);


//	scene->addCamera(new PerspectiveCameraFPS({0, 0, 1}, {0, 0, 0}));
	Camera* camera = new PerspectiveCamera();
	camera->setCameraController(new DefaultCameraController(camera));
//	camera->setPosition(vec3(0, 0, -100));
	scene->addCamera(camera);

	while (device->run()) {
		scene->render();

		device->swapBuffers();
	}
	return 1;
}


