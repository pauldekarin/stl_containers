#pragma once
#include <memory>
#include <iostream>
#include "../vector/vector.h"

namespace s21{
    template <typename _T, class _Container = s21::vector<_T>>
    class queue{
    public:
        typedef _Container container_type;
        typedef typename container_type::value_type value_type;
        typedef typename container_type::size_type size_type;
        typedef typename container_type::reference reference;
        typedef typename container_type::const_reference const_reference;
    
    protected:
        container_type c_;
    
    public:
        queue();
        queue(std::initializer_list<value_type> const &);
        queue(const queue&);
        queue(queue&&);
        ~queue();
        queue& operator=(queue&&);

        const_reference front();
        const_reference back();

        bool empty();
        size_type size();

        void push(const_reference);
        void pop();
        void swap(queue&);
    };
}

#include "queue.tpp"