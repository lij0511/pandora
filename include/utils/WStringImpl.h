/*
 * WStringImpl.h
 *
 *  Created on: 2016年7月13日
 *      Author: lijing
 */

#ifndef POLA_WSTRINGIMPL_H_
#define POLA_WSTRINGIMPL_H_

#include "utils/RefBase.h"
#include "utils/JenkinsHash.h"

typedef uint16_t wchar;

size_t wstrlen(const wchar* wstr) {
	const wchar *ss = wstr;
	while (*ss)
		ss++;
	return ss - wstr;
}

namespace pola {
namespace utils {

class WString;

/*
 *
 */
class WStringImpl: public RefBase<WStringImpl> {
private:
	friend class WString;
	WStringImpl();
	WStringImpl(const wchar* chars, size_t length);
	WStringImpl(const wchar* str);
public:
	static WStringImpl* emptyString();
	static WStringImpl* create(const wchar* chars, size_t length);
	static WStringImpl* create(const wchar* str);

	~WStringImpl();
	void print() const;

	size_t length() const;

	bool isEmpty() const;

	wchar charAt(size_t index) const;

	const wchar* characters() const;

	bool startsWith(const WStringImpl& str, size_t start = 0) const;

	bool endsWith(const WStringImpl& str) const;

	bool contains(const WStringImpl& str) const;

	/**
	 * operator compares.
	 */
	bool operator==(const WStringImpl& s) const;
	bool operator!=(const WStringImpl& s) const;
	bool operator>(const WStringImpl& s) const;
	bool operator>=(const WStringImpl& s) const;
	bool operator<(const WStringImpl& s) const;
	bool operator<=(const WStringImpl& s) const;

	hash_t hash() const;

private:
	int32_t compare(const WStringImpl& s) const;
	void checkIndex(size_t index) const {
		if (index >= length()) {
			throwIndexOutOfBounds(index, length());
		}
	}
	void throwIndexOutOfBounds(int index, int len) const {
		printf("IndexOutOfBounds index=%d, length=%d!\n", index, len);
		throw "IndexOutOfBounds";
	}

	const wchar* m_data;
	size_t m_length;

	mutable hash_t m_hash;
};

} /* namespace utils */
} /* namespace pola */

#endif /* POLA_WSTRINGIMPL_H_ */
