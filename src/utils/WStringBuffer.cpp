/*
 * WWStringBuffer.cpp
 *
 *  Created on: 2016年7月14日
 *      Author: lijing
 */

#include "utils/WStringBuffer.h"

namespace pola {
namespace utils {

WStringBuffer::WStringBuffer() : WStringBuffer(0) {
}

WStringBuffer::WStringBuffer(size_t capacity) :
	m_buffer(nullptr), m_length(0), m_capacity(0) {
	ensureCapacity(capacity);
}
WStringBuffer::WStringBuffer(const WStringBuffer& other) {
	if (this != &other) {
		ensureCapacity(other.m_length + 1);
		m_length = other.m_length;
		memcpy(m_buffer, other.m_buffer, m_length * sizeof(wchar));
		*(m_buffer + m_length) = 0;
	}
}
WStringBuffer& WStringBuffer::operator=(const WStringBuffer& other) {
	if (this != &other) {
		ensureCapacity(other.m_length + 1);
		m_length = other.m_length;
		memcpy(m_buffer, other.m_buffer, m_length * sizeof(wchar));
		*(m_buffer + m_length) = 0;
	}
	return *this;
}

WStringBuffer::~WStringBuffer() {
	if (m_buffer) {
		delete m_buffer;
		m_buffer = nullptr;
	}
}

WStringBuffer& WStringBuffer::append(wchar cc) {
	if (m_length +1 >= m_capacity) {
		ensureCapacity(_grow(m_length + 1));
	}
	*(m_buffer + (m_length++)) = cc;
	*(m_buffer + m_length) = 0;
	return *this;
}
WStringBuffer& WStringBuffer::append(const wchar* data) {
	return append(data, wstrlen(data));
}
WStringBuffer& WStringBuffer::append(const wchar* data, size_t len) {
	if (len > 0) {
		if (m_length +len >= m_capacity) {
			ensureCapacity(_grow(m_length + len + 1));
		}
		memcpy(m_buffer + m_length, data, len * sizeof(wchar));
		m_length += len;
		*(m_buffer + m_length) = 0;
	}
	return *this;
}
WStringBuffer& WStringBuffer::append(const char* data) {
	return *this;
}
WStringBuffer& WStringBuffer::append(const char* data, size_t len) {
	return *this;
}
WStringBuffer& WStringBuffer::append(const WString& str) {
	return append(str.characters(), str.length());
}
WStringBuffer& WStringBuffer::append(const WStringBuffer& str) {
	return append(str.buffer(), str.length());
}

const wchar* WStringBuffer::buffer() const {
	return m_buffer;
}
size_t WStringBuffer::length() const {
	return m_length;
}
bool WStringBuffer::isEmpty() const {
	return m_length == 0;
}

void WStringBuffer::release(WString& str) {
	if (m_length > 0) {
		str = WString(m_buffer, m_length, true);
		m_length = 0;
		m_buffer = nullptr;
		m_capacity = 0;
	} else {
		str = WString(true);
	}
}

void WStringBuffer::toString(WString& str) {
	str = WString(m_buffer, m_length);
}

const WString WStringBuffer::toString() const {
	return WString(m_buffer, m_length);
}

wchar WStringBuffer::charAt(size_t index) const {
	if (index >= m_length) {
		return 0;
	}
	return *(m_buffer + index);
}

void WStringBuffer::reset() {
	if (m_length > 0) {
		m_length = 0;
		*m_buffer = 0;
	}
}

void WStringBuffer::ensureCapacity(size_t minimumCapacity) {
	if (m_capacity < minimumCapacity) {
		wchar* p = m_buffer;
		m_buffer = new wchar[minimumCapacity];
		memset(m_buffer, 0, minimumCapacity * sizeof(wchar));
		if (p) {
			memcpy(m_buffer, p, m_length * sizeof(wchar));
			delete p;
		}
		m_capacity = minimumCapacity;
	}
}

size_t WStringBuffer::_grow(size_t newSize) {
	return newSize * 3 / 2;
}

} /* namespace utils */
} /* namespace pola */
