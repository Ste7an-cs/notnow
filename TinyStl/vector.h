//
// Created by ste7an on 2022/3/16.
//

#ifndef TINYSTL_VECTOR_H
#define TINYSTL_VECTOR_H
#include "iterator.h"

namespace TINYSTL
{

template<class T>
class vector
{
    static_assert(!std::is_same<bool, T>::value, "vector<bool> is abandoned in tinystl");

public:
    //vector typedef

    typedef tinystl::allocator<T>                                  allocator_type;
    typedef tinystl::allocator<T>                                  data_allocator;

    typedef typename allocator_type::value_type                    value_type;
    typedef typename allocator_type::size_type                     size_type;
    typedef typename allocator_type::difference_type               difference_type;
    typedef typename allocator_type::pointer                       pointer;
    typedef typename allocator_type::const_pointer                 const_pointer;
    typedef typename allocator_type::reference                     reference;
    typedef typename allocator_type::const_reference               const_reference;


    //vector iterator
    typedef value_type*                                            iterator;
    typedef const value_type*                                      const_iterator;

    typedef tinystl::reverse_iterator<iterator>                    reverse_iterator;
    typedef tinystl::reverse_iterator<const_iterator>              const_reverse_iterator;

private:

    iterator begin_;
    iterator end_;
    iterator cap_; //end - begin


public:

    //vector ctor

    vector() noexcept
    {
        default_init();
    }

    //create a vector with default constructed elements
    //fill the vector with n default constructed elements
    explicit vector(size_type n)
    {
         fill_init(n, value_type());
    }

   vector(size_type n, const value_type& value)
   {
        fill(n, value);
   }

    //copy ctor from [first, last)
    template<class InputIter, typename std::enable_if<
      tinystl::is_input_iterator<InputIter>::value, int>::value = 0>
    vector(InputIter first, InputIter last)
    {
        range_init(first, last, tinystl::iterator_category(first));
    }

    //copy ctor from another vector
    vector(const vector& other)
    {
        range_init(other.begin_, other.end_, tinystl::iterator_category(other.end_));
    }

    //move ctor

    vector(vector&& other) noexcept
    :begin_(other.begin_), end_(other.end_), cap_(other.cap_)
    {
        other.begin_ = nullptr;
        other.end_ = nullptr;
        other.cap_ = nullptr;
    }

   //initializer_list
   vector(std::initializer_list<value_type> list)
   {
        range_init(list.begin(), list.end(), tinystl::random_access_iterator_tag() );
   }

    vector& operator=(const vector& rhs);
    vector& operator=(vector&& rhs) noexcept;

    vector& operator=(std::initializer_list<value_type> ilist)
    {
        vector tmp(ilist.begin(), ilist.end());
        swap(tmp);
        return *this;
    }

    ~vector()
    {
        destroy_and_recover(begin_, end_, cap_ - begin_);
        begin_ = end_ = cap_ = nullptr;
    }


private:
    //helper functions

    // called by vector()
    void        default_init() noexcept;

    //called by vector( n ) ,vector(n, value_type)
    void        fill_init(size_type n, const value_type& value);

    //called by fill init() , range init()
    //
    void        init_space(size_type size, size_type cap);


    template<class Iter>
    void        range_init(Iter first, Iter last, tinystl::input_iterator_tag);
    template<class Iter>
    void        range_init(Iter first, Iter last, tinystl::forward_iterator_tag);


    //destroy and deallocate
    void        destroy_and_recover();


    //calculate the growth size
    size_type   get_new_cap(size_type add_size);


    //assign

    void        fill_assign(size_type n, const value_type& value);

    template <class InputIter>
    void        copy_assign(InputIter first, InputIter last, tinystl::input_iterator_tag);

    template<class ForwardIter>
    void        copy_assign(ForwardIter first, ForwardIter last, tinystl::forward_iterator_tag);

    //reallocate

    template<class... Args>
    void        reallocate_emplace(iterator pos,Args&&... args);
    void        reallocate_insert(iterator pos, const value_type& value);


    //insert

    iterator    fill_insert(iterator pos, size_type n, const value_type& value);
    template<class InputIter>
    void        copy_insert(iterator pos, InputIter first, InputIter last);


    //shrink to fit

    void        reinsert(size_type size);





};

    template<class T>
    void vector<T>::default_init() noexcept {

    }


}






#endif //TINYSTL_VECTOR_H
