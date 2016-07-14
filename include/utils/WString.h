/*
 * WString.h
 *
 *  Created on: 2016年7月13日
 *      Author: lijing
 */

#ifndef POLA_WSTRING_H_
#define POLA_WSTRING_H_

#include "utils/WStringImpl.h"

namespace pola {
namespace utils {

bool isWhitespace(wchar cc);
bool isASCII(wchar cc);
bool isASCIIAlpha(wchar cc);
bool isASCIISpace(wchar cc);
bool isASCIIUpper(wchar cc);
bool isASCIILower(wchar cc);
bool isASCIIDigit(wchar cc);
bool isASCIIHexDigit(wchar cc);
wchar toLowerCase(wchar cc);
wchar toUpperCase(wchar cc);

class WStringBuffer;

/*
 *
 */
class WString {
public:
	WString(bool null = true);
	WString(const char* str);
	WString(const wchar* str);
	WString(const wchar* chars, size_t length);
	WString(const WString& o);

	~WString();

	void print() const;

	size_t length() const;

	bool isEmpty() const;

	bool isNull() const;

	wchar charAt(size_t index) const;

	const wchar* characters() const;

	const WStringImpl* impl() const;

	bool startsWith(const WString& str, size_t start = 0) const;

	bool endsWith(const WString& str) const;

	bool equalIgnoringCase(const WString& str);

	bool contains(const WString& str) const;

	WString lower();

	WString upper();

	WString trim();

	ssize_t indexOf(wchar c) const;

	ssize_t lastIndexOf(wchar c) const;

	WString substring(size_t start);

	WString substring(size_t start, size_t end);

	WString& operator+=(const WString& s);
	WString& operator+=(const wchar* s);
	WString& operator=(const wchar* s);
	WString operator+(const WString& s);
	WString operator+(const wchar* s);

	/**
	 * operator compares.
	 */
	bool operator==(const WString& s) const;
	bool operator!=(const WString& s) const;
	bool operator>(const WString& s) const;
	bool operator>=(const WString& s) const;
	bool operator<(const WString& s) const;
	bool operator<=(const WString& s) const;

	hash_t hash() const;

private:
	friend class WStringBuffer;
	WString(const wchar* chars, size_t length, bool istatic);

	sp<WStringImpl> m_impl;
};

inline hash_t hash_type(const WString& string) {
    return string.hash();
}

} /* namespace utils */
} /* namespace pola */

#endif /* POLA_WSTRING_H_ */
