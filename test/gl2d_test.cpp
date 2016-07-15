/*
 * gltest1.cpp
 *
 *  Created on: 2015年12月10日
 *      Author: lijing
 */

#include "pola/scene/camera/OrthoCamera.h"
#include "pola/scene/camera/PerspectiveCamera.h"
#include "pola/scene/camera/DefaultCameraController.h"
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
	GLTexture* texture = (GLTexture*) scene->graphic()->loadTexture("./res/faerie2.bmp");
	Material* tm1 = new Material({1.0f, 1.0f, 1.0f, .1f}, texture);

	BasicMesh* m = new BasicMesh(new RectangleGeometry(0, 0, 100, 100));
	BasicMeshSceneNode* node = new BasicMeshSceneNode(m);
	node->setMaterial(tm1);
//	node->setScale({3, 3, 3});
	node->setPosition({100, 100, 0});
	scene->addSceneNode(node);

//	scene->addCamera(new PerspectiveCameraFPS({0, 0, 1}, {0, 0, 0}));
//	Camera* camera = new PerspectiveCamera();
	Camera* camera = new OrthoCamera(-1, 1);
//	camera->setCameraController(new DefaultCameraController(camera));
//	camera->setPosition(vec3(0, 0, -100));
	scene->addCamera(camera);

	while (device->run()) {
		scene->render();

		device->swapBuffers();
	}
	return 1;
}


