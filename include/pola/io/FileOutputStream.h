/*
 * FileOutputStream.h
 *
 *  Created on: 2016年8月26日
 *      Author: lijing
 */

#ifndef POLA_FILEOUTPUTSTREAM_H_
#define POLA_FILEOUTPUTSTREAM_H_

#include "pola/io/OutputStream.h"

#include <stdio.h>

namespace pola {
namespace io {

/*
 *
 */
class FileOutputStream: public OutputStream {
public:
	FileOutputStream(const char* file);
	virtual ~FileOutputStream();

	virtual void flush();

	virtual void write(const void* buffer, size_t size);

	virtual void write(int oneByte);

	virtual void close();

private:
	FILE* mFP;
};

} /* namespace io */
} /* namespace pola */

#endif /* POLA_FILEOUTPUTSTREAM_H_ */
