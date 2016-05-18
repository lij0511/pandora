/*
 * WeakPtr.h
 *
 *  Created on: 2015年12月23日
 *      Author: lijing
 */

#ifndef WEAKPTR_H_
#define WEAKPTR_H_

namespace pola {
namespace utils {
// ---------------------------------------------------------------------------

template<typename T> class sp;
template<typename T> class weakref_impl;

#define COMPARE(_op_)                                           \
inline bool operator _op_ (const wp<T>& o) const {              \
    return m_ptr _op_ o.m_ptr;                                  \
}                                                               \
inline bool operator _op_ (const T* o) const {                  \
    return m_ptr _op_ o;                                        \
}                                                               \
template<typename U>                                            \
inline bool operator _op_ (const wp<U>& o) const {              \
    return m_ptr _op_ o.m_ptr;                                  \
}                                                               \
template<typename U>                                            \
inline bool operator _op_ (const U* o) const {                  \
    return m_ptr _op_ o;                                        \
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
    inline wp() : m_ptr(nullptr) { }

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
    inline  T*      get() const         { return m_ptr ? m_ptr->get() : nullptr; }

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
    weakref_impl<T>* m_ptr;
};

#undef COMPARE

// ---------------------------------------------------------------------------
// No user serviceable parts below here.

template<typename T>
wp<T>::wp(T* other)
	: wp() {
    if (other) {
        m_ptr = other->get_weak_impl();
		m_ptr->ref_weak();
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
wp<T>::wp(const sp<T>& other)
        : wp() {
	T* otherPtr(other.get());
	m_ptr = otherPtr ? otherPtr->get_weak_impl() : nullptr;
	if (m_ptr) {
		m_ptr->ref_weak();
	}

}

template<typename T> template<typename U>
wp<T>::wp(U* other)
        : wp() {
    if (other) {
		m_ptr = ((T*) other)->get_weak_impl();
		m_ptr->ref_weak();
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
wp<T>::wp(const sp<U>& other)
        : wp() {
	T* otherPtr(other.get());
	m_ptr = otherPtr ? otherPtr->get_weak_impl() : nullptr;
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
	weakref_impl<T>* old = m_ptr;
	m_ptr = otherPtr ? otherPtr->get_weak_impl() : nullptr;
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
	weakref_impl<T>* old = m_ptr;
    m_ptr = other ? other->get_weak_impl() : nullptr;
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
	weakref_impl<T>* old = m_ptr;
	m_ptr = otherPtr ? otherPtr->get_weak_impl() : nullptr;
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
	weakref_impl<T>* old = m_ptr;
	m_ptr = other ? other->get_weak_impl() : nullptr;
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
	weakref_impl<T>* old = m_ptr;
	m_ptr = otherPtr ? otherPtr->get_weak_impl() : nullptr;
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
	weakref_impl<T>* old = m_ptr;
	m_ptr = otherPtr ? otherPtr->get_weak_impl() : nullptr;
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

#endif /* WEAKPTR_H_ */
