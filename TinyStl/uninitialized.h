//
// Created by Ste7an on 2022/3/30.
//

#ifndef TINYSTL_UNINITIALIZED_H
#define TINYSTL_UNINITIALIZED_H
#include "algobase.h"
#include <type_traits>
namespace tinystl{


template<typename ForwardIter, typename T>
void _uninit_fill(ForwardIter first, ForwardIter last, const T& value, std::true_type)
{
    tinystl::fill(first, last, value);
}
template<typename ForwardIter, typename T>
void _uninit_fill(ForwardIter first, ForwardIter last, const T& value, std::false_type)
{
    auto cur = first;
    try
    {
        for(; first != last; ++first)
        {
            tinystl::construct(&*first, value);
        }
    }
    catch(...)
    {
        tinystl::destroy(first, cur);
    }

}

template<typename ForwardIter, typename T>
void uninitialized_fill(ForwardIter first, ForwardIter last , const T& value)
{
    tinystl::_uninit_fill(first, last, value, std::is_trivially_copy_assignable<
                                    typename tinystl::iterator_traits<ForwardIter>::value_type>{});
}



template<typename ForwardIter, typename Size, typename T>
void _uninit_fill_n(ForwardIter first, Size n, const T& value, std::true_type )
{
    tinystl::fill_n(first, n, value);
}

template<typename ForwardIter, typename Size, typename T>
void _uninit_fill_n(ForwardIter first, Size n, const T& value, std::false_type )
{
    auto cur = first;
    try
    {
        for(; n > 0; --n, ++cur)
        {
            tinystl::construct(&*cur, value);
        }
    }
    catch(...)
    {
       tinystl::destroy(first, cur);
    }
}

    template<typename ForwardIter, typename Size, typename T>
void uninitialized_fill_n(ForwardIter first, Size n, T& value)
{
    tinystl::_uninit_fill_n(first, n, value, std::is_trivially_copy_assignable<
                                    typename tinystl::iterator_traits<ForwardIter>::value_type>{});
}



template<typename InputIter, typename ForwardIter>
ForwardIter _uninit_copy(InputIter first, InputIter last, ForwardIter result, std::true_type )
{
    return tinystl::copy(first, last, result);
}

template<typename InputIter, typename ForwardIter>
ForwardIter _uninit_copy(InputIter first, InputIter last, ForwardIter result, std::false_type )
{
    auto cur = result;
    try
    {
        for(; first != last; ++first, ++cur)
        {
            tinystl::construct(&*cur, *first);
        }
    }
    catch(...)
    {
        for (; result != cur; --cur)
        {
            tinystl::destroy(&*cur);
        }
    }
    return cur;
}

/**
 * @brief copies the range[first, last] into result
 * @param first input iterator
 * @param last  input iterator
 * @param result
 * @return result + (last -first)
 *
 * don't require an initialized  output range
 * check if result is trivially copy assignable
 * if true call tinystl::copy
 * else call ctor
 */
template<typename InputIter, typename ForwardIter>
ForwardIter uninitialized_copy(InputIter first, InputIter last, ForwardIter result)
{
    return _uninit_copy(first, last, result,
                        std::is_trivially_copy_assignable<
                        typename iterator_traits<ForwardIter>::value_type>{});
}

template<typename RandomAccessIter, typename Size, typename ForwardIter>
ForwardIter _uninit_copy_n(RandomAccessIter first, Size n, ForwardIter result, tinystl::random_access_iterator_tag)
{
    return tinystl::uninitialized_copy(first, first + n, result);
}

template<typename InputIter, typename Size, typename ForwardIter>
ForwardIter _uninit_copy_n(InputIter first, Size n, ForwardIter result, tinystl::input_iterator_tag)
{
    auto cur = result;
    try
    {
        for(; n > 0; --n, ++first)
        {
            tinystl::construct(&*cur, *first);
        }
    }
    catch(...)
    {
        tinystl::destroy(result, cur);
    }
}

    /**
 * @brief copies the range[first, last] into result
 * @param first input iterator
 * @param n     the number of elements to copy
 * @param result
 * @return result + n
 *
 * don't require an initialized  output range
 */

template<typename InputIter, typename ForwardIter>
ForwardIter uninitialized_copy_n(InputIter first, InputIter last, ForwardIter result)
{
    return _uninit_copy_n(first, last, result,tinystl::iterator_category(first));

}

template<typename InputIter, typename ForwardIter>
ForwardIter _uninit_move(InputIter first, InputIter last, ForwardIter result, std::false_type)
{
    ForwardIter cur = result;
    try
    {
        for(; first != last; ++first, ++cur)
            tinystl::construct(&*cur, std::move(*first));
    }
    catch(...)
    {
        tinystl::destroy(result, cur);
    }
}

template<typename InputIter, typename ForwardIter>
ForwardIter _uninit_move(InputIter first, InputIter last, ForwardIter result, std::true_type)
{
    return tinystl::move(first, last, result);
}

//move ctor
template<typename InputIter, typename ForwardIter>
ForwardIter uninitialized_move(InputIter first, InputIter last, ForwardIter result)
{
    return _uninit_move(first, last, result,
                        std::is_trivially_move_assignable<
                        typename iterator_traits<InputIter>::value_type>{} );
}

} //namespace tinystl


#endif //TINYSTL_UNINITIALIZED_H
