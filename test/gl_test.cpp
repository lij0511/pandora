/*
 * gltest1.cpp
 *
 *  Created on: 2015年12月10日
 *      Author: lijing
 */

#include "scene/Scene.h"
#include "graphic/gl/GLGraphicContext.h"
#include "graphic/gl/GLCaches.h"
#include "scene/Camera3D.h"
#include "scene/mesh/MeshLoader.h"
#include "io/FileInputStream.h"
#include "scene/mesh/AnimatedMesh.h"
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

Display *display_;
Window window_;
GLXContext gl_context_;
int WINDOW_WIDTH = 1000;
int WINDOW_HEIGHT = 800;

Handler* mHandler;
Scene* scene;
AnimatedMesh* mesh;
Camera3D* camera;
GLTexture* texture;
XEvent e;


FPS fps;

void display() {
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

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
	scene->graphic()->setCurrentCamera(camera->matrix());
	if (mesh) {
		if (texture != nullptr && texture->generateTexture()) {
			GLCaches::get().bindTexture(texture->id);
		}
	for (int i = 0; i < 1; i ++)
		scene->graphic()->renderMeshBuffer(*(mesh->getMeshBuffer(0)));
	}

	glXSwapBuffers(display_, window_);
	fps.fps();
}
void loop() {

	// Consume all the X events.
	display();
	while (XPending(display_)) {
	  XEvent e;
	  XNextEvent(display_, &e);
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

	display_ = XOpenDisplay(NULL);
	if (!display_) {
		printf("Cannot open display\n");
	  return 0;
	}

	// Get properties of the screen.
	int screen = DefaultScreen(display_);
	int root_window = RootWindow(display_, screen);

	XSetWindowAttributes swa;
	  memset(&swa, 0, sizeof(swa));
	  swa.background_pixmap = None;
	  swa.override_redirect = false;
	  window_ = XCreateWindow(
			  display_,
			  root_window,
			  100,
			  100,
			  WINDOW_WIDTH,
			  WINDOW_HEIGHT,
	      0,               // border width
	      CopyFromParent,  // depth
	      InputOutput,
	      CopyFromParent,  // visual
	      CWBackPixmap | CWOverrideRedirect,
	      &swa);
	XStoreName(display_, window_, "Compositor Model Bench");

	XSelectInput(display_, window_,
				 ExposureMask | KeyPressMask | StructureNotifyMask | PointerMotionMask | ButtonPressMask | ButtonReleaseMask);
	XMapWindow(display_, window_);

	XResizeWindow(display_, window_, WINDOW_WIDTH, WINDOW_HEIGHT);

	XWindowAttributes attributes;
	XGetWindowAttributes(display_, window_, &attributes);
	XVisualInfo visual_info_template;
	visual_info_template.visualid = XVisualIDFromVisual(attributes.visual);
	int visual_info_count = 0;
	XVisualInfo* visual_info_list = XGetVisualInfo(display_, VisualIDMask,
												   &visual_info_template,
												   &visual_info_count);
	for (int i = 0; i < visual_info_count && !gl_context_; ++i) {
	  gl_context_ = glXCreateContext(display_, visual_info_list + i, 0,
									 True /* Direct rendering */);
	}

	XFree(visual_info_list);
	if (!gl_context_) {
		printf("Cannot open glContext\n");
	  return 0;
	}

	if (!glXMakeCurrent(display_, window_, gl_context_)) {
	  glXDestroyContext(display_, gl_context_);
	  gl_context_ = NULL;
	  printf("Cannot open glXMakeCurrent\n");
	  return 0;
	}
	if(glewInit() != GLEW_OK) {
		 printf("haha\n");
	 }

	 if (!glewIsSupported("GL_VERSION_2_0")) {

	 fprintf(stderr, "Required OpenGL extensions missing. %s", glGetString(GL_EXTENSIONS));

	 exit(-1);

	 }
	 HandlerThread thread;
	 thread.start();
	 Handler h(thread.getLooper());

	pola::io::FileInputStream is("/home/lijing/work/workspace/webcore/irrlicht-1.8.3/media/sydney.md2");
	mesh = MeshLoader::loadMesh(&is);

	 scene = new Scene(new GLGraphicContext);
	 scene->setViewport(WINDOW_WIDTH, WINDOW_HEIGHT);
	 camera = new Camera3D;
	 camera->setSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	 texture = (GLTexture*) scene->graphic()->loadTexture("/home/lijing/work/workspace/webcore/irrlicht-1.8.3/media/gun.jpg");

	Looper::prepare();
	mHandler = new Handler(Looper::myLooper());
	mHandler->post(new FunctionalTask(bind(&loop)));
	Looper::myLooper()->loop();
	return 1;
}


