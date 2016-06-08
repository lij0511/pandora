/*
 * BufferedReader.cpp
 *
 *  Created on: 2016年6月8日
 *      Author: lijing
 */

#include "log/Log.h"
#include "io/BufferedReader.h"

namespace pola {
namespace io {

BufferedReader::BufferedReader(Reader* reader, size_t bufSize) : mReader(reader), mPosition(0), mEnd(0) {
	LOG_FATAL_IF(bufSize == 0, "Buffer Size must not be 0.\n");
	mBuffer = new char[bufSize];
	mBufferSize = bufSize;
}

BufferedReader::~BufferedReader() {
	close();
}

size_t BufferedReader::read(void* buffer, size_t size) {
	// TODO
	return mReader->read(buffer, size);
}
int BufferedReader::read() {
	// TODO
	return mReader->read();
}
size_t BufferedReader::skip(size_t size) {
	if (mPosition + size <= mEnd) {
		mPosition += size;
		return size;
	}
	mPosition = mEnd = 0;
	return mReader->skip(mPosition + size - mEnd);
}
size_t BufferedReader::seek(size_t size) {
	mPosition = mEnd = 0;
	return mReader->seek(size);
}
bool BufferedReader::rewind() {
	bool r = mReader->rewind();
	if (r) {
		mPosition = mEnd = 0;
	}
	return r;
}

bool BufferedReader::readLine(utils::String& line) {
	// TODO
	return false;
}

void BufferedReader::close() {
	mReader->close();
	if (mBuffer != nullptr) {
		delete mBuffer;
		mBuffer = nullptr;
	}
}

int BufferedReader::fillBuffer() {
	int result = mReader->read(mBuffer, mBufferSize);
	if (result > 0) {
		mPosition = 0;
		mEnd = result;
	}
	return result;
}

} /* namespace io */
} /* namespace pola */
