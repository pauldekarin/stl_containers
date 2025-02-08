#pragma once

#include <memory>
#include <iostream>
#include <list>

template <typename _T>
class __list_iterator{
public:
    struct __node{
        __node *head_ = nullptr;
        __node *foot_ = nullptr;

        _T value_;
        bool is_sentinel_ = false;
        __node(const _T &__v):value_(__v), is_sentinel_(false){}
    };
    using value_type = _T;
    using reference = _T&;
    using pointer =   _T*;
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;

public:
    __node *n_ = nullptr;

    __list_iterator();
    __list_iterator(__node *__n);
    template <typename _U, typename = std::enable_if<std::is_same<const _T, _U>::value>>
    __list_iterator(const __list_iterator<_U>& __it);

    __node *get() const;
    pointer operator->();
    reference operator*();
    __list_iterator& operator++();
    __list_iterator operator++(int);
    __list_iterator& operator--();
    __list_iterator operator--(int);
    __list_iterator& operator+(difference_type __n);
    bool operator==(const __list_iterator &__li) const;
    bool operator!=(const __list_iterator &__li) const;
};

namespace s21{
    
    template <typename _T, class _Allocator = std::allocator<_T>>
    class list{
    public:
        using alloc_type = _Allocator;
        using value_type = typename alloc_type::value_type;
        using reference = typename alloc_type::reference;
        using const_reference = typename alloc_type::const_reference;
        using size_type = typename alloc_type::size_type;
        using pointer = typename alloc_type::pointer;

        
        using iterator = __list_iterator<_T>;
        using const_iterator = __list_iterator<const _T>;
        
        using node_type = typename __list_iterator<_T>::__node;
        using node_pointer = node_type*;

        using node_allocator = typename std::allocator_traits<alloc_type>::template rebind_alloc<node_type>;
        using alloc_traits = std::allocator_traits<node_allocator>;

    protected:
        node_allocator alloc_;
        node_pointer root_ = nullptr;
        node_pointer sentinel_ = nullptr;
        size_type size_ = 0;

    public:
        list();

        list(size_type __n);

        list(const std::initializer_list<_T> &__il);

        list(const list &__l);

        list(list &&__l);

        ~list();

        const_reference front();

        const_reference back();

        size_type size() const noexcept;
        
        size_type max_size() const;

        inline bool empty() const;

        iterator insert(iterator __pos, const_reference __value);
        template <class... Args> iterator insert_many(const_iterator, Args&&...);
        template <class... Args> void insert_many_back(Args&&...);
        template <class... Args> void insert_many_front(Args&&...);
        void clear();

        void erase(iterator __pos);
        
        void push_back(const_reference __ref);

        void pop_back();

        void push_front(const_reference __ref);

        void swap(list &__oth);

        template <class _Compare = std::less<_T>> void merge(list &__oth, _Compare comp = _Compare());

        void splice(const_iterator __pos, list &__oth);

        void reverse();

        void unique();

        template <typename _Compare = std::less<_T>> void sort();

        iterator begin() ;
        iterator end() ;

        const_iterator begin() const;
        const_iterator end() const;

        list& operator=(const list &__oth);
        list& operator=(list &&__oth);

    private:
        template <typename _Compare = std::less<_T>>
        void _sort(iterator __begin, iterator __end, _Compare comp = _Compare());

        void _clear_node(node_pointer __n);

        void _init_sentinel();

        void _clear_sentinel();
    };
};


#include "iterator.tpp"
#include "list.tpp"