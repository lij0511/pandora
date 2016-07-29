/*
 * FileInputStream.h
 *
 *  Created on: 2015年12月13日
 *      Author: lijing
 */

#ifndef POLA_FILEINPUTSTREAM_H_
#define POLA_FILEINPUTSTREAM_H_

#include "pola/io/InputStream.h"

#include <stdio.h>

namespace pola {
namespace io {

class FileInputStream: public InputStream {
public:
	FileInputStream(const char* file);
	FileInputStream(FILE* fp);
	virtual ~FileInputStream();

	virtual size_t read(void* buffer, size_t length);
	virtual int read();
	virtual size_t skip(size_t length);
	virtual size_t seek(size_t size);
	virtual bool rewind();
	virtual void close();

	virtual size_t getPosition() const;

	virtual bool hasLength() const {return true;};
	virtual size_t getLength() const;

private:
	FILE* mFP;
};

}
}

#endif /* POLA_FILEINPUTSTREAM_H_ */
