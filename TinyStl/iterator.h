//
// Created by ste7an on 2022/3/16.
//

#ifndef TINYSTL_ITERATOR_H
#define TINYSTL_ITERATOR_H

#include<cstddef>

namespace tinystl
{
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

//判断Iterator 是否 有 category
template<class T>
struct _has_iterator_category
{
private:
    struct _two{char _val; char _vall;};
    template<class U> static _two _test(...);
    template<class U> static char _test(typename U::Iterator_category* = 0);

public:
    static const bool value = sizeof(_test<T>(0)) == 1;
};


template<class Iterator, bool>
struct _iterator_traits_impl {};

template<class Iterator>
struct _iterator_traits_impl<Iterator, true>
{
    typedef typename Iterator::iterator_category    iterator_category;
    typedef typename Iterator::value_type           value_type;
    typedef typename Iterator::difference_type      difference_type;
    typedef typename Iterator::pointer              pointer;
    typedef typename Iterator::reference            reference;
};

//泛化的 _iterator_traits
//模版参数 Iterator ：
//模版参数 bool ：表示Iterator是否有category
//false 则返回一个空类
//true 匹配特化版本_iterator_traits<Iterator, true>
template<class Iterator,  bool>
struct _iterator_traits{};

//_iterator_traits 特化版本
//_has_iterator_category 为True
//然后判断category 类型 是否可以 转换成如下 两种
template<class Iterator>
struct _iterator_traits<Iterator, true>
        : public _iterator_traits_impl<Iterator,
                std::is_convertible<typename Iterator::iterator_category, input_iterator_tag>::value ||
                std::is_convertible<typename Iterator::iterator_category, output_iterator_tag>::value>
{};

//首先判断Iter 是否有 category
template<class Iterator>
struct iterator_traits
        : public _iterator_traits<Iterator, _has_iterator_category<Iterator>::value>{};


//iterator_traits
//针对naive pointer 特化版本

template<class T>
struct iterator_traits<T*>
{
    typedef random_access_iterator_tag      iterator_category;
    typedef T                               value_type;
    typedef T*                              pointer;
    typedef ptrdiff_t                       difference_type;
    typedef T&                              reference;
};

template<class T>
struct iterator_traits<const T*>
{
    typedef random_access_iterator_tag      iterator_category;
    typedef T                               value_type;
    typedef const T*                        pointer;
    typedef ptrdiff_t                       difference_type;
    typedef const T&                        reference;
};


//has iterator category convertible to
template<class T, class U, bool = _has_iterator_category<T>::value>
struct _has_iterator_category_convertible_to
    :public std::integral_constant<bool,
        std::is_convertible<typename T::iterator_category, U>::value>
{};


template<class T, class U>
struct _has_iterator_category_convertible_to<T, U, false> :public std::false_type{};

template<class Iterator>
struct is_input_iterator : public _has_iterator_category_convertible_to<Iterator, input_iterator_tag>{};

template<class Iterator>
struct is_output_iterator : public _has_iterator_category_convertible_to<Iterator, output_iterator_tag>{};

template<class Iterator>
struct is_forward_iterator : public _has_iterator_category_convertible_to<Iterator, forward_iterator_tag>{};

template<class Iterator>
struct is_bidirectional_iterator : public _has_iterator_category_convertible_to<Iterator, bidirectional_iterator_tag>{};

template<class Iterator>
struct is_random_access_iterator :  public _has_iterator_category_convertible_to<Iterator, random_access_iterator_tag>{};


template<class Iterator>
struct is_iterator
        :   public std::integral_constant<bool,
                is_input_iterator<Iterator>::value || is_output_iterator<Iterator>::value>{};


//traits iterator_category
//return a category object
template<class Iterator>
typename iterator_traits<Iterator>::iterator_category
iterator_category(const Iterator&)
{
    typedef typename iterator_traits<Iterator>::iterator_category category;
    return category();
}


//traits value-type
//return a null pointer to value_type
template<class Iterator>
typename iterator_traits<Iterator>::value_type*
value_type(const Iterator&)
{
    return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}

//traits difference_type
//return a null pointer to value_type
template<class Iterator>
typename iterator_traits<Iterator>::difference_type*
difference_type(const Iterator&)
{
    return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
}



//distance for input_iterator
template<class InputIter>
typename iterator_traits<InputIter>::difference_type
_distance(InputIter first, InputIter last, input_iterator_tag)
{
    typename iterator_traits<InputIter>::difference_type n = 0;
    while( first != last)
    {
        ++first;
        ++n;
    }
    return n;
}

//distance for random_access_iterator
template<class RandIter>
typename iterator_traits<RandIter>::difference_type
_distance(RandIter first, RandIter last, random_access_iterator_tag)
{
    return last - first;
}

//accumulate distance between iterators
template<class InputIter>
typename iterator_traits<InputIter>::diference_type
distance(InputIter first, InputIter last)
{
    return _distance(first, last, iterator_category(first))   ;
}

//random_access_iterator advance n
template<class RandIter, class Distance>
void _advance(RandIter& iter, Distance n, random_access_iterator_tag)
{
    iter += n ;
}

//input_iterator advance n
template<class InputIter, class Distance>
void _advance(InputIter& iter, Distance n, input_iterator_tag)
{
    while(n--)
        ++iter;
}

//bidirectional_iterator advance n
template<class BiDirIter, class Distance>
void _advance(BiDirIter& iter, Distance n, bidirectional_iterator_tag)
{
    if(n > 0)
    {
        while(n--)
            ++iter;
    }
    else
    {
        while(n++)
            --iter;
    }
}

//iterator advance  n
template<class InputIter, class Distance>
void advance(InputIter& iter, Distance n)
{
    _advance(iter, n, iterator_category(iter));
}



//reverse_iterator class
template<class Iter>
struct reverse_iterator
    :   public iterator<typename iterator_traits<Iter>::iterator_category,
                        typename iterator_traits<Iter>::value_type,
                        typename iterator_traits<Iter>::diference_type,
                        typename iterator_traits<Iter>::pointer,
                        typename iterator_traits<Iter>::reference>

{
public:
    typedef             Iter                                        iterator_type;
    typedef typename    iterator_traits<Iter>::difference_type      difference_type;
    typedef typename    iterator_traits<Iter>::pointer              pointer;
    typedef typename    iterator_traits<Iter>::reference            reference;
    typedef             reverse_iterator<Iter>                      self;

private:
    Iter current;

public:
    //ctor
    reverse_iterator() : current() {}
    explicit reverse_iterator(iterator_type iter) :current(iter){};
    reverse_iterator(const reverse_iterator<Iter>& iter) :current(iter.current){}

public:

    iterator_type base() const { return current; }

    //operator overriding
    reference operator*() const
    {
        Iter tmp = current;
        return *--tmp;
    }
    pointer operator->() const
    {
        return &(operator*());
    }
    self& operator++()
    {
        ++current;
        return *this;
    }
    self operator++(int)
    {
        self tmp = *this;
        --current;
        return tmp;
    }
    self& operator--()
    {
        ++current;
        return *this;
    }
    self operator--(int)
    {
        self tmp = *this;
        ++current;
        return tmp;
    }
    self& operator+(difference_type n)
    {
        current -= n;
        return *this;
    }
    self operator+=(difference_type n)
    {
        return self(current - n);
    }
    self& operator-(difference_type n)
    {
        current += n;
        return *this;
    }
    self operator-=(difference_type n)
    {
        return self(current + n);
    }

    reference operator[](difference_type n)
    {
        return *(*this + n);
    }
};

//operator- computes the distance
template <class Iterator>
typename reverse_iterator<Iterator>::difference_type
operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return lhs.base() - rhs.base();
}


//TODO:function template operator+   overriding

// compare operator overriding
template <class Iterator>
bool operator==(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs)
{
    return lhs.base() == rhs.base();
}

template <class Iterator>
bool operator<(const reverse_iterator<Iterator>& lhs,
               const reverse_iterator<Iterator>& rhs)
{
    return rhs.base() < lhs.base();
}

template <class Iterator>
bool operator!=(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs)
{
    return !(lhs == rhs);
}

template <class Iterator>
bool operator>(const reverse_iterator<Iterator>& lhs,
               const reverse_iterator<Iterator>& rhs)
{
    return rhs < lhs;
}

template <class Iterator>
bool operator<=(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs)
{
    return !(rhs < lhs);
}

template <class Iterator>
bool operator>=(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs)
{
    return !(lhs < rhs);
}

} // namespace tinystl
#endif //TINYSTL_ITERATOR_H
