/*
 * OutputStream.h
 *
 *  Created on: 2016年8月26日
 *      Author: lijing
 */

#ifndef POLA_OUTPUTSTREAM_H_
#define POLA_OUTPUTSTREAM_H_

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <assert.h>

namespace pola {
namespace io {

/*
 *
 */
class OutputStream {
public:
	OutputStream();
	virtual ~OutputStream();

	virtual void flush();

	virtual void write(const void* buffer, size_t size) = 0;

	virtual void write(int oneByte) = 0;

	bool isClosed() const {
		return mClosed;
	}
	virtual void close() {
		mClosed = true;
	}

private:
	bool mClosed;
};

} /* namespace io */
} /* namespace pola */

#endif /* POLA_OUTPUTSTREAM_H_ */
