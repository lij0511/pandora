/*
 * LinuxDevice.h
 *
 *  Created on: 2016年5月30日
 *      Author: lijing
 */

#ifndef POLA_LINUXDEVICE_H_
#define POLA_LINUXDEVICE_H_

#include "Device.h"

namespace pola {

/*
 *
 */
class LinuxDevice: public Device {
public:
	LinuxDevice(const DeviceParam& param);
	virtual ~LinuxDevice();

	virtual void run();

};

} /* namespace pola */

#endif /* LINUXDEVICE_H_ */
