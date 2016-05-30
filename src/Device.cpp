/*
 * Device.cpp
 *
 *  Created on: 2016年5月30日
 *      Author: lijing
 */

#include "Device.h"
#include "LinuxDevice.h"

namespace pola {

Device::Device(const DeviceParam& param) : mDeviceParam(param) {
}

Device::~Device() {
}

Device* createDevice(const DeviceParam& param) {
	static LinuxDevice* device = new LinuxDevice(param);
	return device;
}

}
