/*
 * StringImpl.h
 *
 *  Created on: 2016年1月11日
 *      Author: lijing
 */

#ifndef POLA_STRINGIMPL_H_
#define POLA_STRINGIMPL_H_


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>

#include "log/Log.h"
#include "utils/RefBase.h"

#include "utils/JenkinsHash.h"

namespace pola {
namespace utils {

class String;

class StringImpl : public RefBase<StringImpl> {
private:
	friend class String;
	StringImpl() : m_data(nullptr), m_length(0), m_const(false), m_hash(0) {
	}
	StringImpl(const char* chars, size_t length) : m_length(length), m_const(false), m_hash(0) {
		char* tmp = new char[length + 1];
		memcpy(tmp, chars, length);
		*(tmp + m_length) = 0;
		m_data = tmp;
	}
	StringImpl(const char* str, bool isConst = false) : m_length(strlen(str)), m_const(isConst), m_hash(0) {
		char* tmp = new char[m_length + 1];
		for (size_t i = 0; i < m_length; i ++) {
			*(tmp + i) = str[i];
		}
		*(tmp + m_length) = 0;
		m_data = tmp;
	}
public:
	static StringImpl* emptyString() {
		return new StringImpl();
	}
	static StringImpl* create(const char* chars, size_t length) {
		return new StringImpl(chars, length);
	}
	static StringImpl* create(const char* str, bool isConst = false) {
		return new StringImpl(str, isConst);
	}

	~StringImpl() {
		if (!m_const && m_data != nullptr) {
			delete m_data;
		}
		m_data = nullptr;
		m_length = 0;
	}
	void print() const {
		printf("%s\n", m_data);
	}

	size_t length() const {
		return m_length;
	}

	bool isEmpty() const {
		return length() <= 0;
	}

	char charAt(size_t index) const {
		checkIndex(index);
		return *(m_data + index);
	}

	const char* characters() const {
		return m_data;
	}

	bool startsWith(const StringImpl& str, size_t start = 0) const {
		LOG_FATAL_IF((start < 0), "Can't be less than 0. start=%lud\n", start);
		size_t len = str.length();
		if (len <= 0 || len + start > length()) {
			return false;
		}
		return !memcmp(m_data + start, str.characters(), len);
	}

	bool endsWith(const StringImpl& str) const {
		size_t len = str.length();
		if (len <= 0 || len > length()) {
			return false;
		}
		return !memcmp(m_data + (length() - len), str.characters(), len);
	}

	bool contains(const StringImpl& str) const {
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
	bool operator==(const StringImpl& s) const {
		if (length() != s.length()) {
			return false;
		}
		if (length() > 0) {
			return !memcmp(m_data, s.m_data, length());
		}
		return true;
	}
	bool operator!=(const StringImpl& s) const {
		return !(*this == s);
	}
	bool operator>(const StringImpl& s) const {
		return compare(s) > 0;
	}
	bool operator>=(const StringImpl& s) const {
		return compare(s) >= 0;
	}
	bool operator<(const StringImpl& s) const {
		return compare(s) < 0;
	}
	bool operator<=(const StringImpl& s) const {
		return compare(s) <= 0;
	}

	hash_t hash() const {
		int hash = m_hash;
		if (hash == 0) {
			if (length() == 0) {
				return 0;
			}
			size_t len = length();
			for (size_t index = 0; index < len; index ++) {
				hash = JenkinsHashMix(hash, hash_type(charAt(index)));
			}
			hash = JenkinsHashWhiten(hash);
			m_hash = hash;
		}
		return hash;
	}

private:
	size_t compare(const StringImpl& s) const {
		for (size_t i = 0; i < length() && i < s.length(); i ++) {
			if (charAt(i) > s.charAt(i)) {
				return 1;
			} else if (charAt(i) < s.charAt(i)) {
				return -1;
			}
		}
		return length() - s.length();
	}
	void checkIndex(size_t index) const {
		if (index < 0 || index >= length()) {
			throwIndexOutOfBounds(index, length());
		}
	}
	void throwIndexOutOfBounds(int index, int len) const {
		printf("IndexOutOfBounds index=%d, length=%d!\n", index, len);
		throw "IndexOutOfBounds";
	}

	const char* m_data;
	size_t m_length;
	const bool m_const;

	mutable hash_t m_hash;
};
}
}

#endif /* POLA_STRINGIMPL_H_ */
