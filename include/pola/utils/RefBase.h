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
//#include "pola/utils/WeakPtr.h"

using namespace std;

//#define DEBUG_RP 1

namespace pola {
namespace utils {

class RefBase;
class weakref_impl;

class weakref_impl {
public:
	inline weakref_impl(RefBase* ref) : m_strongrefCount(0), m_weakrefCount(0), m_ref(ref) {
	}

	inline virtual ~weakref_impl() {
	}

	inline RefBase* get() {
		if (m_ref) {
			return m_ref;
		} else {
			return NULL;
		}
	}

	inline weakref_impl* ref_weak() {
		m_weakrefCount ++;
#ifdef DEBUG_RP
		int count = m_weakrefCount;
		LOGI("ref_weak refCount=%d", count);
#endif
		return this;
	}

	inline void deref_weak() {
#ifdef DEBUG_RP
		int count = m_weakrefCount - 1;
		LOGI("deref_weak refCount=%d", count);
#endif
		const int32_t c = m_weakrefCount --;
		if (c <= 1) {
			delete this;
		}
	}

	inline bool attempt_refStrong() {
		ref_weak();
		const int32_t c = m_strongrefCount ++;
		bool r = c >= 1;
		if (!r) {
			deref_weak();
			m_strongrefCount --;
		}
		return r;
	}

private:
	friend class RefBase;
	volatile int32_t m_strongrefCount;
	atomic_int m_weakrefCount;
	RefBase* m_ref;
};

class RefBase {

public:

	virtual ~RefBase() {
		m_weakref->m_ref = NULL;
	}

	inline void ref() {
		m_weakref->m_strongrefCount ++;
		m_weakref->ref_weak();
#ifdef DEBUG_RP
		int count = getStrongCount();
		LOGI("ref refCount=%d", count);
#endif
	}
	inline void deref() {
#ifdef DEBUG_RP
		int count = getStrongCount() - 1;
		LOGI("deref refCount=%d", count);
#endif
		const int32_t c = m_weakref->m_strongrefCount --;
		if (c <= 1) {
			m_weakref->m_ref = NULL;
		}
		m_weakref->deref_weak();
		if (c <= 1) {
			delete this;
		}
	}

	inline int32_t getStrongCount() const {
		return m_weakref->m_strongrefCount;
	}

	inline weakref_impl* get_weak_impl() {
		return m_weakref;
	}

protected:
	RefBase() : m_weakref(new weakref_impl(this)) {};

private:

	friend class weakref_impl;

	weakref_impl* m_weakref;
};

template<typename T> class sp;

#define COMPARE(_op_)                                           \
inline bool operator _op_ (const wp<T>& o) const {              \
    return m_ptr _op_ o.m_ptr;                                  \
}                                                               \
inline bool operator _op_ (const T* o) const {                  \
    return get() _op_ o;                                        \
}                                                               \
template<typename U>                                            \
inline bool operator _op_ (const wp<U>& o) const {              \
    return m_ptr _op_ o.m_ptr;                                  \
}                                                               \
template<typename U>                                            \
inline bool operator _op_ (const U* o) const {                  \
    return get() _op_ o;                                        \
}                                                               \
inline bool operator _op_ (const sp<T>& o) const {              \
    return get() _op_ o.m_ptr;                                  \
}                                                               \
template<typename U>                                            \
inline bool operator _op_ (const sp<U>& o) const {              \
    return get() _op_ o.m_ptr;                                  \
}                                                               \

// ---------------------------------------------------------------------------

template<typename T>
class wp {
public:
    inline wp() : m_ptr(NULL) { }

    wp(T* other);
    wp(const wp<T>& other);
    wp(const sp<T>& other);
    template<typename U> wp(U* other);
    template<typename U> wp(const wp<U>& other);
    template<typename U> wp(const sp<U>& other);

    ~wp();

    // Assignment

    wp& operator = (T* other);
    wp& operator = (const wp<T>& other);
    wp& operator = (const sp<T>& other);

    template<typename U> wp& operator = (const wp<U>& other);
    template<typename U> wp& operator = (U* other);

    template<typename U> wp& operator = (const sp<U>& other);

    // Reset

    void clear();

    // Accessors

    inline  T&      operator* () const  { return *get(); }
    inline  T*      operator-> () const { return get();  }
    inline  T*      get() const         { return m_ptr ? (T*) m_ptr->get() : NULL; }
    inline sp<T> promote() const {
		if (m_ptr && m_ptr->attempt_refStrong()) {
			sp<T> result;
			result.set_pointer((T*) m_ptr->get());
			return result;
		}
		return NULL;
	}

    // Operators

    COMPARE(==)
    COMPARE(!=)
    COMPARE(>)
    COMPARE(<)
    COMPARE(<=)
    COMPARE(>=)

private:
    template<typename Y> friend class sp;
    template<typename Y> friend class wp;
    weakref_impl* m_ptr;
};

#undef COMPARE

// ---------------------------------------------------------------------------
// No user serviceable parts below here.

template<typename T>
wp<T>::wp(T* other) {
    if (other) {
        m_ptr = other->get_weak_impl();
		m_ptr->ref_weak();
    } else {
    	m_ptr = NULL;
    }
}

template<typename T>
wp<T>::wp(const wp<T>& other)
        : m_ptr(other.m_ptr) {
	if (m_ptr) {
		m_ptr->ref_weak();
	}
}

template<typename T>
wp<T>::wp(const sp<T>& other) {
	T* otherPtr(other.get());
	m_ptr = otherPtr ? otherPtr->get_weak_impl() : NULL;
	if (m_ptr) {
		m_ptr->ref_weak();
	}

}

template<typename T> template<typename U>
wp<T>::wp(U* other) {
    if (other) {
		m_ptr = ((T*) other)->get_weak_impl();
		m_ptr->ref_weak();
	} else {
		m_ptr = NULL;
	}
}

template<typename T> template<typename U>
wp<T>::wp(const wp<U>& other)
        : m_ptr(other.m_ptr) {
	if (m_ptr) {
		m_ptr->ref_weak();
	}
}

template<typename T> template<typename U>
wp<T>::wp(const sp<U>& other) {
	T* otherPtr(other.get());
	m_ptr = otherPtr ? otherPtr->get_weak_impl() : NULL;
	if (m_ptr) {
		m_ptr->ref_weak();
	}
}

template<typename T>
wp<T>::~wp() {
	if (m_ptr) {
		m_ptr->deref_weak();
	}
}

template<typename T>
wp<T>& wp<T>::operator =(const wp<T>& other) {
	T* otherPtr(other.get());
	weakref_impl* old = m_ptr;
	m_ptr = otherPtr ? otherPtr->get_weak_impl() : NULL;
	if (m_ptr) {
		m_ptr->ref_weak();
	}
	if (old) {
		old->deref_weak();
	}
    return *this;
}

template<typename T>
wp<T>& wp<T>::operator =(T* other) {
	weakref_impl* old = m_ptr;
    m_ptr = other ? other->get_weak_impl() : NULL;
    if (m_ptr) {
		m_ptr->ref_weak();
	}
    if (old) {
		old->deref_weak();
	}
    return *this;
}

template<typename T> template<typename U>
wp<T>& wp<T>::operator =(const wp<U>& other) {
    T* otherPtr(other.get());
	weakref_impl* old = m_ptr;
	m_ptr = otherPtr ? otherPtr->get_weak_impl() : NULL;
	if (m_ptr) {
		m_ptr->ref_weak();
	}
	if (old) {
		old->deref_weak();
	}
    return *this;
}

template<typename T> template<typename U>
wp<T>& wp<T>::operator =(U* other) {
	weakref_impl* old = m_ptr;
	m_ptr = other ? other->get_weak_impl() : NULL;
	if (m_ptr) {
		m_ptr->ref_weak();
	}
	if (old) {
		old->deref_weak();
	}
    return *this;
}

template<typename T>
wp<T>& wp<T>::operator =(const sp<T>& other) {
	T* otherPtr(other.get());
	weakref_impl* old = m_ptr;
	m_ptr = otherPtr ? otherPtr->get_weak_impl() : NULL;
	if (m_ptr) {
		m_ptr->ref_weak();
	}
	if (old) {
		old->deref_weak();
	}
    return *this;
}
template<typename T> template<typename U>
wp<T>& wp<T>::operator =(const sp<U>& other) {
    T* otherPtr(other.get());
	weakref_impl* old = m_ptr;
	m_ptr = otherPtr ? otherPtr->get_weak_impl() : NULL;
	if (m_ptr) {
		m_ptr->ref_weak();
	}
	if (old) {
		old->deref_weak();
	}
    return *this;
}

template<typename T>
void wp<T>::clear() {
	T* ptr = get();
    if (ptr) {
		ptr->deref_weak();
    }
}
}
}

#endif /* POLA_REFBASE_H_ */
