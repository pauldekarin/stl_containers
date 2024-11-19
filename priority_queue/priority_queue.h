#pragma once

#include "../vector/vector.h"

namespace s21{
    template <typename _T, class _Container = s21::vector<_T>, class _Compare = std::less<typename _Container::value_type>>
    class priority_queue{
    public:
        typedef _Container container_type;
        typedef _Compare value_compare;
        typedef typename container_type::reference reference;
        typedef typename container_type::const_reference const_reference;
        typedef typename container_type::value_type value_type;
        typedef typename container_type::size_type size_type;
    
    protected:
        container_type c_;
        value_compare comp_;

    public:
        priority_queue();
        priority_queue(std::initializer_list<value_type> const&);
        priority_queue(const priority_queue&);
        priority_queue(priority_queue&&);
        ~priority_queue();
        priority_queue& operator=(priority_queue&&);
        bool empty();
        size_type size();
        const_reference top();
        void push(const_reference);
        void pop();
        void swap(priority_queue&);
    };
};

#include "priority_queue.tpp"