/*
 * StringBuffer.h
 *
 *  Created on: 2015年12月24日
 *      Author: lijing
 */

#include "utils/String.h"

#include <string.h>

#ifndef POLA_STRINGBUFFER_H_
#define POLA_STRINGBUFFER_H_

namespace pola {
namespace utils {

class StringBuffer {
public:
	StringBuffer();
	StringBuffer(size_t capacity);
	StringBuffer(const StringBuffer& other);
	StringBuffer& operator=(const StringBuffer& other);

	virtual ~StringBuffer();

	void append(char cc);
	void append(char* data, size_t len);
	void append(const char* data, size_t len);
	void append(const String& str);
	void append(const StringBuffer& str);

	const char* buffer() const;
	const size_t length() const;
	const bool isEmpty() const;

	void release(String& str);
	void toString(String& str);
	const String toString() const;

	char charAt(size_t index) const;

	void reset();

private:

	void ensureCapacity(size_t minimumCapacity);
	size_t _grow(size_t newSize);

private:
	char* m_buffer;
	size_t m_length;
	size_t m_capacity;
};

}
}

#endif /* POLA_STRINGBUFFER_H_ */
