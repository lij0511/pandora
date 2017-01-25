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
#include "pola/scene/node/SceneNode.h"
#include "pola/scene/mesh/BasicMesh.h"
#include "pola/scene/mesh/SkinnedMesh.h"
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

	 pola::utils::sp<MeshLoader::MeshInfo> result;
	if ((result = MeshLoader::loadMesh("./res/ratamahatta.md2")) != nullptr) {
		SceneNode* n = scene->addMesh(result->mesh.get(), scene);
		SceneNode* node = scene->addMesh(result->mesh.get(), scene);
		node->setPosition(graphic::vec3(0, 0, 20));
		node->setMaterial(0, tm1);
		n->setPosition(graphic::vec3(-100, 0, 0));
		n->setMaterial(0, tm1);
		if ((result = MeshLoader::loadMesh("./res/weapon.md2")) != nullptr) {
			SceneNode* weaponNode = scene->addMesh(result->mesh.get(), n);
			weaponNode->setMaterial(0, new LambertMaterial({1.0f, 1.0f, 1.0f}, scene->graphic()->loadTexture("./res/weapon.png")));
			n->addChild(weaponNode);
		}
	}

	if ((result = MeshLoader::loadMesh("./res/monster.ms3d")) != nullptr) {
		SceneNode* n = scene->addMesh(result->mesh.get(), scene);
		for (unsigned i = 0; i < result->materials.size(); i ++) {
			const MaterialDescription& mate = result->materials[i];
			std::string texName = "./res/";
			texName += mate.texture;
			n->setMaterial(i, new LambertMaterial({1.0f, 1.0f, 1.0f}, scene->graphic()->loadTexture(texName.c_str())));
		}
	}
	if ((result = MeshLoader::loadMesh("./res/fbx/nvhai.FBX")) != nullptr) {
		SceneNode* n = scene->addMesh(result->mesh.get(), scene);
//		n->setScale({0.1f, 0.1f, 0.1f});
		n->setPosition(graphic::vec3(- 50, 0, 0));
		for (unsigned i = 0; i < result->materials.size(); i ++) {
			const MaterialDescription& mate = result->materials[i];
			std::string texName = "./res/";
			texName += mate.texture;
			n->setMaterial(i, new LambertMaterial({1.0f, 1.0f, 1.0f}, scene->graphic()->loadTexture(texName.c_str())));
		}
		for (unsigned i = 0; i < result->children.size(); i ++) {
			SceneNode* node = scene->addMesh(result->children[i]->mesh.get(), n);
			for (unsigned j = 0; i < result->children[i]->materials.size(); j ++) {
				const MaterialDescription& mate = result->children[i]->materials[j];
				std::string texName = "./res/";
				texName += mate.texture;
				n->setMaterial(j, new LambertMaterial({1.0f, 1.0f, 1.0f}, scene->graphic()->loadTexture(texName.c_str())));
			}
		}
	}
	BasicMesh* m = new BasicMesh(new SphereGeometry(30.f, 20, 20));
//	BasicMesh* m = new BasicMesh(new CubeGeometry(30.f, 30.f, 30.f));
	SceneNode* node = scene->addMesh(m, scene);
	node->setMaterial(0, new LambertMaterial({1.0f, 1.0f, 1.0f}));
	node->setPosition(graphic::vec3(50, 0, 0));

	m = new BasicMesh(new CubeGeometry(60.f, 60.f, 60.f));
	node = scene->addMesh(m, scene);
	node->setMaterial(0, new LambertMaterial({1.0f, 1.0f, 1.0f}));
	node->setPosition(graphic::vec3(100, 0, 0));

	/*yunos::graphics::VPath path;
	path.moveTo(0, 0);
	path.quadTo(300, 0, 0, 300);

//	path.lineTo(100, 0);
//	path.lineTo(100, 200);
//	path.lineTo(0, 200);
	path.close();
	Geometry2D* g = new Geometry2D();
	yunos::graphics::VVertexBuffer vb;
	yunos::graphics::VPathTessellator::tessellatePath(path, yunos::graphics::VPathTessellator::PaintInfo(), vb);
	for (unsigned i = 0; i < vb.vertices.size(); i ++) {
		g->addPosition(vec2(vb.vertices[i].x, vb.vertices[i].y));
		printf("%f %f\n", vb.vertices[i].x, vb.vertices[i].y);
	}
	m = new BasicMesh(g);
	node = scene->addMesh(m, scene);
	node->setMaterial(0, new Material());
	node->setPosition(graphic::vec3(0, 0, 50));*/

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


