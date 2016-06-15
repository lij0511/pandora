/*
 * StringImpl.h
 *
 *  Created on: 2016年1月11日
 *      Author: lijing
 */

#ifndef POLA_STRINGIMPL_H_
#define POLA_STRINGIMPL_H_

#include "log/Log.h"
#include "utils/RefBase.h"

#include "utils/JenkinsHash.h"

namespace pola {
namespace utils {

class String;

class StringImpl : public RefBase<StringImpl> {
private:
	friend class String;
	StringImpl();
	StringImpl(const char* chars, size_t length);
	StringImpl(const char* str, bool isConst = false);
public:
	static StringImpl* emptyString();
	static StringImpl* create(const char* chars, size_t length);
	static StringImpl* create(const char* str, bool isConst = false);

	~StringImpl();
	void print() const;

	size_t length() const;

	bool isEmpty() const;

	char charAt(size_t index) const;

	const char* characters() const;

	bool startsWith(const StringImpl& str, size_t start = 0) const;

	bool endsWith(const StringImpl& str) const;

	bool contains(const StringImpl& str) const;

	/**
	 * operator compares.
	 */
	bool operator==(const StringImpl& s) const;
	bool operator!=(const StringImpl& s) const;
	bool operator>(const StringImpl& s) const;
	bool operator>=(const StringImpl& s) const;
	bool operator<(const StringImpl& s) const;
	bool operator<=(const StringImpl& s) const;

	hash_t hash() const;

private:
	int32_t compare(const StringImpl& s) const;
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
