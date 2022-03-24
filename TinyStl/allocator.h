//
// Created by ste7an on 2022/3/16.
//该头文件 包含一个模版类 allocator 用于内存的分配、释放，对象的构造、析构

#ifndef TINYSTL_ALLOCATOR_H
#define TINYSTL_ALLOCATOR_H

#include"construct.h"
#include<cstddef>
namespace tinystl
{
template <class T>
class allocator
{
public:
    typedef T               value_type;
    typedef T*              pointer;
    typedef const T*        const_pointer;
    typedef T&              reference;
    typedef const T&        const_reference;
    typedef size_t             size_type;
    typedef ptrdiff_t       difference_type;

public:
    static T* allocate();
    static T* allocate(size_type n);

    static void deallocate(T* ptr);
    static void deallocate(T* ptr, size_type size);

    static void construct(T* ptr);
    static void construct(T *ptr,const T &value); // placement new 在pty位置call T.copy_ctor构造对像
    static void construct(T *ptr, T &&value); // placement new  call T.move_ctor

    template<class ...Args>
    static void construct(T* ptr, Args&& ...args);       //placement new by parameter pack

    static void destroy(T* ptr);                        // destroy one
    static void destroy(T* first, T* last);             //destroy from to last


};


template<class T>
T* allocator<T>::allocate()
{
    return static_cast<T*>(::operator new(sizeof(T)));
}

template<class T>
T* allocator<T>::allocate(size_type n)
{
    if (n == 0)
        return nullptr;
    return static_cast<T*>(::operator new(n * sizeof(T)));
}

template<class T>
void allocator<T>::deallocate(T* ptr)
{
    if(ptr == nullptr)
        return;
    ::operator delete(ptr);
}

template<class T>
void allocator<T>::deallocate(T* ptr ,size_type size)
{
    if(ptr == nullptr)
        return;
    ::operator delete(ptr);
}


template<class T>
void allocator<T>::construct(T* ptr)
{
    tinystl::construct(ptr);
}

template<class T>
void allocator<T>::construct(T *ptr, T &&value)
{
    tinystl::construct(ptr, std::move(value));
}
template<class T>
template< class... Args>
void allocator<T>::construct(T *ptr, Args &&...args)
{
    tinystl::construct(ptr, std::forward<Args>(args)...);
}

template<class T>
void allocator<T>::construct(T *ptr, const T &value)
{
    tinystl::construct(ptr, value);
}

template<class T>
void allocator<T>::destroy(T* ptr)
{
    tinystl::destroy(ptr);
}

template<class T>
void allocator<T>::destroy(T* first, T* last)
{
    tinystl::destroy(first, last);
}





} //tinystl
#endif //TINYSTL_ALLOCATOR_H
