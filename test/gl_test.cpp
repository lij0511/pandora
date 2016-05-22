/*
 * gltest1.cpp
 *
 *  Created on: 2015年12月10日
 *      Author: lijing
 */

#include "scene/Scene.h"
#include "graphic/gl/GLGraphicContext.h"
#include "scene/Camera.h"
#include "scene/mesh/MD2MeshLoader.h"
#include "io/FileInputStream.h"
#include "scene/mesh/AnimationMesh.h"

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
AnimationMesh* mesh;
XEvent e;

int mTotalCount;
int mSecondCount = 0;
int mFrameCount = 0;
long mFrameCountingStart = 0;

void fps() {
	long now = uptimeMillis();
	++mFrameCount;
	if (mFrameCountingStart == 0) {
		mFrameCountingStart = now;
	} else if ((now - mFrameCountingStart) > 1000) {
		printf("FPS:%f\n", (double) mFrameCount
				* 1000 / (now - mFrameCountingStart));
		mFrameCountingStart = now;
		mFrameCount = 0;
	}
	++mTotalCount;
}

void display() {
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	Camera c(scene);

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

	scene->graphic()->setCurrentCamera(c.projection(), c.view());
	if (mesh) {
		scene->graphic()->renderMeshBuffer(*(mesh->m_mesh));
	}

	glXSwapBuffers(display_, window_);
	fps();
}
void loop() {

	// Consume all the X events.
	display();
	while (XPending(display_)) {
	  XEvent e;
	  XNextEvent(display_, &e);
	  printf("type=%d\n", e.type);
	  switch (e.type) {
		case Expose:
		  break;
		case ConfigureNotify:
			scene->setViewport(e.xconfigure.width, e.xconfigure.height);
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

	 pola::scene::MD2MeshLoader loader;
	pola::io::FileInputStream is("/home/lijing/work/workspace/irrlicht-1.8.3/media/faerie.md2");
	mesh = loader.loadMesh(&is);

	 scene = new Scene(new GLGraphicContext);
	 scene->setViewport(WINDOW_WIDTH, WINDOW_HEIGHT);

	Looper::prepare();
	mHandler = new Handler(Looper::myLooper());
	mHandler->post(new FunctionalTask(bind(&loop)));
	Looper::myLooper()->loop();
	return 1;
}


