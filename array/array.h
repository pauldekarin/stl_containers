#pragma once

#include <iterator>
#include <memory>
#include <array>

namespace s21{
    template <typename _T, std::size_t _N>
    class array{
    public:
        typedef _T value_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef std::size_t size_type;
        typedef value_type* pointer;
        typedef const value_type* const_pointer;
        typedef std::ptrdiff_t diffeence_type;

        typedef pointer iterator;
        typedef const_pointer const_iterator;

        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        typedef std::random_access_iterator_tag iterator_category;
    
    protected:
        value_type data_[_N];
    
    public:
        array();	
        array(std::initializer_list<value_type> const &items);	
        array(const array &a);
        array(array &&a);	
        ~array();	
        array& operator=(array &&a);	
        reference at(size_type pos);	
        reference operator[](size_type pos);	
        const_reference front();
        const_reference back();
        iterator data();	
        iterator begin() const;
        iterator end() const;
        bool empty();
        size_type size();	
        size_type max_size();
        void swap(array& other);
        void fill(const_reference value);
    };
}

#include "array.tpp"