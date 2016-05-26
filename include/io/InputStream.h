/*
 * InputStream.h
 *
 *  Created on: 2015年12月13日
 *      Author: lijing
 */

#ifndef POLA_INPUTSTREAM_H_
#define POLA_INPUTSTREAM_H_

#include <stdint.h>
#include <stddef.h>
#include <assert.h>

namespace pola {
namespace io {

class InputStream {
public:
	InputStream();
	virtual ~InputStream();

	virtual size_t read(void* buffer, size_t size) = 0;
	virtual uint8_t read() = 0;
	virtual size_t skip(size_t size) = 0;
	virtual size_t seek(size_t size) = 0;
	virtual bool rewind() = 0;

	/** Returns true if this stream can report it's total length. */
	virtual bool hasLength() const { return false; }
	/** Returns the total length of the stream. If this cannot be done, returns 0. */
	virtual size_t getLength() const { return 0; }

	virtual void close() {
		assert(!mClosed);
		mClosed = true;
	}

private:
	bool mClosed;
};

}
}

#endif /* POLA_INPUTSTREAM_H_ */
