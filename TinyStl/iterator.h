//
// Created by ste7an on 2022/3/16.
//

#ifndef TINYSTL_ITERATOR_H
#define TINYSTL_ITERATOR_H

#include<cstddef>



struct input_iterator_tag{};
struct output_iterator_tag{};
struct forward_iterator_tag : public  input_iterator_tag{};
struct bidirectional_iterator_tag : public forward_iterator_tag{};
struct random_access_iterator_tag : public bidirectional_iterator_tag{};


template<class Category, class T, class Distance = ptrdiff_t,
        class Pointer = T*, class Reference = T&>
struct iterator
{
    typedef Category        iterator_category ;
    typedef Pointer         pointer;
    typedef T               value_type;
    typedef Reference       reference;
    typedef Distance        difference_type;
};






#endif //TINYSTL_ITERATOR_H
