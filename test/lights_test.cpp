/*
 * gltest1.cpp
 *
 *  Created on: 2015年12月10日
 *      Author: lijing
 */

#include "pola/scene/camera/PerspectiveCamera.h"
#include "pola/scene/camera/DefaultCameraController.h"
#include "pola/Device.h"
#include "pola/io/FileInputStream.h"
#include "pola/scene/mesh/MeshLoader.h"
#include "pola/scene/mesh/MD2AnimatedMesh.h"
#include "pola/scene/node/MD2MeshSceneNode.h"
#include "pola/scene/node/BasicMeshSceneNode.h"
#include "pola/scene/mesh/BasicMesh.h"
#include "pola/graphic/material/LambertMaterial.h"
#include "pola/graphic/material/PhongMaterial.h"
#include "pola/graphic/geometries/SphereGeometry.h"
#include "pola/graphic/geometries/CubeGeometry.h"
#include "pola/utils/Math.h"

using namespace pola;
using namespace pola::utils;
using namespace pola::scene;
using namespace pola::graphic;

int main(int argc, char *argv[]) {

	DeviceParam param = {500, 500, false, 16};
	Device* device = createDevice(param);

	 Scene* scene = device->getSceneManager()->getActiveScene();
	 scene->setClearColor({0.4f, 0.4f, 0.6f, 1.f});
	Texture* texture = scene->graphic()->loadTexture("./res/ctf_r.png");
	DirectionalLight* light = new DirectionalLight({1.f, 0.f, 0.f}, {1.f, 1.f, 1.f});
	light->castShadow = true;
	LightNode* lightNode = new LightNode(light);
	lightNode->setPosition({-150.f, 0.f, 0.f});
	scene->addChild(lightNode);
//	scene->addChild(new LightNode(new DirectionalLight({1.f, 0.f, 0.f}, {1.f, 1.f, 1.f})));
	scene->environment()->setAmbientLight({0.5f, 0.5f, 0.5f});
//	scene->environment()->addLight(new DirectionalLight({1.f, 0.f, 0.f}, {1.f, 1.f, 1.f}));
//	scene->addChild(new LightNode(new PointLight(graphic::vec3(200, 0, 0), 500, {0.f, 1.f, 0.f})));

	Material* tm1 = new LambertMaterial({1.0f, 1.0f, 1.0f}, texture);

	 Mesh* meshs = nullptr;
	 std::vector<MaterialDescription> materials;
	if (MeshLoader::loadMesh("./res/ratamahatta.md2", meshs, materials)) {
		MD2MeshSceneNode* node = new MD2MeshSceneNode((MD2AnimatedMesh*) meshs);
		node->setPosition(graphic::vec3(-100, 0, 0));
		node->setMaterial(0, tm1);
		materials.clear();
		if (MeshLoader::loadMesh("./res/weapon.md2", meshs, materials)) {
			MD2MeshSceneNode* weaponNode = new MD2MeshSceneNode((MD2AnimatedMesh*) meshs);
			weaponNode->setMaterial(0, new LambertMaterial({1.0f, 1.0f, 1.0f}, scene->graphic()->loadTexture("./res/weapon.png")));
			node->addChild(weaponNode);
		}
		scene->addChild(node);
	}

	materials.clear();
	if (MeshLoader::loadMesh("./res/monster.ms3d", meshs, materials)) {
		BasicMeshSceneNode* n = new  BasicMeshSceneNode(meshs);
		for (unsigned i = 0; i < materials.size(); i ++) {
			const MaterialDescription& mate = materials[i];
			std::string texName = "./res/";
			texName += mate.texture;
			n->setMaterial(i, new LambertMaterial({1.0f, 1.0f, 1.0f}, scene->graphic()->loadTexture(texName.c_str())));
		}
//		n->setPosition(graphic::vec3(150, 0, 0));
		n->setScale(graphic::vec3(10, 10, 10));
		scene->addChild(n);
	}

	BasicMesh* m = new BasicMesh(new SphereGeometry(30.f, 20, 20));
//	BasicMesh* m = new BasicMesh(new CubeGeometry(30.f, 30.f, 30.f));
	BasicMeshSceneNode* node = new BasicMeshSceneNode(m);
	node->setMaterial(0, new LambertMaterial({1.0f, 1.0f, 1.0f}));
	node->setPosition(graphic::vec3(50, 0, 0));
	scene->addChild(node);

	m = new BasicMesh(new CubeGeometry(60.f, 60.f, 60.f));
	node = new BasicMeshSceneNode(m);
	node->setMaterial(0, new LambertMaterial({1.0f, 1.0f, 1.0f}));
	node->setPosition(graphic::vec3(100, 0, 0));
	scene->addChild(node);


//	scene->addCamera(new PerspectiveCameraFPS({0, 0, 1}, {0, 0, 0}));
	Camera* camera = new PerspectiveCamera();
	camera->setCameraController(new DefaultCameraController(camera));
	camera->setPosition(vec3(0, 0, 100));
	scene->addCamera(camera);

	while (device->run()) {
		scene->render();

		device->swapBuffers();
	}
	return 1;
}


