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
#include "pola/graphic/BitmapFactory.h"

using namespace pola;
using namespace pola::utils;
using namespace pola::scene;
using namespace pola::graphic;

int main(int argc, char *argv[]) {

	DeviceParam param = {1300, 900, false, 16};
	Device* device = createDevice(param);
	GraphicContext* graphic = device->getGraphicContext();

	Camera* camera = new OrthoCamera(-1.f, 1.f);

	graphic::Bitmap* b = graphic::BitmapFactory::decodeFile("/home/lijing/work/workspace/webcore/ws/test.png");
//	graphic::Bitmap* b = graphic::BitmapFactory::decodeFile("./res/faerie2.bmp");
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


	graphic->setViewport(1300, 900);
	camera->setSize(1300, 900);
	camera->update(graphic, uptimeMillis());

	int x = 0;

	FPS fps;
	while (/*device->run()*/true) {
//		scene->render();
		graphic->beginFrame({1.f, 0.f, 0.f, 1.f});

		graphic->renderGeometry(geometry, m);
		if (t2 != nullptr) {
			graphic->renderGeometry(geometry2, m2);
		}

		graphic->endFrame();
		device->swapBuffers();
		if (++ x > 500) {
			x = 0;
		}
		fps.fps();
		usleep(16000);
	}
	return 1;
}


