/*
 * InputSteamReader.h
 *
 *  Created on: 2016年5月31日
 *      Author: lijing
 */

#ifndef POLA_INPUTSTEAMREADER_H_
#define POLA_INPUTSTEAMREADER_H_

#include "io/Reader.h"

namespace pola {
namespace io {

class InputSteamReader: public Reader {
public:
	InputSteamReader(InputStream* is);
	virtual ~InputSteamReader();

	virtual size_t read(void* buffer, size_t size);
	virtual int read();
	virtual size_t skip(size_t size);
	virtual size_t seek(size_t size);
	virtual bool rewind();

	virtual size_t getPosition() const;

	virtual bool hasLength() const;
	virtual size_t getLength() const;

	virtual void close();

private:
	InputStream* mInputStream;
};

} /* namespace io */
} /* namespace pola */

#endif /* POLA_INPUTSTEAMREADER_H_ */
