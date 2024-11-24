#pragma once

#include <memory>
#include <iostream>
#include <iterator>

namespace s21{
    template <typename _T>
    class __vec_iterator{
    public:
        typedef _T                              value_type;
        typedef _T*                             pointer;
        typedef _T&                             reference;
        typedef const _T&                       const_reference;
        typedef std::random_access_iterator_tag iterator_category;
        typedef std::ptrdiff_t                  difference_type;
        typedef std::size_t                     size_type;

        __vec_iterator();
        __vec_iterator(pointer __p = nullptr);
        __vec_iterator(const __vec_iterator &__i);

        __vec_iterator& operator++();

        __vec_iterator operator++(int);

        __vec_iterator& operator--();

        __vec_iterator operator--(int);

        __vec_iterator& operator+=(difference_type);

        __vec_iterator& operator-=(difference_type);

        __vec_iterator operator+(difference_type);


        difference_type operator-(__vec_iterator&);

        bool operator==(const __vec_iterator&);

        bool operator!=(const __vec_iterator&);

        reference operator*();

        pointer operator->();

    
    protected:
        pointer __ptr__;

    };

    template <typename _T, class _Allocator = std::allocator<_T>>
    class vector{
    public: 
        using alloc_type        =       typename std::allocator_traits<_Allocator>::template rebind_alloc<_T>;
        using alloc_traits      =       std::allocator_traits<alloc_type>;
        using value_type        =       typename alloc_type::value_type;
        using reference         =       typename alloc_type::reference;
        using const_reference   =       typename alloc_type::const_reference;
        using pointer           =       typename alloc_type::pointer;
        using iterator          =       __vec_iterator<value_type>;
        using const_iterator    =       __vec_iterator<const value_type>;
        using reverse_iterator  =       std::reverse_iterator<iterator>;
        using size_type         =       typename alloc_type::size_type;


    protected:
        alloc_type alloc_;
        pointer begin_ = nullptr;
        pointer end_ = nullptr;
        pointer cap_ = nullptr;

    public: 
        vector();	
        vector(size_type);	
        vector(std::initializer_list<value_type> const &);	
        vector(const vector &);	
        vector(vector &&);	
        ~vector();	
        vector& operator=(vector &&);

        reference at(size_type pos);	
        reference operator[](size_type pos);;	
        const_reference front();	
        const_reference back();	
        pointer data();

        iterator begin();
        iterator end();

        const_iterator begin() const;
        const_iterator end() const;

        reverse_iterator rbegin();
        reverse_iterator rend();

        bool empty();	
        size_type size();	
        size_type max_size();	
        void reserve(size_type size);	
        size_type capacity();	
        void shrink_to_fit();

        iterator insert(iterator pos, const_reference value);	
        void clear();	
        void erase(iterator pos);	
        void push_back(const_reference value);	
        void swap(vector& other);
        void pop_back();	
    
    private:
        void __destroy();
        void __move(vector&&);
        template <class _InputIter>
        void __construct(_InputIter __f, _InputIter __l);
    };
}

#include "iterator.tpp"
#include "vector.tpp"