/*
 * RefBase.h
 *
 *  Created on: 2015年12月1日
 *      Author: lijing
 */

#ifndef POLA_REFBASE_H_
#define POLA_REFBASE_H_

#include "pola/log/Log.h"
#include <atomic>

#include "pola/utils/StrongPtr.h"
#include "pola/utils/WeakPtr.h"

using namespace std;

//#define DEBUG_RP 1

namespace pola {
namespace utils {

template<typename T> class RefBase;
template<typename T> class weakref_impl;

template<typename T> class RefBase {

public:

	virtual ~RefBase() {
		m_weakref->m_ref = nullptr;
	}

	inline void ref() {
		++ m_weakref->m_strongrefCount;
		m_weakref->ref_weak();
#ifdef DEBUG_RP
		int count = m_weakref->m_strongrefCount;
		LOGI("this=%p, ref refCount=%d\n", this, count);
#endif
	}
	inline void deref() {
#ifdef DEBUG_RP
		int count = m_weakref->m_strongrefCount - 1;
		LOGI("this=%p, deref refCount=%d\n", this, count);
#endif
		int32_t c = -- m_weakref->m_strongrefCount;
		if (c <= 0) {
			m_weakref->m_ref = NULL;
		}
		m_weakref->deref_weak();
		if (c <= 0) {
			delete static_cast<T*>(this);
		}
	}

	inline int32_t getStrongCount() const {
		return m_weakref->m_strongrefCount;
	}

	inline weakref_impl<T>* get_weak_impl() {
		return m_weakref;
	}

protected:
	RefBase() : m_weakref(new weakref_impl<T>(this)) {};

private:

	template<typename Y> friend class weakref_impl;

	weakref_impl<T>* m_weakref;
};

template<typename T> class weakref_impl {
public:
	weakref_impl(RefBase<T>* ref) : m_strongrefCount(0), m_weakrefCount(0), m_ref(ref) {
	}

	virtual ~weakref_impl() {
	}

	inline T* get() {
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
		LOGI("this=%p, ref_weak refCount=%d\n", this, count);
#endif
		return this;
	}

	inline void deref_weak() {
#ifdef DEBUG_RP
		int count = m_weakrefCount - 1;
		LOGI("this=%p, deref_weak refCount=%d\n", this, count);
#endif
		if ((-- m_weakrefCount) <= 0) {
			delete this;
		}
	}

	inline bool attempt_refStrong() {
		ref_weak();
		bool r = (++ m_strongrefCount) > 1;
		if (!r) {
			deref_weak();
		}
		return r;
	}

private:
	template<typename Y> friend class RefBase;

	atomic_int m_strongrefCount;
	atomic_int m_weakrefCount;
	RefBase<T>* m_ref;
};
}
}

#endif /* POLA_REFBASE_H_ */
