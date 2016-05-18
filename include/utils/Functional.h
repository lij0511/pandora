/*
 * Functional.h
 *
 *  Created on: 2015年12月23日
 *      Author: lijing
 */

#ifndef FUNCTIONAL_H_
#define FUNCTIONAL_H_

#include "utils/RefBase.h"
#include "utils/WeakPtr.h"

namespace pola {
namespace utils {

// Functional.h provides a very simple way to bind a function pointer and arguments together into a function object
// that can be stored, copied and invoked, similar to how boost::bind and std::bind in C++11.

// A FunctionWrapper is a class template that can wrap a function pointer or a member function pointer and
// provide a unified interface for calling that function.
template<typename>
class FunctionWrapper;

// Bound static functions:

template<typename R>
class FunctionWrapper<R(*)()> {
public:
    typedef R ResultType;

    explicit FunctionWrapper(R(*function)())
        : m_function(function)
    {
    }

    R operator()()
    {
        return m_function();
    }

private:
    R(*m_function)();
};

template<typename R, typename P1>
class FunctionWrapper<R(*)(P1)> {
public:
    typedef R ResultType;

    explicit FunctionWrapper(R(*function)(P1))
        : m_function(function)
    {
    }

    R operator()(P1 p1)
    {
        return m_function(p1);
    }

private:
    R(*m_function)(P1);
};

template<typename R, typename P1, typename P2>
class FunctionWrapper<R(*)(P1, P2)> {
public:
    typedef R ResultType;

    explicit FunctionWrapper(R(*function)(P1, P2))
        : m_function(function)
    {
    }

    R operator()(P1 p1, P2 p2)
    {
        return m_function(p1, p2);
    }

private:
    R(*m_function)(P1, P2);
};

template<typename R, typename P1, typename P2, typename P3>
class FunctionWrapper<R(*)(P1, P2, P3)> {
public:
    typedef R ResultType;

    explicit FunctionWrapper(R(*function)(P1, P2, P3))
        : m_function(function)
    {
    }

    R operator()(P1 p1, P2 p2, P3 p3)
    {
        return m_function(p1, p2, p3);
    }

private:
    R(*m_function)(P1, P2, P3);
};

template<typename R, typename P1, typename P2, typename P3, typename P4>
class FunctionWrapper<R(*)(P1, P2, P3, P4)> {
public:
    typedef R ResultType;

    explicit FunctionWrapper(R(*function)(P1, P2, P3, P4))
        : m_function(function)
    {
    }

    R operator()(P1 p1, P2 p2, P3 p3, P4 p4)
    {
        return m_function(p1, p2, p3, p4);
    }

private:
    R(*m_function)(P1, P2, P3, P4);
};

template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
class FunctionWrapper<R(*)(P1, P2, P3, P4, P5)> {
public:
    typedef R ResultType;

    explicit FunctionWrapper(R(*function)(P1, P2, P3, P4, P5))
        : m_function(function)
    {
    }

    R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
    {
        return m_function(p1, p2, p3, p4, p5);
    }

private:
    R(*m_function)(P1, P2, P3, P4, P5);
};

// Bound member functions:

template<typename R, typename C>
class FunctionWrapper<R(C::*)()> {
public:
    typedef R ResultType;

    explicit FunctionWrapper(R(C::*function)())
        : m_function(function)
    {
    }

    R operator()(C* c)
    {
        return (c->*m_function)();
    }

    R operator()(const wp<C>& c)
    {
        C* obj = c.get();
        if (!obj)
            return R();
        return (obj->*m_function)();
    }

private:
    R(C::*m_function)();
};

template<typename R, typename C, typename P1>
class FunctionWrapper<R(C::*)(P1)> {
public:
    typedef R ResultType;

    explicit FunctionWrapper(R(C::*function)(P1))
        : m_function(function)
    {
    }

    R operator()(C* c, P1 p1)
    {
        return (c->*m_function)(p1);
    }

    R operator()(const wp<C>& c, P1 p1)
    {
        C* obj = c.get();
        if (!obj)
            return R();
        return (obj->*m_function)(p1);
    }

private:
    R(C::*m_function)(P1);
};

template<typename R, typename C, typename P1, typename P2>
class FunctionWrapper<R(C::*)(P1, P2)> {
public:
    typedef R ResultType;

    explicit FunctionWrapper(R(C::*function)(P1, P2))
        : m_function(function)
    {
    }

    R operator()(C* c, P1 p1, P2 p2)
    {
        return (c->*m_function)(p1, p2);
    }

    R operator()(const wp<C>& c, P1 p1, P2 p2)
    {
        C* obj = c.get();
        if (!obj)
            return R();
        return (obj->*m_function)(p1, p2);
    }

private:
    R(C::*m_function)(P1, P2);
};

template<typename R, typename C, typename P1, typename P2, typename P3>
class FunctionWrapper<R(C::*)(P1, P2, P3)> {
public:
    typedef R ResultType;

    explicit FunctionWrapper(R(C::*function)(P1, P2, P3))
        : m_function(function)
    {
    }

    R operator()(C* c, P1 p1, P2 p2, P3 p3)
    {
        return (c->*m_function)(p1, p2, p3);
    }

    R operator()(const wp<C>& c, P1 p1, P2 p2, P3 p3)
    {
        C* obj = c.get();
        if (!obj)
            return R();
        return (obj->*m_function)(p1, p2, p3);
    }

private:
    R(C::*m_function)(P1, P2, P3);
};

template<typename R, typename C, typename P1, typename P2, typename P3, typename P4>
class FunctionWrapper<R(C::*)(P1, P2, P3, P4)> {
public:
    typedef R ResultType;

    explicit FunctionWrapper(R(C::*function)(P1, P2, P3, P4))
        : m_function(function)
    {
    }

    R operator()(C* c, P1 p1, P2 p2, P3 p3, P4 p4)
    {
        return (c->*m_function)(p1, p2, p3, p4);
    }

    R operator()(const wp<C>& c, P1 p1, P2 p2, P3 p3, P4 p4)
    {
        C* obj = c.get();
        if (!obj)
            return R();
        return (obj->*m_function)(p1, p2, p3, p4);
    }

private:
    R(C::*m_function)(P1, P2, P3, P4);
};

template<typename R, typename C, typename P1, typename P2, typename P3, typename P4, typename P5>
class FunctionWrapper<R(C::*)(P1, P2, P3, P4, P5)> {
public:
    typedef R ResultType;

    explicit FunctionWrapper(R(C::*function)(P1, P2, P3, P4, P5))
        : m_function(function)
    {
    }

    R operator()(C* c, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
    {
        return (c->*m_function)(p1, p2, p3, p4, p5);
    }

    R operator()(const wp<C>& c, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
    {
        C* obj = c.get();
        if (!obj)
            return R();
        return (obj->*m_function)(p1, p2, p3, p4, p5);
    }

private:
    R(C::*m_function)(P1, P2, P3, P4, P5);
};

template<typename T> struct ParamStorageTraits {
    typedef T StorageType;

    static StorageType wrap(const T& value) { return value; }
    static const T& unwrap(const StorageType& value) { return value; }
};

template<typename T> struct ParamStorageTraits<sp<T> > {
    typedef sp<T> StorageType;

    static StorageType wrap(sp<T> value) { return value; }
    static T* unwrap(const StorageType& value) { return value.get(); }
};

class FunctionImplBase : public RefBase<FunctionImplBase> {
public:
    virtual ~FunctionImplBase() { }
};

template<typename>
class FunctionImpl;

template<typename R>
class FunctionImpl<R()> : public FunctionImplBase {
public:
    virtual R operator()() = 0;
};

template<typename FunctionWrapper, typename FunctionType>
class BoundFunctionImpl;

template<typename FunctionWrapper, typename R>
class BoundFunctionImpl<FunctionWrapper, R()> final : public FunctionImpl<typename FunctionWrapper::ResultType()> {
public:
    explicit BoundFunctionImpl(FunctionWrapper functionWrapper)
        : m_functionWrapper(functionWrapper)
    {
    }

    virtual ~BoundFunctionImpl() {}

    virtual typename FunctionWrapper::ResultType operator()() override
    {
        return m_functionWrapper();
    }

private:
    FunctionWrapper m_functionWrapper;
};

template<typename FunctionWrapper, typename R, typename P1>
class BoundFunctionImpl<FunctionWrapper, R(P1)> final : public FunctionImpl<typename FunctionWrapper::ResultType()> {
public:
    BoundFunctionImpl(FunctionWrapper functionWrapper, const P1& p1)
        : m_functionWrapper(functionWrapper)
        , m_p1(ParamStorageTraits<P1>::wrap(p1))
    {
    }

    virtual ~BoundFunctionImpl() {}

    virtual typename FunctionWrapper::ResultType operator()() override
    {
        return m_functionWrapper(ParamStorageTraits<P1>::unwrap(m_p1));
    }

private:
    FunctionWrapper m_functionWrapper;
    typename ParamStorageTraits<P1>::StorageType m_p1;
};

template<typename FunctionWrapper, typename R, typename P1, typename P2>
class BoundFunctionImpl<FunctionWrapper, R(P1, P2)> final : public FunctionImpl<typename FunctionWrapper::ResultType()> {
public:
    BoundFunctionImpl(FunctionWrapper functionWrapper, const P1& p1, const P2& p2)
        : m_functionWrapper(functionWrapper)
        , m_p1(ParamStorageTraits<P1>::wrap(p1))
        , m_p2(ParamStorageTraits<P2>::wrap(p2))
    {
    }

    virtual ~BoundFunctionImpl() {}

    virtual typename FunctionWrapper::ResultType operator()() override
    {
        return m_functionWrapper(ParamStorageTraits<P1>::unwrap(m_p1), ParamStorageTraits<P2>::unwrap(m_p2));
    }

private:
    FunctionWrapper m_functionWrapper;
    typename ParamStorageTraits<P1>::StorageType m_p1;
    typename ParamStorageTraits<P2>::StorageType m_p2;
};

template<typename FunctionWrapper, typename R, typename P1, typename P2, typename P3>
class BoundFunctionImpl<FunctionWrapper, R(P1, P2, P3)> final : public FunctionImpl<typename FunctionWrapper::ResultType()> {
public:
    BoundFunctionImpl(FunctionWrapper functionWrapper, const P1& p1, const P2& p2, const P3& p3)
        : m_functionWrapper(functionWrapper)
        , m_p1(ParamStorageTraits<P1>::wrap(p1))
        , m_p2(ParamStorageTraits<P2>::wrap(p2))
        , m_p3(ParamStorageTraits<P3>::wrap(p3))
    {
    }

    virtual ~BoundFunctionImpl() {}

    virtual typename FunctionWrapper::ResultType operator()() override
    {
        return m_functionWrapper(ParamStorageTraits<P1>::unwrap(m_p1), ParamStorageTraits<P2>::unwrap(m_p2), ParamStorageTraits<P3>::unwrap(m_p3));
    }

private:
    FunctionWrapper m_functionWrapper;
    typename ParamStorageTraits<P1>::StorageType m_p1;
    typename ParamStorageTraits<P2>::StorageType m_p2;
    typename ParamStorageTraits<P3>::StorageType m_p3;
};

template<typename FunctionWrapper, typename R, typename P1, typename P2, typename P3, typename P4>
class BoundFunctionImpl<FunctionWrapper, R(P1, P2, P3, P4)> final : public FunctionImpl<typename FunctionWrapper::ResultType()> {
public:
    BoundFunctionImpl(FunctionWrapper functionWrapper, const P1& p1, const P2& p2, const P3& p3, const P4& p4)
        : m_functionWrapper(functionWrapper)
        , m_p1(ParamStorageTraits<P1>::wrap(p1))
        , m_p2(ParamStorageTraits<P2>::wrap(p2))
        , m_p3(ParamStorageTraits<P3>::wrap(p3))
        , m_p4(ParamStorageTraits<P4>::wrap(p4))
    {
    }

    virtual ~BoundFunctionImpl() {}

    virtual typename FunctionWrapper::ResultType operator()() override
    {
        return m_functionWrapper(ParamStorageTraits<P1>::unwrap(m_p1), ParamStorageTraits<P2>::unwrap(m_p2), ParamStorageTraits<P3>::unwrap(m_p3), ParamStorageTraits<P4>::unwrap(m_p4));
    }

private:
    FunctionWrapper m_functionWrapper;
    typename ParamStorageTraits<P1>::StorageType m_p1;
    typename ParamStorageTraits<P2>::StorageType m_p2;
    typename ParamStorageTraits<P3>::StorageType m_p3;
    typename ParamStorageTraits<P4>::StorageType m_p4;
};

template<typename FunctionWrapper, typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
class BoundFunctionImpl<FunctionWrapper, R(P1, P2, P3, P4, P5)> final : public FunctionImpl<typename FunctionWrapper::ResultType()> {
public:
    BoundFunctionImpl(FunctionWrapper functionWrapper, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5)
        : m_functionWrapper(functionWrapper)
        , m_p1(ParamStorageTraits<P1>::wrap(p1))
        , m_p2(ParamStorageTraits<P2>::wrap(p2))
        , m_p3(ParamStorageTraits<P3>::wrap(p3))
        , m_p4(ParamStorageTraits<P4>::wrap(p4))
        , m_p5(ParamStorageTraits<P5>::wrap(p5))
    {
    }

    virtual ~BoundFunctionImpl() {}

    virtual typename FunctionWrapper::ResultType operator()() override
    {
        return m_functionWrapper(ParamStorageTraits<P1>::unwrap(m_p1), ParamStorageTraits<P2>::unwrap(m_p2), ParamStorageTraits<P3>::unwrap(m_p3), ParamStorageTraits<P4>::unwrap(m_p4), ParamStorageTraits<P5>::unwrap(m_p5));
    }

private:
    FunctionWrapper m_functionWrapper;
    typename ParamStorageTraits<P1>::StorageType m_p1;
    typename ParamStorageTraits<P2>::StorageType m_p2;
    typename ParamStorageTraits<P3>::StorageType m_p3;
    typename ParamStorageTraits<P4>::StorageType m_p4;
    typename ParamStorageTraits<P5>::StorageType m_p5;
};

template<typename FunctionWrapper, typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
class BoundFunctionImpl<FunctionWrapper, R(P1, P2, P3, P4, P5, P6)> final : public FunctionImpl<typename FunctionWrapper::ResultType()> {
public:
    BoundFunctionImpl(FunctionWrapper functionWrapper, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5, const P6& p6)
        : m_functionWrapper(functionWrapper)
        , m_p1(ParamStorageTraits<P1>::wrap(p1))
        , m_p2(ParamStorageTraits<P2>::wrap(p2))
        , m_p3(ParamStorageTraits<P3>::wrap(p3))
        , m_p4(ParamStorageTraits<P4>::wrap(p4))
        , m_p5(ParamStorageTraits<P5>::wrap(p5))
        , m_p6(ParamStorageTraits<P6>::wrap(p6))
    {
    }

    virtual ~BoundFunctionImpl() {}

    virtual typename FunctionWrapper::ResultType operator()() override
    {
        return m_functionWrapper(ParamStorageTraits<P1>::unwrap(m_p1), ParamStorageTraits<P2>::unwrap(m_p2), ParamStorageTraits<P3>::unwrap(m_p3), ParamStorageTraits<P4>::unwrap(m_p4), ParamStorageTraits<P5>::unwrap(m_p5), ParamStorageTraits<P6>::unwrap(m_p6));
    }

private:
    FunctionWrapper m_functionWrapper;
    typename ParamStorageTraits<P1>::StorageType m_p1;
    typename ParamStorageTraits<P2>::StorageType m_p2;
    typename ParamStorageTraits<P3>::StorageType m_p3;
    typename ParamStorageTraits<P4>::StorageType m_p4;
    typename ParamStorageTraits<P5>::StorageType m_p5;
    typename ParamStorageTraits<P6>::StorageType m_p6;
};

class FunctionBase {
public:
    bool isNull() const
    {
        return !m_impl;
    }

protected:
    FunctionBase()
    {
    }

    explicit FunctionBase(sp<FunctionImplBase> impl)
        : m_impl(impl)
    {
    }

    template<typename FunctionType> FunctionImpl<FunctionType>* impl() const
    {
        return static_cast<FunctionImpl<FunctionType>*>(m_impl.get());
    }

private:
    sp<FunctionImplBase> m_impl;
};

template<typename>
class Function;

template<typename R>
class Function<R()> : public FunctionBase {
public:
    Function()
    {
    }

    Function(sp<FunctionImpl<R()> > impl)
        : FunctionBase(impl)
    {
    }

    R operator()() const
    {
        return impl<R()>()->operator()();
    }
};

template<typename FunctionType>
Function<typename FunctionWrapper<FunctionType>::ResultType()> bind(FunctionType function)
{
    return Function<typename FunctionWrapper<FunctionType>::ResultType()>(new BoundFunctionImpl<FunctionWrapper<FunctionType>, typename FunctionWrapper<FunctionType>::ResultType()>(FunctionWrapper<FunctionType>(function)));
}

template<typename FunctionType, typename A1>
Function<typename FunctionWrapper<FunctionType>::ResultType()> bind(FunctionType function, const A1& a1)
{
    return Function<typename FunctionWrapper<FunctionType>::ResultType()>(new BoundFunctionImpl<FunctionWrapper<FunctionType>, typename FunctionWrapper<FunctionType>::ResultType (A1)>(FunctionWrapper<FunctionType>(function), a1));
}

template<typename FunctionType, typename A1, typename A2>
Function<typename FunctionWrapper<FunctionType>::ResultType()> bind(FunctionType function, const A1& a1, const A2& a2)
{
    return Function<typename FunctionWrapper<FunctionType>::ResultType()>(new BoundFunctionImpl<FunctionWrapper<FunctionType>, typename FunctionWrapper<FunctionType>::ResultType (A1, A2)>(FunctionWrapper<FunctionType>(function), a1, a2));
}

template<typename FunctionType, typename A1, typename A2, typename A3>
Function<typename FunctionWrapper<FunctionType>::ResultType()> bind(FunctionType function, const A1& a1, const A2& a2, const A3& a3)
{
    return Function<typename FunctionWrapper<FunctionType>::ResultType()>(new BoundFunctionImpl<FunctionWrapper<FunctionType>, typename FunctionWrapper<FunctionType>::ResultType (A1, A2, A3)>(FunctionWrapper<FunctionType>(function), a1, a2, a3));
}

template<typename FunctionType, typename A1, typename A2, typename A3, typename A4>
Function<typename FunctionWrapper<FunctionType>::ResultType()> bind(FunctionType function, const A1& a1, const A2& a2, const A3& a3, const A4& a4)
{
    return Function<typename FunctionWrapper<FunctionType>::ResultType()>(new BoundFunctionImpl<FunctionWrapper<FunctionType>, typename FunctionWrapper<FunctionType>::ResultType (A1, A2, A3, A4)>(FunctionWrapper<FunctionType>(function), a1, a2, a3, a4));
}

template<typename FunctionType, typename A1, typename A2, typename A3, typename A4, typename A5>
Function<typename FunctionWrapper<FunctionType>::ResultType()> bind(FunctionType function, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5)
{
    return Function<typename FunctionWrapper<FunctionType>::ResultType()>(new BoundFunctionImpl<FunctionWrapper<FunctionType>, typename FunctionWrapper<FunctionType>::ResultType (A1, A2, A3, A4, A5)>(FunctionWrapper<FunctionType>(function), a1, a2, a3, a4, a5));
}

template<typename FunctionType, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
Function<typename FunctionWrapper<FunctionType>::ResultType()> bind(FunctionType function, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6)
{
    return Function<typename FunctionWrapper<FunctionType>::ResultType()>(new BoundFunctionImpl<FunctionWrapper<FunctionType>, typename FunctionWrapper<FunctionType>::ResultType (A1, A2, A3, A4, A5, A6)>(FunctionWrapper<FunctionType>(function), a1, a2, a3, a4, a5, a6));
}

typedef Function<void()> Closure;

}
}

#endif /* FUNCTIONAL_H_ */
