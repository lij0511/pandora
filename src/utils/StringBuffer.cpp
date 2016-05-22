/*
 * StringBuffer.cpp
 *
 *  Created on: 2015年12月24日
 *      Author: lijing
 */

#include "utils/StringBuffer.h"

namespace pola {
namespace utils {

StringBuffer::StringBuffer() : StringBuffer(0) {
}

StringBuffer::StringBuffer(size_t capacity) :
	m_buffer(nullptr), m_length(0), m_capacity(0) {
	ensureCapacity(capacity);
}
StringBuffer::StringBuffer(const StringBuffer& other) {
	if (this != &other) {
		ensureCapacity(other.m_length + 1);
		m_length = other.m_length;
		memcpy(m_buffer, other.m_buffer, m_length * sizeof(char));
		*(m_buffer + m_length) = 0;
	}
}
StringBuffer& StringBuffer::operator=(const StringBuffer& other) {
	if (this != &other) {
		ensureCapacity(other.m_length + 1);
		m_length = other.m_length;
		memcpy(m_buffer, other.m_buffer, m_length * sizeof(char));
		*(m_buffer + m_length) = 0;
	}
	return *this;
}

StringBuffer::~StringBuffer() {
	if (m_buffer) {
		delete m_buffer;
		m_buffer = nullptr;
	}
}

void StringBuffer::append(char cc) {
	if (m_length +1 >= m_capacity) {
		ensureCapacity(_grow(m_length + 1));
	}
	*(m_buffer + (m_length++)) = cc;
	*(m_buffer + m_length) = 0;
}
void StringBuffer::append(char* data, size_t len) {
	if (len > 0) {
		if (m_length +len >= m_capacity) {
			ensureCapacity(_grow(m_length + len + 1));
		}
		memcpy(m_buffer + m_length, data, len * sizeof(char));
		m_length += len;
		*(m_buffer + m_length) = 0;
	}
}
void StringBuffer::append(const char* data, size_t len) {
	if (len > 0) {
		if (m_length +len >= m_capacity) {
			ensureCapacity(_grow(m_length + len + 1));
		}
		memcpy(m_buffer + m_length, data, len * sizeof(char));
		m_length += len;
		*(m_buffer + m_length) = 0;
	}
}
void StringBuffer::append(const String& str) {
	append(str.characters(), str.length());
}
void StringBuffer::append(const StringBuffer& str) {
	append(str.buffer(), str.length());
}

const char* StringBuffer::buffer() const {
	return m_buffer;
}
const size_t StringBuffer::length() const {
	return m_length;
}
const bool StringBuffer::isEmpty() const {
	return m_length == 0;
}

void StringBuffer::release(String& str) {
	if (m_length > 0) {
		str = String(m_buffer, m_length, true);
		m_length = 0;
		m_buffer = nullptr;
		m_capacity = 0;
	} else {
		str = String(true);
	}
}

void StringBuffer::toString(String& str) {
	str = String(m_buffer, m_length);
}

const String StringBuffer::toString() const {
	return String(m_buffer, m_length);
}

char StringBuffer::charAt(size_t index) const {
	if (index >= m_length) {
		return 0;
	}
	return *(m_buffer + index);
}

void StringBuffer::reset() {
	if (m_length > 0) {
		m_length = 0;
		*m_buffer = 0;
	}
}

void StringBuffer::ensureCapacity(size_t minimumCapacity) {
	if (m_capacity < minimumCapacity) {
		char* p = m_buffer;
		m_buffer = new char[minimumCapacity];
		memset(m_buffer, 0, minimumCapacity * sizeof(char));
		if (p) {
			memcpy(m_buffer, p, m_length * sizeof(char));
			delete p;
		}
		m_capacity = minimumCapacity;
	}
}

size_t StringBuffer::_grow(size_t newSize) {
	return newSize * 3 / 2;
}

}
}
