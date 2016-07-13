/*
 * WString.cpp
 *
 *  Created on: 2016年7月13日
 *      Author: lijing
 */

#include "utils/WString.h"

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
}

WString::~WString() {
}

} /* namespace utils */
} /* namespace pola */
