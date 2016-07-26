/*
 * String.h
 *
 *  Created on: 2015年11月22日
 *      Author: lijing
 */

#ifndef POLA_STRING_H_
#define POLA_STRING_H_

#include "pola/utils/StringImpl.h"
#include "pola/utils/TypeHelpers.h"

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

	String();
	String(const char* chars, size_t length);
	String(const char* str);
	String(const String& o);

	~String();

	void print() const;

	size_t length() const;

	bool isEmpty() const;

	char charAt(size_t index) const;

	const char* characters() const;

	bool startsWith(const String& str, size_t start = 0) const;

	bool endsWith(const String& str) const;

	bool equalIgnoringCase(const String& str);

	bool contains(const String& str) const;

	String lower();

	String upper();

	String trim();

	ssize_t indexOf(char c) const;

	ssize_t lastIndexOf(char c) const;

	String substring(size_t start);

	String substring(size_t start, size_t end);

	String& operator+=(const String& s);
	String& operator+=(const char* s);
	String& operator=(const char* s);
	String operator+(const String& s);
	String operator+(const char* s);

	/**
	 * operator compares.
	 */
	bool operator==(const String& s) const;
	bool operator!=(const String& s) const;
	bool operator>(const String& s) const;
	bool operator>=(const String& s) const;
	bool operator<(const String& s) const;
	bool operator<=(const String& s) const;

	char& operator[](size_t index);
	const char operator[](size_t index) const;

	hash_t hash() const;

private:
	friend class StringBuffer;
	String(char* chars, size_t length, bool istatic);

	sp<StringImpl> m_impl;
};

inline hash_t hash_type(const String& string) {
    return string.hash();
}
}
}

#endif /* POLA_STRING_H_ */
