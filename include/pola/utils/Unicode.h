/*
 * Unicode.h
 *
 *  Created on: 2016年7月14日
 *      Author: lijing
 */

#ifndef POLA_UNICODE_H_
#define POLA_UNICODE_H_

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

typedef uint16_t wchar;

namespace pola {
namespace utils {

ssize_t utf8_to_utf16_length(const uint8_t* u8str, size_t u8len);
void utf8_to_utf16(const uint8_t* u8str, size_t u8len, wchar* u16str);

ssize_t utf16_to_utf8_length(const wchar *src, size_t src_len);
void utf16_to_utf8(const wchar* src, size_t src_len, char* dst);

} /* namespace utils */
} /* namespace pola */

#endif /* UNICODE_H_ */
