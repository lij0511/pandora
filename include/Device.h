/*
 * Device.h
 *
 *  Created on: 2016年5月30日
 *      Author: lijing
 */

#ifndef LOPA_DEVICE_H_
#define LOPA_DEVICE_H_

#include <stdint.h>

#include "graphic/GraphicContext.h"
#include "scene/SceneManager.h"

namespace pola {

struct DeviceParam {
	uint32_t mWindowWidth;
	uint32_t mWindowHeight;
	bool mFullscreen;
	uint8_t mDepth;
};

/*
 *
 */
class Device {
public:
	Device(const DeviceParam& param);
	virtual ~Device();

	virtual graphic::GraphicContext* getGraphicContext() = 0;
	virtual scene::SceneManager* getSceneManager() = 0;

	virtual void run() = 0;

protected:
	DeviceParam mDeviceParam;
};

Device* createDevice(const DeviceParam& param);

} /* namespace pola */

#endif /* LOPA_DEVICE_H_ */
