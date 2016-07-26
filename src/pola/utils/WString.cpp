/*
 * WString.cpp
 *
 *  Created on: 2016年7月13日
 *      Author: lijing
 */

#include "pola/utils/WString.h"
#include "pola/utils/WStringBuffer.h"

namespace pola {
namespace utils {

bool isWhitespace(wchar cc)  {
    return cc == ' ' || cc == '\x0A' || cc == '\x09' || cc == '\x0C';
}
bool isASCII(wchar cc) {
	return !(cc & ~0x7F);
}
bool isASCIIAlpha(wchar cc) {
	return (cc | 0x20) >= 'a' && (cc | 0x20) <= 'z';
}
bool isASCIISpace(wchar cc) {
    return cc <= ' ' && (cc == ' ' || (cc <= 0xD && cc >= 0x9));
}
bool isASCIIUpper(wchar cc) {
	return cc >= 'A' && cc <= 'Z';
}
bool isASCIILower(wchar cc) {
	return cc >= 'a' && cc <= 'z';
}
bool isASCIIDigit(wchar cc) {
	return cc >= '0' && cc <= '9';
}
 bool isASCIIHexDigit(wchar cc) {
    return isASCIIDigit(cc) || ((cc | 0x20) >= 'a' && (cc | 0x20) <= 'f');
}
 wchar toLowerCase(wchar cc) {
    if (isASCIIUpper(cc)) {
		const int lowerCaseOffset = 0x20;
		return cc + lowerCaseOffset;
    } else {
    	return cc;
    }
}
wchar toUpperCase(wchar cc) {
    if (isASCIILower(cc)) {
		const int lowerCaseOffset = 0x20;
		return cc - lowerCaseOffset;
    } else {
    	return cc;
    }
}

WString::WString() {
	m_impl = WStringImpl::emptyString();
}
WString::WString(const char* chars) {
	m_impl = new WStringImpl;
	wchar* tmp = nullptr;
	utf8_to_utf16(chars, strlen(chars), tmp, m_impl->m_length);
	m_impl->m_data = tmp;
}
WString::WString(const wchar* chars, size_t length) {
	m_impl = WStringImpl::create(chars, length);
}
WString::WString(const wchar* str) {
	m_impl = WStringImpl::create(str);
}
WString::WString(const WString& o) {
	m_impl = o.m_impl;
}

WString::WString(const wchar* chars, size_t length, bool istatic) {
		if (istatic) {
			m_impl = new WStringImpl;
			m_impl->m_data = chars;
			m_impl->m_length = length;
		} else {
			m_impl = WStringImpl::create(chars, length);
		}
	}

WString::~WString() {
}
void WString::print() const {
	m_impl->print();
}

size_t WString::length() const {
	return m_impl->length();
}

bool WString::isEmpty() const {
	return length() <= 0;
}

wchar WString::charAt(size_t index) const {
	return m_impl->charAt(index);
}

const wchar* WString::characters() const {
	return m_impl->characters();
}

bool WString::startsWith(const WString& str, size_t start) const {
	return m_impl->startsWith(*str.m_impl, start);
}

bool WString::endsWith(const WString& str) const {
	return m_impl->endsWith(*str.m_impl);
}

bool WString::equalIgnoringCase(const WString& str) {
	if (*this == str) {
		return true;
	}
	if (length() != str.length()) {
		return false;
	}
	for (unsigned index = 0; index < length(); index ++) {
		if (toLowerCase(charAt(index)) != toLowerCase(str.charAt(index))) {
			return false;
		}
	}
	return true;
}

bool WString::contains(const WString& str) const {
	return m_impl->contains(*(str.m_impl));
}

WString WString::lower() {
	size_t len = length();
	if (len > 0) {
		bool hasUpper = false;
		for (size_t index = 0; index < len; index ++) {
			if (isASCIIUpper(charAt(index))) {
				hasUpper = true;
				break;
			}
		}
		if (hasUpper) {
			wchar* datas = new wchar[len + 1];
			for (size_t index = 0; index < len; index ++) {
				datas[index] = toLowerCase(charAt(index));
			}
			datas[len] = 0;
			return WString(datas, len, true);
		}
	}
	return *this;
}

WString WString::upper() {
	size_t len = length();
	if (len > 0) {
		bool hasLower = false;
		for (size_t index = 0; index < len; index ++) {
			if (isASCIILower(charAt(index))) {
				hasLower = true;
				break;
			}
		}
		if (hasLower) {
			wchar* datas = new wchar[len + 1];
			for (size_t index = 0; index < len; index ++) {
				datas[index] = toUpperCase(charAt(index));
			}
			datas[len] = 0;
			return WString(datas, len, true);
		}
	}
	return *this;
}

WString WString::trim() {
	ssize_t start = 0, last = length() - 1;
	ssize_t end = last;
	const wchar* chars = characters();
	while ((start <= end) && (chars[start] <= ' ')) {
		start++;
	}
	while ((end >= start) && (chars[end] <= ' ')) {
		end--;
	}
	if (start == 0 && end == last) {
		return *this;
	}
	return WString(chars + start, size_t(end - start));
}

ssize_t WString::indexOf(wchar c) const {
	ssize_t len = length();
	for (ssize_t i = 0; i < len; i ++) {
		if (c == charAt(i)) {
			return i;
		}
	}
	return -1;
}

ssize_t WString::lastIndexOf(wchar c) const {
	for (ssize_t i = length() - 1; i >= 0; i --) {
		if (c == charAt(i)) {
			return i;
		}
	}
	return -1;
}

WString WString::substring(size_t start) {
	return substring(start, length());
}

WString WString::substring(size_t start, size_t end) {
	LOG_FATAL_IF((start >= end || end > length()), "Index out of bound, start=%u, end=%u, lenth=%u\n", start, end, length());
	return WString(characters() + start, end - start);
}

WString& WString::operator+=(const WString& s) {
	size_t len = s.length();
	if (len > 0) {
		WStringBuffer sb(length() + len);
		sb.append(*this);
		sb.append(s);
		sb.release(*this);
	}
	return *this;
}

WString& WString::operator+=(const wchar* s) {
	size_t len = wstrlen(s);
	if (len > 0) {
		WStringBuffer sb(length() + len);
		sb.append(*this);
		sb.append(s, len);
		sb.release(*this);
	}
	return *this;
}

WString& WString::operator=(const wchar* s) {
	*this = WString(s);
	return *this;
}

WString WString::operator+(const WString& s) {
	size_t len = s.length();
	if (len > 0) {
		WStringBuffer sb(length() + len);
		sb.append(*this);
		sb.append(s);
		WString result;
		sb.release(result);
		return result;
	}
	return *this;
}

WString WString::operator+(const wchar* s) {
	size_t len = wstrlen(s);
	if (len > 0) {
		WStringBuffer sb(length() + len);
		sb.append(*this);
		sb.append(s, len);
		WString result;
		sb.release(result);
		return result;
	}
	return *this;
}

/**
 * operator compares.
 */
bool WString::operator==(const WString& s) const {
	if (hash() != s.hash()) return false;
	return *m_impl == *s.m_impl;
}
bool WString::operator!=(const WString& s) const {
	return !(*this == s);
}
bool WString::operator>(const WString& s) const {
	return *m_impl > *s.m_impl;
}
bool WString::operator>=(const WString& s) const {
	return *m_impl >= *s.m_impl;
}
bool WString::operator<(const WString& s) const {
	return (s > *this);
}
bool WString::operator<=(const WString& s) const {
	return (s >= *this);
}

hash_t WString::hash() const {
	return m_impl->hash();
}

} /* namespace utils */
} /* namespace pola */
