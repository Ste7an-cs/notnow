//
// Created by ste7an on 2022/3/30.
//

#ifndef TINYSTL_ALGOBASE_H
#define TINYSTL_ALGOBASE_H



#include <type_traits>
#include <cstring>
#include "iterator.h"
namespace tinystl
{



template<typename Tp, typename Size, typename Up>
typename std::enable_if<
    std::is_integral<Tp>::value && sizeof(Tp) == 1 &&
    !std::is_same<Tp, bool>::value &&
    std::is_integral<Up>::value && sizeof(Up) == 1,
    Tp*>::type
_fill_n(Tp* first, Size n, const Up& value)
{
    if(n > 0 )
        std::memset(first, static_cast<unsigned char>(value), size_t(n));

}

template<typename OutputIter, typename Size, typename T>
OutputIter _fill_n(OutputIter first, Size n, const T& value)
{
    for(; n >0; --n, ++first)
        *first = value;
    return first;
}


    template<typename OutputIter, typename Size, typename T>
OutputIter fill_n(OutputIter first, Size n, const T& value)
{
    return _fill_n(first, n, value);
}


template <typename RandomIter, typename T>
void _fill_aux(RandomIter first, RandomIter last, const T& value, tinystl::random_access_iterator_tag)
{
    fill_n(first, last - first, value);
}
template <typename ForwardIter, typename T>
void _fill_aux(ForwardIter first, ForwardIter last, const T& value, tinystl::forward_iterator_tag)
{
    for(; first != last; ++first)
    {
        *first = value;
    }
}

template <typename ForwardIter, typename T>
void fill(ForwardIter first, ForwardIter last, const T& value)
{
    tinystl::_fill_aux(first, last, value, iterator_category(first));
}

// input_iterator_tag 版本
template <class InputIter, class OutputIter>
OutputIter
_copy_aux(InputIter first, InputIter last, OutputIter result,
                   input_iterator_tag)
{
    for (; first != last; ++first, ++result)
    {
        *result = *first;
    }
    return result;
}

//random_access iterator
template <typename RandomIter, typename OutputIter>
OutputIter _copy_aux(RandomIter first, RandomIter last, OutputIter result,
                     random_access_iterator_tag)
{
    for(auto n = last - first; n > 0; --n, ++first)
        *result = *first;
    return result;
}

template<typename InputIter, typename OutputIter>
OutputIter _copy(InputIter first, InputIter last, OutputIter result)
{
    _copy_aux(first, last, result, iterator_category(first));
}


template<typename Tp, typename Up>
typename std::enable_if<
    std::is_same<typename std::remove_const<Tp>::value, Up>::value &&
    std::is_trivially_copy_assignable<Up>::value, Up*>::type
_copy(Tp* first, Tp* last, Up* result)
{
    const auto n = static_cast<size_t>(last - first);
    if (n > 0 )
        std::memmove(result, first, n * sizeof(Up));
    return result + n ;
}



template<typename InputIter, typename OutputIter>
OutputIter copy(InputIter first, InputIter last, OutputIter result)
{
    _copy(first, last, result);
}







}















#endif //TINYSTL_ALGOBASE_H
