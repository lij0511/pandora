/*
 * RefBase.h
 *
 *  Created on: 2015年12月1日
 *      Author: lijing
 */

#ifndef POLA_REFBASE_H_
#define POLA_REFBASE_H_

#include "log/Log.h"
#include <atomic>

#include "utils/StrongPtr.h"

using namespace std;

//#define DEBUG_RP 1

namespace pola {
namespace utils {

template<typename T> class RefBase;
template<typename T> class weakref_impl;

template<typename T> class RefBase {

public:

	~RefBase() {
		if (m_weakref) {
			m_weakref->clear();
			m_weakref = nullptr;
		}
	}

	inline void ref() {
		++ m_refCount;
#ifdef DEBUG_RP
		int count = m_refCount;
		LOGI("ref refCount=%d\n", count);
#endif
	}
	inline void deref() {
#ifdef DEBUG_RP
		int count = m_refCount - 1;
		LOGI("deref refCount=%d\n", count);
#endif
		if ((-- m_refCount) <= 0) {
			delete static_cast<T*>(this);
		}
	}

	inline weakref_impl<T>* get_weak_impl() {
		if (!m_weakref) {
			m_weakref = new weakref_impl<T>(this);
		}
		return m_weakref;
	}

protected:
	RefBase() : m_refCount(0), m_weakref(nullptr) {};

private:

	template<typename Y> friend class weakref_impl;

	atomic_int m_refCount;
	weakref_impl<T>* m_weakref;
};

template<typename T> class weakref_impl {
public:
	weakref_impl(RefBase<T>* ref) : m_weakrefCount(0), m_ref(ref) {
	}

	virtual ~weakref_impl() {
	}

	void clear() {
		m_ref = nullptr;
		if (m_weakrefCount <= 0) {
			delete this;
		}
	}

	T* get() {
		if (m_ref) {
			return static_cast<T*>(m_ref);
		} else {
			return nullptr;
		}
	}

	inline weakref_impl<T>* ref_weak() {
		++ m_weakrefCount;
#ifdef DEBUG_RP
		int count = m_weakrefCount;
		LOGI("ref_weak refCount=%d\n", count);
#endif
		return this;
	}

	inline void deref_weak() {
#ifdef DEBUG_RP
		int count = m_weakrefCount - 1;
		LOGI("deref_weak refCount=%d\n", count);
#endif
		if ((-- m_weakrefCount) <= 0) {
			delete this;
		}
	}

private:
	atomic_int m_weakrefCount;
	RefBase<T>* m_ref;
};
}
}

#endif /* POLA_REFBASE_H_ */
