#pragma once
#include <memory>
#include <initializer_list>
#include <iostream>
#include "../vector/vector.h"

namespace s21{
    template <typename _T, class _Container = s21::vector<_T>>
    class stack{
    public:
        typedef _Container container_type;
        typedef typename container_type::value_type value_type;
        typedef typename container_type::size_type size_type;
        typedef typename container_type::reference reference;
        typedef typename container_type::const_reference const_reference;
    
    protected:
        container_type c_;
    
    public:
        stack();
        stack(std::initializer_list<value_type> const &);
        stack(const stack&);
        stack(stack&&);
        ~stack();
        stack& operator=(stack&&);
        const_reference top();
        bool empty();
        size_type size();
        void push(const_reference);
        template <class... Args> void insert_many_back(Args&&...);
        void pop();
        void swap(stack&);
    };
}

#include "stack.tpp"