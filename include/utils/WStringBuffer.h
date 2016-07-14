/*
 * WStringBuffer.h
 *
 *  Created on: 2016年7月14日
 *      Author: lijing
 */

#ifndef POLA_WSTRINGBUFFER_H_
#define POLA_WSTRINGBUFFER_H_

#include "utils/WString.h"
#include "utils/Unicode.h"

#include <string.h>

namespace pola {
namespace utils {

/*
 *
 */
class WStringBuffer {
public:
	WStringBuffer();
	WStringBuffer(size_t capacity);
	WStringBuffer(const WStringBuffer& other);
	WStringBuffer& operator=(const WStringBuffer& other);

	virtual ~WStringBuffer();

	WStringBuffer& append(wchar cc);
	WStringBuffer& append(const wchar* data);
	WStringBuffer& append(const wchar* data, size_t len);
	WStringBuffer& append(const char* data);
	WStringBuffer& append(const char* data, size_t len);
	WStringBuffer& append(const WString& str);
	WStringBuffer& append(const WStringBuffer& str);

	const wchar* buffer() const;
	size_t length() const;
	bool isEmpty() const;

	void release(WString& str);
	void toString(WString& str);
	const WString toString() const;

	wchar charAt(size_t index) const;

	void reset();

private:

	void ensureCapacity(size_t minimumCapacity);
	size_t _grow(size_t newSize);

private:
	wchar* m_buffer;
	size_t m_length;
	size_t m_capacity;
};

} /* namespace utils */
} /* namespace pola */

#endif /* POLA_WSTRINGBUFFER_H_ */
