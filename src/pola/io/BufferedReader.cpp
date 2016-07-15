/*
 * BufferedReader.cpp
 *
 *  Created on: 2016年6月8日
 *      Author: lijing
 */

#include "pola/log/Log.h"
#include "pola/utils/StringBuffer.h"
#include "pola/io/BufferedReader.h"

namespace pola {
namespace io {

BufferedReader::BufferedReader(Reader* reader, size_t bufSize) : mReader(reader), mPosition(0), mEnd(0) {
	LOG_FATAL_IF(bufSize == 0, "Buffer Size must not be 0.\n");
	mBuffer = new char[bufSize];
	mBufferSize = bufSize;
	mLastWasCR = false;
}

BufferedReader::~BufferedReader() {
	close();
}

size_t BufferedReader::read(void* buffer, size_t size) {
	if (size == 0) {
		return 0;
	}

	maybeSwallowLF();

	ssize_t length = ssize_t(size);
	ssize_t outstanding = length;
	while (outstanding > 0) {
		// If there are chars in the buffer, grab those first.
		int32_t available = mEnd - mPosition;
		if (available > 0) {
			int count = available >= outstanding ? outstanding : available;
			memcpy(buffer, mBuffer + mPosition, count);
			mPosition += count;
			outstanding -= count;
		}

		if (outstanding == 0 || outstanding < length) {
			break;
		}

		if (fillBuffer() <= 0) {
			break; // source is exhausted
		}
	}
	ssize_t count = length - outstanding;
	if (count > 0) {
		return count;
	}
	return EOF;
}
int BufferedReader::read() {
	int ch = readChar();
	if (mLastWasCR && ch == '\n') {
		ch = readChar();
	}
	mLastWasCR = false;
	return ch;
}
int BufferedReader::readChar() {
	if (mPosition < mEnd || fillBuffer() > 0) {
		return mBuffer[mPosition++];
	}
	return EOF;
}

size_t BufferedReader::skip(size_t size) {
	if (mPosition + ssize_t(size) <= mEnd) {
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
	maybeSwallowLF();

	// Do we have a whole line in the buffer?
	for (int32_t i = mPosition; i < mEnd; ++ i) {
		char ch = mBuffer[i];
		if (ch == '\n' || ch == '\r') {
			line = utils::String(mBuffer + mPosition, size_t(i - mPosition));
			mPosition = i + 1;
			mLastWasCR = (ch == '\r');
			return true;
		}
	}

	utils::StringBuffer sb;
	sb.append(mBuffer + mPosition, size_t(mEnd - mPosition));
	while (true) {
		mPosition = mEnd;
		if (fillBuffer() <= 0) {
			// If there's no more input, return what we've read so far, if anything.
			if (sb.length() > 0) {
				sb.release(line);
				return true;
			} else {
				return false;
			}
		}

		// Do we have a whole line in the buffer now?
		for (int32_t i = mPosition; i < mEnd; ++ i) {
			char ch = mBuffer[i];
			if (ch == '\n' || ch == '\r') {
				sb.append(mBuffer + mPosition, size_t(i - mPosition));
				mPosition = i + 1;
				mLastWasCR = (ch == '\r');
				sb.release(line);
				return true;
			}
		}

		// Add this whole buffer to the line-in-progress and try again...
		sb.append(mBuffer + mPosition, size_t(mEnd - mPosition));
	}
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

void BufferedReader::chompNewline() {
	if ((mPosition != mEnd || fillBuffer() > 0) && mBuffer[mPosition] == '\n') {
		++ mPosition;
	}
}

void BufferedReader::maybeSwallowLF() {
	if (mLastWasCR) {
		chompNewline();
		mLastWasCR = false;
	}
}

} /* namespace io */
} /* namespace pola */
