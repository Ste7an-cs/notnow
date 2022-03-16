//
// Created by ste7an on 2022/3/16.
//该头文件 包含一个模版类 allocator 用于内存的分配、释放，对象的构造、析构

#ifndef TINYSTL_ALLOCATOR_H
#define TINYSTL_ALLOCATOR_H
namespace TINYSTL
{
template <class T>
class Allocator
{
public:
    typedef T               value_type;
    typedef T*              pointer;
    typedef const T*        const_pointer;
    typedef T&              reference;
    typedef const T&        const_reference;
    typedef size_t          size_type;
    typedef ptrdiff_t       difference_type;

public:
    static T* allocate();
    static T* allocate(size_t size);

    static void deallocate(T* ptr);
    static void deallocate(T* ptr, size_t size);

    static void construct(T* ptr);
    
};




}
#endif //TINYSTL_ALLOCATOR_H
