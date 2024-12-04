#pragma once

#include "../tree/tree.h"

#include <iterator>
#include <memory>

namespace s21{
    template <typename _T, class _Compare = std::less<_T>, class _Allocator = std::allocator<_T>>
    class multiset{
    public:
        typedef _Allocator allocator_type;
        typedef _Compare value_compare;
        typedef _T key_type	;
        typedef key_type value_type	;
        typedef typename allocator_type::reference reference	;
        typedef typename allocator_type::const_reference const_reference	;

        typedef s21::__tree<value_type, value_compare, allocator_type> __base;
        typedef typename __base::iterator iterator;
        typedef typename __base::const_iterator	const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef typename __base::size_type size_type	;
    protected:
        __base tree_;

    public:
        multiset()	;
        multiset(std::initializer_list<value_type> const &items)	;
        multiset(const multiset &s);
        multiset(multiset &&s);
        ~multiset()	;
        multiset& operator=(multiset &&s)	;
        iterator begin()	;
        iterator end()	;
        iterator begin() const;
        iterator end() const;
        reverse_iterator rbegin();
        reverse_iterator rend();
        reverse_iterator rbegin() const;
        reverse_iterator rend() const;
        bool empty();
        size_type size();
        size_type max_size()	;
        void clear();
        std::pair<iterator, bool> insert(const_reference);
        template <class... Args> std::pair<iterator, bool> insert_many(Args&&...);
        void erase(iterator);
        void erase(iterator, iterator);
        void erase(const_reference);
        void swap(multiset&);
        void merge(multiset&);
        iterator find(const_reference);
        iterator lower_bound(const_reference);
        iterator upper_bound(const_reference);
        size_type count(const_reference);
        bool contains(const_reference);
    };
}

#include "multiset.tpp"