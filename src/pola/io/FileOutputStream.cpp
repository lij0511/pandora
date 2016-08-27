/*
 * FileOutputStream.cpp
 *
 *  Created on: 2016年8月26日
 *      Author: lijing
 */

#include "pola/io/FileOutputStream.h"

namespace pola {
namespace io {

FileOutputStream::FileOutputStream(const char* file) {
	mFP = fopen(file, "wb");
}

FileOutputStream::~FileOutputStream() {
	close();
}

void FileOutputStream::flush() {
	if (!mFP) return;
	fflush(mFP);
}

void FileOutputStream::write(const void* buffer, size_t size) {
	if (!mFP) return;
	fwrite(buffer, 1, size, mFP);
}

void FileOutputStream::write(int oneByte) {
	if (!mFP) return;
	char c = oneByte;
	fwrite(&c, 1, 1, mFP);
}

void FileOutputStream::close() {
	OutputStream::close();
	if (mFP) {
		flush();
	}
	mFP = 0;
}

} /* namespace io */
} /* namespace pola */
