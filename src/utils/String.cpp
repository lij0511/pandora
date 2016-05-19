/*
 * String.cpp
 *
 *  Created on: 2016年1月19日
 *      Author: lijing
 */

#include "utils/String.h"

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

}
}

