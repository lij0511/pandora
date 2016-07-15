/*
 * InputStreamReader.cpp
 *
 *  Created on: 2016年5月31日
 *      Author: lijing
 */

#include "pola/io/InputStreamReader.h"

namespace pola {
namespace io {

InputStreamReader::InputStreamReader(InputStream* is) : mInputStream(is) {
}

InputStreamReader::~InputStreamReader() {
}

size_t InputStreamReader::read(void* buffer, size_t size) {
	return mInputStream->read(buffer, size);
}
int InputStreamReader::read() {
	return mInputStream->read();
}
size_t InputStreamReader::skip(size_t size) {
	return mInputStream->skip(size);
}
size_t InputStreamReader::seek(size_t size) {
	return mInputStream->seek(size);
}
bool InputStreamReader::rewind() {
	return mInputStream->rewind();
}

void InputStreamReader::close() {
	mInputStream->close();
}

} /* namespace io */
} /* namespace pola */
