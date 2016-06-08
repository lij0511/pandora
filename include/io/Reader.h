/*
 * Reader.h
 *
 *  Created on: 2016年5月31日
 *      Author: lijing
 */

#ifndef POLA_READER_H_
#define POLA_READER_H_

#include "io/InputStream.h"

namespace pola {
namespace io {

class Reader {
public:
	virtual ~Reader() {};

	virtual size_t read(void* buffer, size_t size) = 0;
	virtual int read() = 0;
	virtual size_t skip(size_t size) = 0;
	virtual size_t seek(size_t size) = 0;
	virtual bool rewind() = 0;

	virtual void close() = 0;
};

} /* namespace io */
} /* namespace pola */

#endif /* POLA_READER_H_ */
