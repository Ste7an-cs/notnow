//
// Created by ste7an on 2022/3/16.
//
/*
 *  该头文件包含两个函数：construct、destroy
 *  construct：负责构造对象
 *  destroy：负责析构对象
 *
 */
#ifndef TINYSTL_CONSTRUCT_H
#define TINYSTL_CONSTRUCT_H

#include "iterator.h"

namespace tinystl
{
    //construct

template<class T>
void construct(T* ptr)
{
    ::new((void*)ptr) T();
}

template<class T, class U>
void construct(T* ptr, U& val)
{
    ::new((void*)ptr) U(val);
}

template<class T, class ...Args>
void construct(T* ptr, Args&&... args)
{
    ::new((void*)ptr) T(std::forward<Args>(args)... );
}


//destroy


template<class T>
void _destroy_Ptr(T* , std::true_type){}

template<class T>
void _destroy_Ptr(T* ptr, std::false_type)
{
    if (ptr!=nullptr)
    {
        ptr->~T();
    }
}

template<class T>
void destroy(T* ptr)
{
    _destroy_Ptr(ptr, std::is_trivially_destructible<T>{});
}


template<class ForwardIter>
void _destroy_Iter(ForwardIter , ForwardIter , std::true_type){}

template<class ForwardIter>
void _destroy_Iter(ForwardIter first, ForwardIter last, std::false_type)
{
    for(; first!=last; ++first)
    {
        destroy(&*first);
    }
}

template<class ForwardIter>
void destroy(ForwardIter first, ForwardIter last)
{
    _destory_Iter(first, last, std::is_trivially_destructible<
            typename iterator_traits<ForwardIter>::value_type>{});
}




}//namespace tinystl
#endif //TINYSTL_CONSTRUCT_H
