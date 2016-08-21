/*
 * gltest1.cpp
 *
 *  Created on: 2015年12月10日
 *      Author: lijing
 */

#include <unistd.h>

#include "pola/scene/camera/OrthoCamera.h"
#include "pola/scene/camera/PerspectiveCamera.h"
#include "pola/scene/camera/DefaultCameraController.h"
#include "pola/Device.h"
#include "pola/io/FileInputStream.h"
#include "pola/scene/mesh/MeshLoader.h"
#include "pola/scene/mesh/MD2AnimatedMesh.h"
#include "pola/scene/node/MD2MeshSceneNode.h"
#include "pola/scene/node/BasicMeshSceneNode.h"
#include "pola/graphic/material/LambertMaterial.h"
#include "pola/graphic/material/PhongMaterial.h"
#include "pola/utils/Math.h"
#include "pola/graphic/geometries/SphereGeometry.h"
#include "pola/graphic/geometries/CubeGeometry.h"
#include "pola/graphic/geometries/RectangleGeometry.h"
#include "pola/graphic/BitmapFactory.h"

using namespace pola;
using namespace pola::utils;
using namespace pola::scene;
using namespace pola::graphic;

int main(int argc, char *argv[]) {

	DeviceParam param = {1300, 900, false, 16};
	Device* device = createDevice(param);
	GraphicContext* graphic = device->getGraphicContext();

	Camera* camera = new OrthoCamera(0, 13000,  0, 900, -1000.f, 1000.f);
//	Camera* camera = new PerspectiveCamera();

	graphic::Bitmap* b = graphic::BitmapFactory::decodeFile("/home/lijing/work/workspace/webcore/ws/test.png");
//	graphic::Bitmap* b = graphic::BitmapFactory::decodeFile("/home/lijing/work/cyclone/src/0.png"/*, Bitmap::Format::ALPHA8*/);
//	graphic::Bitmap* b = graphic::BitmapFactory::decodeFile("./res/faerie2.bmp");
//	graphic::Bitmap* b = graphic::BitmapFactory::decodeFile("/home/lijing/work/cyclone/src/pageloaderror.png");
	GLTexture* t = new GLTexture(b);
	GLTexture* t2 = nullptr;

	graphic::Bitmap* c = nullptr;
	if (b->scale(c, 2.f, 2.f)) {
		t2 = new GLTexture(c);
	}

	Geometry2D* geometry = new RectangleGeometry(0, 0, b->getWidth(), b->getHeight());
	Material* m = new Material({1.f, 1.f, 1.f, 1.f}, t);

	Geometry2D* geometry2 = new RectangleGeometry(b->getWidth(), 0, c->getWidth(), c->getHeight());
	Material* m2 = new Material({1.f, 1.f, 1.f, 1.f}, t2);

	Geometry2D* geometry3 = new RectangleGeometry(0, 0, 200, 200);
	Material m3({1.f, 1.f, 1.f, 0.9f});


	graphic->setViewport(1300, 900);
	camera->setSize(1300, 900);
	camera->update(graphic, uptimeMillis());

	int x = 0;
	float w2 = (b->getWidth()) / 2;
	float h2 = (b->getHeight()) / 2;

	FPS fps;
	while (/*device->run()*/true) {
//		scene->render();
		graphic->beginFrame({1.f, 0.f, 0.f, 1.f});
		mat4 transform;
		transform.loadIdentity();
		transform.translate(w2, h2);
		transform.rotate(x, 0, 0, 1);
		transform.translate(- w2, - h2);
		graphic->setMatrix(GraphicContext::MODEL, transform);
		graphic->renderGeometry(geometry, m);
		if (t2 != nullptr) {
			mat4 transform;
			transform.loadIdentity();
			transform.translate(0, 0, 0);
			transform.rotate(20, 0, 0, 1);
			graphic->setMatrix(GraphicContext::MODEL, transform);
			graphic->renderGeometry(geometry2, m2);
		}
		transform.loadIdentity();
		transform.translate(0, 0, 0);
		transform.rotate(45, 0, 0, 1);
		graphic->setMatrix(GraphicContext::MODEL, transform);
		graphic->renderGeometry(geometry3, &m3);

		transform.loadIdentity();
		transform.translate(300, 300, 0);
		transform.rotate(80, 0, 0, 1);
		graphic->setMatrix(GraphicContext::MODEL, transform);
		graphic->renderGeometry(geometry3, &m3);

		graphic->endFrame();
		device->swapBuffers();
		if (++ x > 360) {
			x = 0;
		}
		fps.fps();
		usleep(16000);
	}
	return 1;
}


