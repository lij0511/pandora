/*
 * FileInputStream.h
 *
 *  Created on: 2015年12月13日
 *      Author: lijing
 */

#ifndef POLA_FILEINPUTSTREAM_H_
#define POLA_FILEINPUTSTREAM_H_

#include "io/InputStream.h"

#include <stdio.h>

namespace pola {
namespace io {

class FileInputStream: public InputStream {
public:
	FileInputStream(const char* file);
	FileInputStream(FILE* fp);
	virtual ~FileInputStream();

	virtual size_t read(void* buffer, size_t length) override;
	virtual uint8_t read() override;
	virtual size_t skip(size_t length) override;
	virtual size_t seek(size_t size) override;
	virtual bool rewind() override;
	virtual void close() override;

private:
	FILE* mFP;
};

}
}

#endif /* POLA_FILEINPUTSTREAM_H_ */
