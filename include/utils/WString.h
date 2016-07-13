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

/*
 *
 */
class WString {
public:
	WString();
	virtual ~WString();
};

} /* namespace utils */
} /* namespace pola */

#endif /* POLA_WSTRING_H_ */
