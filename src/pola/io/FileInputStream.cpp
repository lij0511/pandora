/*
 * FileInputStream.cpp
 *
 *  Created on: 2015年12月13日
 *      Author: lijing
 */

#include "pola/io/FileInputStream.h"

#include <assert.h>

namespace pola {
namespace io {

FileInputStream::FileInputStream(const char* file) {
	mFP = fopen(file, "rb");
}

FileInputStream::FileInputStream(FILE* fp) : mFP(fp) {
}

FileInputStream::~FileInputStream() {
	close();
}

size_t FileInputStream::read(void* buffer, size_t length) {
	if (!mFP) return 0;
	return fread(buffer, 1, length, mFP);
}

int FileInputStream::read() {
	if (!mFP) return EOF;
	return fgetc(mFP);
}

size_t FileInputStream::skip(size_t length) {
	if (!mFP) return 0;
	return fseek(mFP, length, SEEK_CUR);
}

size_t FileInputStream::seek(size_t length) {
	if (!mFP) return 0;
	return fseek(mFP, length, SEEK_SET);
}

bool FileInputStream::rewind() {
	if (!mFP) return false;
	fseek(mFP, 0, SEEK_SET);
	return true;
}

void FileInputStream::close() {
	if (!isClosed()) {
		InputStream::close();
	}
	if (!mFP) return;
	fclose(mFP);
	mFP = 0;
}

size_t FileInputStream::getPosition() const {
	if (!mFP) return 0;
	return ftell(mFP);
}

size_t FileInputStream::getLength() const {
	if (!mFP) return 0;
	size_t cursor = ftell(mFP);
	fseek(mFP, 0, SEEK_END);
	size_t bytes = ftell(mFP);
	fseek(mFP, cursor, SEEK_SET);
	return bytes;
}

}
}
