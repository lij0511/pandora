/*
 * gltest1.cpp
 *
 *  Created on: 2015年12月10日
 *      Author: lijing
 */

#include "scene/Scene.h"
#include "graphic/gl/GLGraphicContext.h"
#include "graphic/gl/GL1xGraphicContext.h"
#include "graphic/gl/GLCaches.h"
#include "scene/Camera3D.h"
#include "scene/mesh/MeshLoader.h"
#include "io/FileInputStream.h"
#include "scene/node/MD2AnimatedMeshSceneNode.h"
#include "scene/FPS.h"

#include "utils/thread/FunctionalTask.h"
#include "utils/thread/Handler.h"
#include "utils/thread/HandlerThread.h"
#include <GL/gl.h>
#include <GL/glx.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <signal.h>
#include <execinfo.h>
#include<ucontext.h>


using namespace pola::utils;
using namespace pola::scene;
using namespace pola::graphic;

Display *dpy;
GLXWindow glw;
GLXContext glc;
int WINDOW_WIDTH = 1000;
int WINDOW_HEIGHT = 800;

Handler* mHandler;
Scene* scene;
Camera3D* camera;
GLTexture* texture;
XEvent e;


FPS fps;

void display() {
	glClearColor(1.0f, 0.4f, 0.4f, 0.6f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	/*MeshBuffer m(Vertex3::type());
	Vertex3* vertex= (Vertex3*) m.alloc(4);
	Vertex3::set(vertex, -1.0f, -1.0f, -0.0f);
	Vertex3::set(vertex + 1, -1.0f, 1.0f, -0.0f);
	Vertex3::set(vertex + 2, 1.0f, -1.0f, -0.0f);
	Vertex3::set(vertex + 3, 1.0f, 1.0f, -.0f);
	m.pushIndex(0);
	m.pushIndex(1);
	m.pushIndex(2);
	m.pushIndex(2);
	m.pushIndex(1);
	m.pushIndex(3);*/
//	camera->yaw(1);
	/*glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(M_PI / 2.5f, 1.0f, 1000, 3000000);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0, 0, 50, 0, 0, 49, 0, 1, 0);*/
		if (texture != nullptr && texture->generateTexture()) {
			GLCaches::get().bindTexture(texture->id);
		}
		scene->render();

	glXSwapBuffers(dpy, glw);
	fps.fps();
}
void loop() {

	// Consume all the X events.
	display();
	while (XPending(dpy)) {
	  XEvent e;
	  XNextEvent(dpy, &e);
	  switch (e.type) {
		case Expose:
		  break;
		case ConfigureNotify:
			scene->setViewport(e.xconfigure.width, e.xconfigure.height);
			camera->setSize(e.xconfigure.width, e.xconfigure.height);
		  break;
		default:
		  break;
	  }
	}

	mHandler->post(new FunctionalTask(bind(&loop)));
}

int main(int argc, char *argv[]) {

	/* 建立 X 窗口所需的变量 */
	Window root;
	Window win;
	XVisualInfo *vi;
	Colormap cmap;
	XSetWindowAttributes swa;
	XWindowAttributes gwa;
	XEvent xev;

	/* 在 X 窗口中渲染 OpenGL 图形所需变量 */
	GLXFBConfig *fc;

	int att[] = {GLX_RGBA, GLX_USE_GL,
			GLX_RED_SIZE, 4,
			GLX_GREEN_SIZE, 4,
			GLX_BLUE_SIZE, 4,
		  GLX_DEPTH_SIZE, 24,
			GLX_ALPHA_SIZE, 1,
			 GLX_SAMPLE_BUFFERS, 1,
				GLX_SAMPLES, 2,
					  GLX_DOUBLEBUFFER, True,
					  None};
	int nelements;

	dpy = XOpenDisplay (NULL);

	if (dpy == NULL) {
			printf ("\n\tcannot connect to X server\n\n");
			return -1;
	}

	fc = glXChooseFBConfig (dpy, 0, att, &nelements);

	if (fc == NULL) {
			printf
				("\n\tno appropriate framebuffer config found\n\n");
			return -1;
	}

	vi = glXGetVisualFromFBConfig (dpy, *fc);

	if (vi == NULL) {
			printf ("\n\tno appropriate visual found\n\n");
			return -1;
	}

	root = RootWindow (dpy, DefaultScreen(dpy));
	cmap = XCreateColormap (dpy, root, vi->visual, AllocNone);

	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask | StructureNotifyMask;

	win = XCreateWindow (dpy, root, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
										 0, vi->depth,
										 InputOutput, vi->visual,
										 CWColormap | CWEventMask, &swa);
	XMapWindow (dpy, win);
	XStoreName (dpy, win, "VERY SIMPLE APPLICATION");

	glw = glXCreateWindow (dpy, *fc, win, NULL);
	glc = glXCreateNewContext (dpy, *fc, GLX_RGBA_TYPE, NULL, GL_TRUE);

	if (!glXMakeContextCurrent(dpy, glw, glw, glc)) {
	  glXDestroyContext(dpy, glc);
	  printf("Cannot open glXMakeCurrent\n");
	  return 0;
	}
	if(glewInit() != GLEW_OK) {
		 printf("haha\n");
	 }

	 /*if (!glewIsSupported("GL_VERSION_2_0")) {

	 fprintf(stderr, "Required OpenGL extensions missing. %s", glGetString(GL_EXTENSIONS));

	 exit(-1);

	 }*/
	 HandlerThread thread;
	 thread.start();
	 Handler h(thread.getLooper());

	 scene = new Scene(new GLGraphicContext);
	 scene->setViewport(WINDOW_WIDTH, WINDOW_HEIGHT);
	pola::io::FileInputStream is("/home/lijing/work/workspace/webcore/irrlicht-1.8.3/media/faerie.md2");
	MD2AnimatedMesh* mesh = (MD2AnimatedMesh*) MeshLoader::loadMesh(&is);
	if (mesh) {
		MD2AnimatedMeshSceneNode* node = new MD2AnimatedMeshSceneNode(mesh);
		scene->addSceneNode(node);
		node = new MD2AnimatedMeshSceneNode(mesh);
		node->setPosition({50, 0, 0});
		node->setAnimationType(MAT_JUMP);
		scene->addSceneNode(node);
	}
	 camera = new Camera3D({0, 0, 100}, {0, 0, 99});
	 camera->setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	 scene->graphic()->setMatrix(GraphicContext::PROJECTION, camera->matrix());

	 texture = (GLTexture*) scene->graphic()->loadTexture("/home/lijing/work/workspace/webcore/irrlicht-1.8.3/media/faerie2.bmp");
	Looper::prepare();
	mHandler = new Handler(Looper::myLooper());
	mHandler->post(new FunctionalTask(bind(&loop)));
	Looper::myLooper()->loop();
	return 1;
}


