/*
 * InputStreamReader.h
 *
 *  Created on: 2016年5月31日
 *      Author: lijing
 */

#ifndef POLA_INPUTSTREAMREADER_H_
#define POLA_INPUTSTREAMREADER_H_

#include "pola/io/Reader.h"

namespace pola {
namespace io {

class InputStreamReader: public Reader {
public:
	InputStreamReader(InputStream* is);
	virtual ~InputStreamReader();

	virtual size_t read(void* buffer, size_t size);
	virtual int read();
	virtual size_t skip(size_t size);
	virtual size_t seek(size_t size);
	virtual bool rewind();

	virtual void close();

private:
	InputStream* mInputStream;
};

} /* namespace io */
} /* namespace pola */

#endif /* POLA_INPUTSTREAMREADER_H_ */
