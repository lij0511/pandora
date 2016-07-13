/*
 * WStringImpl.cpp
 *
 *  Created on: 2016年7月13日
 *      Author: lijing
 */

#include "utils/WStringImpl.h"

namespace pola {
namespace utils {

WStringImpl::WStringImpl() : m_data(nullptr), m_length(0), m_hash(0) {
}
WStringImpl::WStringImpl(const wchar* chars, size_t length) : m_length(length), m_hash(0) {
	wchar* tmp = new wchar[length + 1];
	memcpy(tmp, chars, length * sizeof(wchar));
	*(tmp + m_length) = 0;
	m_data = tmp;
}
WStringImpl::WStringImpl(const wchar* str) : m_length(wstrlen(str)), m_hash(0) {
	wchar* tmp = new wchar[m_length + 1];
	memcpy(tmp, str, m_length * sizeof(wchar));
	*(tmp + m_length) = 0;
	m_data = tmp;
}

WStringImpl* WStringImpl::emptyString() {
	static sp<WStringImpl> emptyS = new WStringImpl();
	return emptyS.get();
}
WStringImpl* WStringImpl::create(const wchar* chars, size_t length) {
	return new WStringImpl(chars, length);
}
WStringImpl* WStringImpl::create(const wchar* str) {
	return new WStringImpl(str);
}

WStringImpl::~WStringImpl() {
	if (m_data != nullptr) {
		delete m_data;
	}
	m_data = nullptr;
	m_length = 0;
}
void WStringImpl::print() const {
	for (unsigned i = 0; i < m_length; i ++) {
		printf("%c", m_data[i]);
	}
	printf("\n");
}

size_t WStringImpl::length() const {
	return m_length;
}

bool WStringImpl::isEmpty() const {
	return length() <= 0;
}

wchar WStringImpl::charAt(size_t index) const {
	checkIndex(index);
	return *(m_data + index);
}

const wchar* WStringImpl::characters() const {
	return m_data;
}

bool WStringImpl::startsWith(const WStringImpl& str, size_t start) const {
	size_t len = str.length();
	if (len <= 0 || len + start > length()) {
		return false;
	}
	return !memcmp(m_data + start, str.characters(), len * sizeof(wchar));
}

bool WStringImpl::endsWith(const WStringImpl& str) const {
	size_t len = str.length();
	if (len <= 0 || len > length()) {
		return false;
	}
	return !memcmp(m_data + (length() - len), str.characters(), len * sizeof(wchar));
}

bool WStringImpl::contains(const WStringImpl& str) const {
	size_t len = str.length();
	if (len <= 0 || len > length()) {
		return false;
	}
	for (size_t i = 0; i < length() - len; i ++) {
		if (startsWith(str, i)) {
			return true;
		}
	}
	return false;
}

/**
 * operator compares.
 */
bool WStringImpl::operator==(const WStringImpl& s) const {
	if (length() != s.length()) {
		return false;
	}
	if (length() > 0) {
		return !memcmp(m_data, s.m_data, length() * sizeof(wchar));
	}
	return true;
}
bool WStringImpl::operator!=(const WStringImpl& s) const {
	return !(*this == s);
}
bool WStringImpl::operator>(const WStringImpl& s) const {
	return compare(s) > 0;
}
bool WStringImpl::operator>=(const WStringImpl& s) const {
	return compare(s) >= 0;
}
bool WStringImpl::operator<(const WStringImpl& s) const {
	return compare(s) < 0;
}
bool WStringImpl::operator<=(const WStringImpl& s) const {
	return compare(s) <= 0;
}

hash_t WStringImpl::hash() const {
	int hash = m_hash;
	if (hash == 0) {
		if (length() == 0) {
			return 0;
		}
		size_t len = length();
		for (size_t index = 0; index < len; index ++) {
			hash = JenkinsHashMix(hash, charAt(index));
		}
		hash = JenkinsHashWhiten(hash);
		m_hash = hash;
	}
	return hash;
}

int32_t WStringImpl::compare(const WStringImpl& s) const {
	for (size_t i = 0; i < length() && i < s.length(); i ++) {
		if (charAt(i) > s.charAt(i)) {
			return 1;
		} else if (charAt(i) < s.charAt(i)) {
			return -1;
		}
	}
	return length() - s.length();
}

} /* namespace utils */
} /* namespace pola */
