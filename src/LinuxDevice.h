/*
 * LinuxDevice.h
 *
 *  Created on: 2016年5月30日
 *      Author: lijing
 */

#ifndef POLA_LINUXDEVICE_H_
#define POLA_LINUXDEVICE_H_

#include <GL/gl.h>
#include <GL/glx.h>
#include "Device.h"

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

	virtual void run();

private:
	void createWindow();

private:
	Display* mDisplay;
	GLXWindow mGLWindow;
	GLXContext mGLContext;

	graphic::GraphicContext* mGraphicContext;
	scene::SceneManager* mSceneManager;

};

} /* namespace pola */

#endif /* LINUXDEVICE_H_ */
