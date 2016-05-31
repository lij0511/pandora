/*
 * InputSteamReader.cpp
 *
 *  Created on: 2016年5月31日
 *      Author: lijing
 */

#include "io/InputSteamReader.h"

namespace pola {
namespace io {

InputSteamReader::InputSteamReader(InputStream* is) : mInputStream(is) {
}

InputSteamReader::~InputSteamReader() {
}

size_t InputSteamReader::read(void* buffer, size_t size) {
	return mInputStream->read(buffer, size);
}
int InputSteamReader::read() {
	return mInputStream->read();
}
size_t InputSteamReader::skip(size_t size) {
	return mInputStream->skip(size);
}
size_t InputSteamReader::seek(size_t size) {
	return mInputStream->seek(size);
}
bool InputSteamReader::rewind() {
	return mInputStream->rewind();
}

size_t InputSteamReader::getPosition() const {
	return mInputStream->getPosition();
}

bool InputSteamReader::hasLength() const {
	return mInputStream->hasLength();
}
size_t InputSteamReader::getLength() const {
	return mInputStream->getLength();
}

void InputSteamReader::close() {
	Reader::close();
	mInputStream->close();
}

} /* namespace io */
} /* namespace pola */
