/*
 * LinuxDevice.cpp
 *
 *  Created on: 2016年5月30日
 *      Author: lijing
 */

#include "log/Log.h"
#include "graphic/gl/GLGraphicContext.h"
#include "LinuxDevice.h"

namespace pola {

LinuxDevice::LinuxDevice(const DeviceParam& param) : Device(param) {
	mGraphicContext = nullptr;
	mSceneManager = nullptr;
	createWindow();
}

LinuxDevice::~LinuxDevice() {
	if (mGraphicContext != nullptr) {
		delete mGraphicContext;
	}
}

graphic::GraphicContext* LinuxDevice::getGraphicContext() {
	if (mGraphicContext == nullptr) {
		mGraphicContext = new graphic::GLGraphicContext;
	}
	return mGraphicContext;
}

scene::SceneManager* LinuxDevice::getSceneManager() {
	if (mSceneManager == nullptr) {
		mSceneManager = new scene::SceneManager(getGraphicContext());
	}
	return mSceneManager;
}

void LinuxDevice::run() {
	while (1) {
		getSceneManager()->getActiveScene()->render();

		glXSwapBuffers(mDisplay, mGLWindow);

		while (XPending(mDisplay)) {
		  XEvent e;
		  XNextEvent(mDisplay, &e);
		  switch (e.type) {
			case Expose:
			  break;
			case ConfigureNotify:
				getSceneManager()->getActiveScene()->setViewport(e.xconfigure.width, e.xconfigure.height);
			  break;
			default:
			  break;
		  }
		}
	}
}

void LinuxDevice::createWindow() {
	/* 建立 X 窗口所需的变量 */
	Display* dpy;
	Window root;
	Window win;
	GLXWindow glWindow;
	GLXContext glContext;
	XVisualInfo *vi;
	Colormap cmap;
	XSetWindowAttributes swa;

	/* 在 X 窗口中渲染 OpenGL 图形所需变量 */
	GLXFBConfig *fc;

	int att[] = {GLX_RGBA, GLX_USE_GL,
			GLX_RED_SIZE, 4,
			GLX_GREEN_SIZE, 4,
			GLX_BLUE_SIZE, 4,
			GLX_DEPTH_SIZE, 16,
			GLX_ALPHA_SIZE, 1,
			GLX_SAMPLE_BUFFERS, 1,
			GLX_SAMPLES, 2,
			GLX_DOUBLEBUFFER, True,
			None};
	int nelements;

	dpy = XOpenDisplay (NULL);
	LOG_FATAL_IF(dpy == NULL, "cannot connect to X server\n");

	fc = glXChooseFBConfig (dpy, 0, att, &nelements);
	LOG_FATAL_IF(fc == NULL, "no appropriate framebuffer config found\n");

	vi = glXGetVisualFromFBConfig (dpy, *fc);
	LOG_FATAL_IF(vi == NULL, "no appropriate visual found\n");

	root = RootWindow (dpy, DefaultScreen(dpy));
	cmap = XCreateColormap (dpy, root, vi->visual, AllocNone);

	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask | StructureNotifyMask;

	win = XCreateWindow (dpy, root, 0, 0, mDeviceParam.mWindowWidth, mDeviceParam.mWindowHeight,
										 0, vi->depth,
										 InputOutput, vi->visual,
										 CWColormap | CWEventMask, &swa);
	XMapWindow (dpy, win);
	XStoreName (dpy, win, "VERY SIMPLE APPLICATION");

	glWindow = glXCreateWindow (dpy, *fc, win, NULL);
	glContext = glXCreateNewContext (dpy, *fc, GLX_RGBA_TYPE, NULL, GL_TRUE);

	if (!glXMakeContextCurrent(dpy, glWindow, glWindow, glContext)) {
	  glXDestroyContext(dpy, glContext);
	  LOG_ALWAYS_FATAL("Cannot open glXMakeCurrent\n");
	}
	if(glewInit() != GLEW_OK) {
	 }

	mDisplay = dpy;
	mGLWindow = glWindow;
	mGLContext = glContext;

	getGraphicContext();
	getSceneManager()->getActiveScene()->setViewport(mDeviceParam.mWindowWidth, mDeviceParam.mWindowHeight);
}

} /* namespace pola */
