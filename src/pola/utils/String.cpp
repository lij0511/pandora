/*
 * String.cpp
 *
 *  Created on: 2016年1月19日
 *      Author: lijing
 */

#include "pola/utils/String.h"
#include "pola/utils/StringBuffer.h"

namespace pola {
namespace utils {

bool isWhitespace(char cc)  {
    return cc == ' ' || cc == '\x0A' || cc == '\x09' || cc == '\x0C';
}
bool isASCII(char cc) {
	return !(cc & ~0x7F);
}
bool isASCIIAlpha(char cc) {
	return (cc | 0x20) >= 'a' && (cc | 0x20) <= 'z';
}
bool isASCIISpace(char cc) {
    return cc <= ' ' && (cc == ' ' || (cc <= 0xD && cc >= 0x9));
}
bool isASCIIUpper(char cc) {
	return cc >= 'A' && cc <= 'Z';
}
bool isASCIILower(char cc) {
	return cc >= 'a' && cc <= 'z';
}
bool isASCIIDigit(char cc) {
	return cc >= '0' && cc <= '9';
}
 bool isASCIIHexDigit(char cc) {
    return isASCIIDigit(cc) || ((cc | 0x20) >= 'a' && (cc | 0x20) <= 'f');
}
char toLowerCase(char cc) {
    if (isASCIIUpper(cc)) {
		const int lowerCaseOffset = 0x20;
		return cc + lowerCaseOffset;
    } else {
    	return cc;
    }
}
char toUpperCase(char cc) {
    if (isASCIILower(cc)) {
		const int lowerCaseOffset = 0x20;
		return cc - lowerCaseOffset;
    } else {
    	return cc;
    }
}

String::String() {
	m_impl = StringImpl::emptyString();
}
String::String(const char* chars, size_t length) {
	m_impl = StringImpl::create(chars, length);
}
String::String(const char* str) {
	m_impl = StringImpl::create(str);
}
String::String(const String& o) {
	m_impl = o.m_impl;
}

String::String(char* chars, size_t length, bool istatic) {
		if (istatic) {
			m_impl = new StringImpl;
			m_impl->m_data = chars;
			m_impl->m_length = length;
		} else {
			m_impl = StringImpl::create(chars, length);
		}
	}

String::~String() {
}
void String::print() const {
	m_impl->print();
}

size_t String::length() const {
	return m_impl->length();
}

bool String::isEmpty() const {
	return length() <= 0;
}

char String::charAt(size_t index) const {
	return m_impl->charAt(index);
}

const char* String::characters() const {
	return m_impl->characters();
}

bool String::startsWith(const String& str, size_t start) const {
	return m_impl->startsWith(*str.m_impl, start);
}

bool String::endsWith(const String& str) const {
	return m_impl->endsWith(*str.m_impl);
}

bool String::equalIgnoringCase(const String& str) {
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

bool String::contains(const String& str) const {
	return m_impl->contains(*(str.m_impl));
}

String String::lower() {
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
			char* datas = new char[len + 1];
			for (size_t index = 0; index < len; index ++) {
				datas[index] = toLowerCase(charAt(index));
			}
			datas[len] = 0;
			return String(datas, len, true);
		}
	}
	return *this;
}

String String::upper() {
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
			char* datas = new char[len + 1];
			for (size_t index = 0; index < len; index ++) {
				datas[index] = toUpperCase(charAt(index));
			}
			datas[len] = 0;
			return String(datas, len, true);
		}
	}
	return *this;
}

String String::trim() {
	ssize_t start = 0, last = length() - 1;
	ssize_t end = last;
	const char* chars = characters();
	while ((start <= end) && (chars[start] <= ' ')) {
		start++;
	}
	while ((end >= start) && (chars[end] <= ' ')) {
		end--;
	}
	if (start == 0 && end == last) {
		return *this;
	}
	return String(chars + start, size_t(end - start));
}

ssize_t String::indexOf(char c) const {
	ssize_t len = length();
	for (ssize_t i = 0; i < len; i ++) {
		if (c == charAt(i)) {
			return i;
		}
	}
	return -1;
}

ssize_t String::lastIndexOf(char c) const {
	for (ssize_t i = length() - 1; i >= 0; i --) {
		if (c == charAt(i)) {
			return i;
		}
	}
	return -1;
}

String String::substring(size_t start) {
	return substring(start, length());
}

String String::substring(size_t start, size_t end) {
	LOG_FATAL_IF((start >= end || end > length()), "Index out of bound, start=%u, end=%u, lenth=%u\n", start, end, length());
	return String(characters() + start, end - start);
}

String& String::operator+=(const String& s) {
	size_t len = s.length();
	if (len > 0) {
		StringBuffer sb(length() + len);
		sb.append(*this);
		sb.append(s);
		sb.release(*this);
	}
	return *this;
}

String& String::operator+=(const char* s) {
	size_t len = strlen(s);
	if (len > 0) {
		StringBuffer sb(length() + len);
		sb.append(*this);
		sb.append(s, len);
		sb.release(*this);
	}
	return *this;
}

String& String::operator=(const char* s) {
	*this = String(s);
	return *this;
}

String String::operator+(const String& s) {
	size_t len = s.length();
	if (len > 0) {
		StringBuffer sb(length() + len);
		sb.append(*this);
		sb.append(s);
		String result;
		sb.release(result);
		return result;
	}
	return *this;
}

String String::operator+(const char* s) {
	size_t len = strlen(s);
	if (len > 0) {
		StringBuffer sb(length() + len);
		sb.append(*this);
		sb.append(s, len);
		String result;
		sb.release(result);
		return result;
	}
	return *this;
}

/**
 * operator compares.
 */
bool String::operator==(const String& s) const {
	if (hash() != s.hash()) return false;
	return *m_impl == *s.m_impl;
}
bool String::operator!=(const String& s) const {
	return !(*this == s);
}
bool String::operator>(const String& s) const {
	return *m_impl > *s.m_impl;
}
bool String::operator>=(const String& s) const {
	return *m_impl >= *s.m_impl;
}
bool String::operator<(const String& s) const {
	return (s > *this);
}
bool String::operator<=(const String& s) const {
	return (s >= *this);
}

char& String::operator [](size_t index) {
	if (m_impl->getStrongCount() > 1) {
		m_impl = StringImpl::create(m_impl->characters(), m_impl->length());
	}
	return m_impl->characters()[index];
}

const char String::operator [](size_t index) const {
	return charAt(index);
}

hash_t String::hash() const {
	return m_impl->hash();
}
}
}

