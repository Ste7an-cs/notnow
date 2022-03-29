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
    //create a vector with default constructed elements
    vector() noexcept
    {
        default_init();
    }

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

   //assignment operator
   vector& operator=(const vector& rhs);
   vector& operator=(vector&& rhs) noexcept;

   vector& operator=(std::initializer_list<value_type> ilist)
   {
       vector tmp(ilist.begin(), ilist.end());
       swap(tmp);
       return *this;
   }


    //destroy
    ~vector()
    {
        destroy_and_recover(begin_, end_, cap_ - begin_);
        begin_ = end_ = cap_ = nullptr;
    }

public:

    //iterators

    iterator                     begin()   noexcept { return begin_;}
    const_iterator               begin()   const noexcept { return begin_;}
    iterator                     end()     noexcept { return end_;}
    const_iterator               end()     const noexcept { return end_;}

    reverse_iterator             rbegin()  noexcept { return reverse_iterator(end());}
    const_reverse_iterator       rbegin()  const noexcept {return const_reverse_iterator(end());}
    reverse_iterator             rend()    noexcept { return reverse_iterator(begin());}
    const_reverse_iterator       rend()    const noexcept { return const_reverse_iterator(begin());}

    const_iterator              cbegin()   const noexcept   { return begin();}
    const_iterator              cend()     const noexcept   { return end();}
    const_reverse_iterator      crbegin()  const noexcept   { return rbegin();}
    const_reverse_iterator      crend()    const noexcept   { return rend();}


    //capacity

    bool        empty()         const noexcept { return begin_ == end_; }
    size_type   size()          const noexcept { return static_cast<size_type>(end_ - begin_) ; }
    size_type   max_size()      const noexcept { return static_cast<size_type>(-1) / sizeof(T); }
    size_type   capacity()      const noexcept { return static_cast<size_type>(cap_ - begin_); }


    void        reserve(size_type new_cap);
    void        shrink_to_fit();

    //elements access

    reference operator[](size_type n)
    {
        assert(n < size());
        return *(begin_ + n);
    }

    const_reference operator[](size_type n) const
    {
        assert(n < size());
        return *(begin_ + n);
    }

    reference at(size_type n)
    {
        if(n > size()) throw std::out_of_range("");
        return (*this)[n];
    }

    const_reference at(size_type n) const
    {
        if(n > size()) throw std::out_of_range("");
        return (*this)[n];
    }

    reference front()
    {
        assert(!empty());
        return *begin_;
    }
    const_reference front() const
    {
        assert(!empty());
       return  *begin_;
    }

    reference back()
    {
       assert(!empty());
       return  *(end_ - 1);
    }
    reference back() const
    {
        assert(!empty());
        return  *(end_ - 1);
    }

    pointer data()          noexcept { return begin_;}
    const_pointer data() const noexcept { return begin_;}

    //assign
    void assign(size_type n, const value_type& value)
    { fill_assign(n, value); }

   template<class InputIter, typename std::enable_if<
           tinystl::is_input_iterator<InputIter>::value, int> = 0>
    void assign(InputIter first, InputIter last)
   {
        assert(!(last < first));
        copy_assign(first, last, tinystl::iterator_category(first));
   }

   void assign(std::initializer_list<value_type> list)
   { copy_assign(list.begin(), list.end(), tinystl::random_access_iterator_tag()); }


   //emplace / emplace_back

   template<class... Args>
   iterator emplace(const_iterator pos, Args&&... args);


    template<class... Args>
    iterator emplace_back(Args&& ...args);


    //push_back / pop_back
    void push_back(const value_type& value);
    void push_back(value_type&& value) { emplace_back(std::move(value)); }
    void pop_back();

    //insert

    iterator insert(const_iterator pos, const value_type& value);
    iterator insert(const_iterator pos, value_type&& value) {return emplace(pos, std::move(value)); }

    iterator insert(const_iterator pos, size_type n, value_type& value)
    {
        assert(pos >= begin() && pos <= end());
        return fill_insert(const_cast<iterator>(pos), n, value);
    }

    template<class InputIter, typename std::enable_if<
            tinystl::is_input_iterator<InputIter>::value, int>::value = 0>
    iterator insert(const_iterator pos, InputIter first, InputIter last)
    {

        assert(pos >= begin() && pos <= end() && !(last < first));
        difference_type offset = pos - cbegin();
        _range_insert(begin() + offset, first, last, tinystl::iterator_category(first) );
        return begin() + offset;
    }

    iterator insert(const_iterator pos, std::initializer_list<value_type> list)
    {
        difference_type offset = pos - cbegin();
        _range_insert(begin() + offset, list.begin(), list.end(), tinystl::random_access_iterator_tag() );
        return begin() + offset;
    }


    //erase  / clear

    iterator erase(const iterator pos);
    iterator erase(const iterator first, const iterator last);
    void     clear() { erase(begin() , end()); }


    //resize  /reverse

    void resize(size_type new_size){ return resize(new_size, value_type()); }
    void resize(size_type new_size, value_type& value);

    //TODO: algorithm
    void reverse(){ }

    //swap
    void swap(vector& other) noexcept;



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

    void        move_assign(vector&& other, std::true_type);
    void        move_assign(vector&& other, std::false_type);

    //reallocate

    template<class... Args>
    void        reallocate_emplace(iterator pos,Args&&... args);
    void        reallocate_insert(iterator pos, const value_type& value);


    //insert

    iterator    fill_insert(iterator pos, size_type n, const value_type& value);

    template<class InputIter>
    void        _range_insert(iterator pos, InputIter first, InputIter last, tinystl::input_iterator_tag);
    template<class ForwardIter>
    void        _range_insert(iterator pos, ForwardIter first, ForwardIter last, tinystl::forward_iterator_tag);




    //shrink to fit

    void        reinsert(size_type size);





};

    template<class T>
    void vector<T>::default_init() noexcept {

    }

    template<class T>
    void vector<T>::reinsert(vector::size_type size) {

    }


}






#endif //TINYSTL_VECTOR_H
