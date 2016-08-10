/*
 * LinuxDevice.cpp
 *
 *  Created on: 2016年5月30日
 *      Author: lijing
 */

#ifdef POLA_LINUX_X11
#include "pola/graphic/gl/GLGraphicContext.h"
#include "pola/log/Log.h"
#include "pola/LinuxDevice.h"
#include "pola/input/KeyEvent.h"
#include "pola/input/MouseEvent.h"

namespace pola {

LinuxDevice::LinuxDevice(const DeviceParam& param) : Device(param) {
	mGraphicContext = nullptr;
	mSceneManager = nullptr;

	createKeyMap();

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

void LinuxDevice::swapBuffers() {
	glXSwapBuffers(mDisplay, mGLWindow);
}

bool LinuxDevice::run() {
	while (XPending(mDisplay)) {
	  XEvent e;
	  XNextEvent(mDisplay, &e);
	  switch (e.type) {
		case Expose:
		  break;
		case ConfigureNotify:
			getSceneManager()->getActiveScene()->setViewport(e.xconfigure.width, e.xconfigure.height);
		  break;
		case KeyRelease:{
			if ((XPending(mDisplay) > 0)) {
				// check for Autorepeat manually
				// We'll do the same as Windows does: Only send KeyPressed
				// So every KeyRelease is a real release
				XEvent next_event;
				XPeekEvent (e.xkey.display, &next_event);
				if ((next_event.type == KeyPress) &&
					(next_event.xkey.keycode == e.xkey.keycode) &&
					(next_event.xkey.time - e.xkey.time) < 2)	// usually same time, but on some systems a difference of 1 is possible
				{
					/* Ignore the key release event */
					break;
				}
			}
		}
		case KeyPress: {
			KeySym k = XLookupKeysym(&e.xkey, 0);
			std::map<KeySym, input::KeyEvent::KeyCode>::iterator index = mKeyMap.find(k);
			if (index != mKeyMap.end()) {
				input::KeyEvent keyEvent(index->second, e.type == KeyRelease ? input::KeyEvent::ACTION_UP : input::KeyEvent::ACTION_DOWN);
				getSceneManager()->getActiveScene()->dispatchKeyEvent(keyEvent);
			} else {
				printf("keycode=%lu not found\n", k);
			}
			break;
		}
		case MotionNotify: {
			int32_t buttonState = (e.xbutton.state & Button1Mask) ? input::MouseEvent::BUTTON_LEFT : 0;
			buttonState |= (e.xbutton.state & Button2Mask) ? input::MouseEvent::BUTTON_MIDDLE : 0;
			buttonState |= (e.xbutton.state & Button3Mask) ? input::MouseEvent::BUTTON_RIGHT: 0;
			input::MouseEvent mouseEvent(e.xbutton.x, e.xbutton.y, input::MouseEvent::ACTION_MOVE, input::MouseEvent::BUTTON_NONE, buttonState);
			getSceneManager()->getActiveScene()->dispatchMouseEvent(mouseEvent);
			break;
		}
		case ButtonPress:
		case ButtonRelease: {
			int32_t buttonState = (e.xbutton.state & Button1Mask) ? input::MouseEvent::BUTTON_LEFT : 0;
			buttonState |= (e.xbutton.state & Button2Mask) ? input::MouseEvent::BUTTON_MIDDLE : 0;
			buttonState |= (e.xbutton.state & Button3Mask) ? input::MouseEvent::BUTTON_RIGHT: 0;
			input::MouseEvent::Action action = e.type == ButtonPress ? input::MouseEvent::ACTION_DOWN : input::MouseEvent::ACTION_UP;
			input::MouseEvent::Button button = input::MouseEvent::BUTTON_NONE;
			switch (e.xbutton.button) {
				case Button1:
					button = input::MouseEvent::BUTTON_LEFT;
					break;
				case Button2:
					button = input::MouseEvent::BUTTON_MIDDLE;
					break;
				case Button3:
					button = input::MouseEvent::BUTTON_RIGHT;
					break;
				default:
					break;
			}
			input::MouseEvent mouseEvent(e.xbutton.x, e.xbutton.y, action, button, buttonState);
			getSceneManager()->getActiveScene()->dispatchMouseEvent(mouseEvent);
			break;
		}
		default:
		  break;
	  }
	}
	return true;
}

void LinuxDevice::createKeyMap() {

	mKeyMap[XK_KP_0] = input::KeyEvent::KEYCODE_NUMPAD_0;
	mKeyMap[XK_KP_1] = input::KeyEvent::KEYCODE_NUMPAD_1;
	mKeyMap[XK_KP_2] = input::KeyEvent::KEYCODE_NUMPAD_2;
	mKeyMap[XK_KP_3] = input::KeyEvent::KEYCODE_NUMPAD_3;
	mKeyMap[XK_KP_4] = input::KeyEvent::KEYCODE_NUMPAD_4;
	mKeyMap[XK_KP_5] = input::KeyEvent::KEYCODE_NUMPAD_5;
	mKeyMap[XK_KP_6] = input::KeyEvent::KEYCODE_NUMPAD_6;
	mKeyMap[XK_KP_7] = input::KeyEvent::KEYCODE_NUMPAD_7;
	mKeyMap[XK_KP_8] = input::KeyEvent::KEYCODE_NUMPAD_8;
	mKeyMap[XK_KP_9] = input::KeyEvent::KEYCODE_NUMPAD_9;

	mKeyMap[XK_0] = input::KeyEvent::KEYCODE_0;
	mKeyMap[XK_1] = input::KeyEvent::KEYCODE_1;
	mKeyMap[XK_2] = input::KeyEvent::KEYCODE_2;
	mKeyMap[XK_3] = input::KeyEvent::KEYCODE_3;
	mKeyMap[XK_4] = input::KeyEvent::KEYCODE_4;
	mKeyMap[XK_5] = input::KeyEvent::KEYCODE_5;
	mKeyMap[XK_6] = input::KeyEvent::KEYCODE_6;
	mKeyMap[XK_7] = input::KeyEvent::KEYCODE_7;
	mKeyMap[XK_8] = input::KeyEvent::KEYCODE_8;
	mKeyMap[XK_9] = input::KeyEvent::KEYCODE_9;

	mKeyMap[XK_A] = input::KeyEvent::KEYCODE_A;
	mKeyMap[XK_B] = input::KeyEvent::KEYCODE_B;
	mKeyMap[XK_C] = input::KeyEvent::KEYCODE_C;
	mKeyMap[XK_D] = input::KeyEvent::KEYCODE_D;
	mKeyMap[XK_E] = input::KeyEvent::KEYCODE_E;
	mKeyMap[XK_F] = input::KeyEvent::KEYCODE_F;
	mKeyMap[XK_G] = input::KeyEvent::KEYCODE_G;
	mKeyMap[XK_H] = input::KeyEvent::KEYCODE_H;
	mKeyMap[XK_I] = input::KeyEvent::KEYCODE_I;
	mKeyMap[XK_J] = input::KeyEvent::KEYCODE_J;
	mKeyMap[XK_K] = input::KeyEvent::KEYCODE_K;
	mKeyMap[XK_L] = input::KeyEvent::KEYCODE_L;
	mKeyMap[XK_M] = input::KeyEvent::KEYCODE_M;
	mKeyMap[XK_N] = input::KeyEvent::KEYCODE_N;
	mKeyMap[XK_O] = input::KeyEvent::KEYCODE_O;
	mKeyMap[XK_P] = input::KeyEvent::KEYCODE_P;
	mKeyMap[XK_Q] = input::KeyEvent::KEYCODE_Q;
	mKeyMap[XK_R] = input::KeyEvent::KEYCODE_R;
	mKeyMap[XK_S] = input::KeyEvent::KEYCODE_S;
	mKeyMap[XK_T] = input::KeyEvent::KEYCODE_T;
	mKeyMap[XK_U] = input::KeyEvent::KEYCODE_U;
	mKeyMap[XK_V] = input::KeyEvent::KEYCODE_V;
	mKeyMap[XK_W] = input::KeyEvent::KEYCODE_W;
	mKeyMap[XK_X] = input::KeyEvent::KEYCODE_X;
	mKeyMap[XK_Y] = input::KeyEvent::KEYCODE_Y;
	mKeyMap[XK_Z] = input::KeyEvent::KEYCODE_Z;

	mKeyMap[XK_a] = input::KeyEvent::KEYCODE_A;
	mKeyMap[XK_b] = input::KeyEvent::KEYCODE_B;
	mKeyMap[XK_c] = input::KeyEvent::KEYCODE_C;
	mKeyMap[XK_d] = input::KeyEvent::KEYCODE_D;
	mKeyMap[XK_e] = input::KeyEvent::KEYCODE_E;
	mKeyMap[XK_f] = input::KeyEvent::KEYCODE_F;
	mKeyMap[XK_g] = input::KeyEvent::KEYCODE_G;
	mKeyMap[XK_h] = input::KeyEvent::KEYCODE_H;
	mKeyMap[XK_i] = input::KeyEvent::KEYCODE_I;
	mKeyMap[XK_j] = input::KeyEvent::KEYCODE_J;
	mKeyMap[XK_k] = input::KeyEvent::KEYCODE_K;
	mKeyMap[XK_l] = input::KeyEvent::KEYCODE_L;
	mKeyMap[XK_m] = input::KeyEvent::KEYCODE_M;
	mKeyMap[XK_n] = input::KeyEvent::KEYCODE_N;
	mKeyMap[XK_o] = input::KeyEvent::KEYCODE_O;
	mKeyMap[XK_p] = input::KeyEvent::KEYCODE_P;
	mKeyMap[XK_q] = input::KeyEvent::KEYCODE_Q;
	mKeyMap[XK_r] = input::KeyEvent::KEYCODE_R;
	mKeyMap[XK_s] = input::KeyEvent::KEYCODE_S;
	mKeyMap[XK_t] = input::KeyEvent::KEYCODE_T;
	mKeyMap[XK_u] = input::KeyEvent::KEYCODE_U;
	mKeyMap[XK_v] = input::KeyEvent::KEYCODE_V;
	mKeyMap[XK_w] = input::KeyEvent::KEYCODE_W;
	mKeyMap[XK_x] = input::KeyEvent::KEYCODE_X;
	mKeyMap[XK_y] = input::KeyEvent::KEYCODE_Y;
	mKeyMap[XK_z] = input::KeyEvent::KEYCODE_Z;

	mKeyMap[XK_Left] = input::KeyEvent::KEYCODE_LEFT;
	mKeyMap[XK_Right] = input::KeyEvent::KEYCODE_RIGHT;
	mKeyMap[XK_Up] = input::KeyEvent::KEYCODE_UP;
	mKeyMap[XK_Down] = input::KeyEvent::KEYCODE_DOWN;


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
	swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask | StructureNotifyMask | PointerMotionMask | ButtonPressMask| ButtonReleaseMask;

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

#endif
