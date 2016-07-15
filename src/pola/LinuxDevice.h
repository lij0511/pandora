/*
 * LinuxDevice.h
 *
 *  Created on: 2016年5月30日
 *      Author: lijing
 */

#ifdef POLA_LINUX_X11
#ifndef POLA_LINUXDEVICE_H_
#define POLA_LINUXDEVICE_H_

#include <GL/gl.h>
#include <GL/glx.h>
#include <X11/keysym.h>

#include "pola/utils/KeyedVector.h"
#include "pola/Device.h"

namespace pola {

/*
 *
 */
class LinuxDevice: public Device {
public:
	LinuxDevice(const DeviceParam& param);
	virtual ~LinuxDevice();

	virtual graphic::GraphicContext* getGraphicContext();
	virtual scene::SceneManager* getSceneManager();

	virtual void swapBuffers();

	virtual bool run();

private:
	void createKeyMap();
	void createWindow();

private:
	Display* mDisplay;
	GLXWindow mGLWindow;
	GLXContext mGLContext;

	graphic::GraphicContext* mGraphicContext;
	scene::SceneManager* mSceneManager;

	utils::KeyedVector<KeySym, input::KeyEvent::KeyCode> mKeyMap;

};

} /* namespace pola */

#endif /* LINUXDEVICE_H_ */
#endif
