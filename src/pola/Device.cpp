/*
 * Device.cpp
 *
 *  Created on: 2016年5月30日
 *      Author: lijing
 */

#include "pola/Device.h"
#ifdef POLA_LINUX_X11
#include "pola/LinuxDevice.h"
#endif

namespace pola {

Device::Device(const DeviceParam& param) : mDeviceParam(param) {
}

Device::~Device() {
}

Device* createDevice(const DeviceParam& param) {
#ifdef POLA_LINUX_X11
	static LinuxDevice* device = new LinuxDevice(param);
	return device;
#else
	return nullptr;
#endif
}

}
