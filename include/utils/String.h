/*
 * String.h
 *
 *  Created on: 2015年11月22日
 *      Author: lijing
 */

#ifndef POLA_STRING_H_
#define POLA_STRING_H_

#include "utils/StringImpl.h"
#include "utils/TypeHelpers.h"

namespace pola {
namespace utils {

bool isWhitespace(char cc);
bool isASCII(char cc);
bool isASCIIAlpha(char cc);
bool isASCIISpace(char cc);
bool isASCIIUpper(char cc);
bool isASCIILower(char cc);
bool isASCIIDigit(char cc);
bool isASCIIHexDigit(char cc);
char toLowerCase(char cc);
char toUpperCase(char cc);

class StringBuffer;

class String {
public:

	String(bool null = false) {
		if (!null) {
			m_impl = StringImpl::emptyString();
		}
	}
	String(char* chars, size_t length) {
		m_impl = StringImpl::create(chars, length);
	}
	String(const char* chars, size_t length) {
		m_impl = StringImpl::create(chars, length);
	}
	String(const char* str, bool isConst = false) {
		m_impl = StringImpl::create(str, isConst);
	}

	~String() {
	}
	void print() const {
		impl() ? m_impl->print() : (void)0;
	}

	size_t length() const {
		return impl() ? m_impl->length() : 0;
	}

	bool isEmpty() const {
		return length() <= 0;
	}

	bool isNull() const {
		return !impl();
	}

	char charAt(size_t index) const {
		return impl() ? m_impl->charAt(index) : 0;
	}

	const char* characters() const {
		return impl() ? m_impl->characters() : nullptr;
	}

	const StringImpl* impl() const {
		return m_impl.get();
	}

	bool startsWith(const String& str, size_t start = 0) const {
		return impl() && m_impl->startsWith(*str.impl(), start);
	}

	bool endsWith(const String& str) const {
		return impl() && str.impl() && m_impl->endsWith(*str.impl());
	}

	bool equalIgnoringCase(const String& str) {
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

	bool contains(const String& str) const {
		return impl() && str.impl() && m_impl->contains(*(str.m_impl));
	}

	String lower() {
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

	String upper() {
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

	/**
	 * operator compares.
	 */
	bool operator==(const String& s) const {
		if (hash() != s.hash()) return false;
		if (impl() && s.impl()) {
			return *m_impl == *s.impl();
		}
		return !impl() && !s.impl();
	}
	bool operator!=(const String& s) const {
		return !(*this == s);
	}
	bool operator>(const String& s) const {
		if (impl() && s.impl()) {
			return *m_impl > *s.impl();
		}
		return impl();
	}
	bool operator>=(const String& s) const {
		if (impl() && s.impl()) {
			return *m_impl >= *s.impl();
		}
		return impl();
	}
	bool operator<(const String& s) const {
		return (s > *this);
	}
	bool operator<=(const String& s) const {
		return (s >= *this);
	}

	hash_t hash() const {
		return impl() ? impl()->hash() : 0;
	}

private:
	friend class StringBuffer;
	String(const char* chars, size_t length, bool istatic) {
		if (istatic) {
			m_impl = new StringImpl;
			m_impl->m_data = chars;
			m_impl->m_length = length;
		} else {
			m_impl = StringImpl::create(chars, length);
		}
	}

	sp<StringImpl> m_impl;
};

inline hash_t hash_type(const String& string) {
    return string.hash();
}
}
}

#endif /* POLA_STRING_H_ */
