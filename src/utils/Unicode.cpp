/*
 * Unicode.cpp
 *
 *  Created on: 2016年7月14日
 *      Author: lijing
 */

#include "utils/Unicode.h"

namespace pola {
namespace utils {

static const char32_t kByteMask = 0x000000BF;
static const char32_t kByteMark = 0x00000080;

// Surrogates aren't valid for UTF-32 characters, so define some
// constants that will let us screen them out.
static const char32_t kUnicodeSurrogateHighStart  = 0x0000D800;
static const char32_t kUnicodeSurrogateHighEnd    = 0x0000DBFF;
static const char32_t kUnicodeSurrogateLowStart   = 0x0000DC00;
static const char32_t kUnicodeSurrogateLowEnd     = 0x0000DFFF;
static const char32_t kUnicodeSurrogateStart      = kUnicodeSurrogateHighStart;
static const char32_t kUnicodeSurrogateEnd        = kUnicodeSurrogateLowEnd;
static const char32_t kUnicodeMaxCodepoint        = 0x0010FFFF;

// Mask used to set appropriate bits in first byte of UTF-8 sequence,
// indexed by number of bytes in the sequence.
// 0xxxxxxx
// -> (00-7f) 7bit. Bit mask for the first byte is 0x00000000
// 110yyyyx 10xxxxxx
// -> (c0-df)(80-bf) 11bit. Bit mask is 0x000000C0
// 1110yyyy 10yxxxxx 10xxxxxx
// -> (e0-ef)(80-bf)(80-bf) 16bit. Bit mask is 0x000000E0
// 11110yyy 10yyxxxx 10xxxxxx 10xxxxxx
// -> (f0-f7)(80-bf)(80-bf)(80-bf) 21bit. Bit mask is 0x000000F0
static const char32_t kFirstByteMark[] = {
    0x00000000, 0x00000000, 0x000000C0, 0x000000E0, 0x000000F0
};

size_t utf8_codepoint_len(uint8_t c);
void utf8_shift_and_mask(uint32_t& codePoint, const uint8_t byte);
uint32_t utf8_to_utf32_codepoint(const uint8_t *src, size_t length);
size_t utf32_codepoint_utf8_length(uint32_t srcChar);
void utf32_codepoint_to_utf8(uint8_t* dstP, uint32_t srcChar, size_t bytes);

size_t utf8_codepoint_len(uint8_t ch)
{
    return ((0xe5000000 >> ((ch >> 3) & 0x1e)) & 3) + 1;
}

void utf8_shift_and_mask(uint32_t& codePoint, const uint8_t byte)
{
    codePoint <<= 6;
    codePoint |= 0x3F & byte;
}

uint32_t utf8_to_utf32_codepoint(const uint8_t *src, size_t length)
{
    uint32_t unicode = 0;

    switch (length)
    {
        case 1:
            return src[0];
        case 2:
            unicode = src[0] & 0x1f;
            utf8_shift_and_mask(unicode, src[1]);
            return unicode;
        case 3:
            unicode = src[0] & 0x0f;
            utf8_shift_and_mask(unicode, src[1]);
            utf8_shift_and_mask(unicode, src[2]);
            return unicode;
        case 4:
            unicode = src[0] & 0x07;
            utf8_shift_and_mask(unicode, src[1]);
            utf8_shift_and_mask(unicode, src[2]);
            utf8_shift_and_mask(unicode, src[3]);
            return unicode;
        default:
            return 0xffff;
    }

    //printf("Char at %p: len=%d, utf-16=%p\n", src, length, (void*)result);
}

/**
 * Return number of UTF-8 bytes required for the character. If the character
 * is invalid, return size of 0.
 */
size_t utf32_codepoint_utf8_length(uint32_t srcChar)
{
    // Figure out how many bytes the result will require.
    if (srcChar < 0x00000080) {
        return 1;
    } else if (srcChar < 0x00000800) {
        return 2;
    } else if (srcChar < 0x00010000) {
        if ((srcChar < kUnicodeSurrogateStart) || (srcChar > kUnicodeSurrogateEnd)) {
            return 3;
        } else {
            // Surrogates are invalid UTF-32 characters.
            return 0;
        }
    }
    // Max code point for Unicode is 0x0010FFFF.
    else if (srcChar <= kUnicodeMaxCodepoint) {
        return 4;
    } else {
        // Invalid UTF-32 character.
        return 0;
    }
}

ssize_t utf8_to_utf16_length(const uint8_t* u8str, size_t u8len)
{
    const uint8_t* const u8end = u8str + u8len;
    const uint8_t* u8cur = u8str;

    /* Validate that the UTF-8 is the correct len */
    size_t u16measuredLen = 0;
    while (u8cur < u8end) {
        u16measuredLen++;
        int u8charLen = utf8_codepoint_len(*u8cur);
        uint32_t codepoint = utf8_to_utf32_codepoint(u8cur, u8charLen);
        if (codepoint > 0xFFFF) u16measuredLen++; // this will be a surrogate pair in utf16
        u8cur += u8charLen;
    }

    /**
     * Make sure that we ended where we thought we would and the output UTF-16
     * will be exactly how long we were told it would be.
     */
    if (u8cur != u8end) {
        return -1;
    }

    return u16measuredLen;
}

void utf8_to_utf16(const uint8_t* u8str, size_t u8len, wchar* u16str)
{
    const uint8_t* const u8end = u8str + u8len;
    const uint8_t* u8cur = u8str;
    wchar* u16cur = u16str;

    while (u8cur < u8end) {
        size_t u8len = utf8_codepoint_len(*u8cur);
        uint32_t codepoint = utf8_to_utf32_codepoint(u8cur, u8len);

        // Convert the UTF32 codepoint to one or more UTF16 codepoints
        if (codepoint <= 0xFFFF) {
            // Single UTF16 character
            *u16cur++ = (wchar) codepoint;
        } else {
            // Multiple UTF16 characters with surrogates
            codepoint = codepoint - 0x10000;
            *u16cur++ = (wchar) ((codepoint >> 10) + 0xD800);
            *u16cur++ = (wchar) ((codepoint & 0x3FF) + 0xDC00);
        }

        u8cur += u8len;
    }
    *u16cur = '\0';
}

ssize_t utf16_to_utf8_length(const wchar *src, size_t src_len)
{
    if (src == NULL || src_len == 0) {
        return -1;
    }

    size_t ret = 0;
    const wchar* const end = src + src_len;
    while (src < end) {
        if ((*src & 0xFC00) == 0xD800 && (src + 1) < end
                && (*++src & 0xFC00) == 0xDC00) {
            // surrogate pairs are always 4 bytes.
            ret += 4;
            src++;
        } else {
            ret += utf32_codepoint_utf8_length((char32_t) *src++);
        }
    }
    return ret;
}

void utf16_to_utf8(const wchar* src, size_t src_len, char* dst)
{
    if (src == NULL || src_len == 0 || dst == NULL) {
        return;
    }

    const wchar* cur_utf16 = src;
    const wchar* const end_utf16 = src + src_len;
    char *cur = dst;
    while (cur_utf16 < end_utf16) {
    	uint32_t utf32;
        // surrogate pairs
        if ((*cur_utf16 & 0xFC00) == 0xD800) {
            utf32 = (*cur_utf16++ - 0xD800) << 10;
            utf32 |= *cur_utf16++ - 0xDC00;
            utf32 += 0x10000;
        } else {
            utf32 = (uint32_t) *cur_utf16++;
        }
        const size_t len = utf32_codepoint_utf8_length(utf32);
        utf32_codepoint_to_utf8((uint8_t*)cur, utf32, len);
        cur += len;
    }
    *cur = '\0';
}

void utf32_codepoint_to_utf8(uint8_t* dstP, uint32_t srcChar, size_t bytes)
{
    dstP += bytes;
    switch (bytes)
    {   /* note: everything falls through. */
        case 4: *--dstP = (uint8_t)((srcChar | kByteMark) & kByteMask); srcChar >>= 6;
        case 3: *--dstP = (uint8_t)((srcChar | kByteMark) & kByteMask); srcChar >>= 6;
        case 2: *--dstP = (uint8_t)((srcChar | kByteMark) & kByteMask); srcChar >>= 6;
        case 1: *--dstP = (uint8_t)(srcChar | kFirstByteMark[bytes]);
    }
}

} /* namespace utils */
} /* namespace pola */
