#pragma once

#include <memory>
#include <deque>
#include <iostream>
#include <type_traits>

template <typename _T, size_t buff_size = 8>
struct __deque_iterator{
public:
    typedef _T**                                __map_pointer;
    typedef _T*                                 pointer;
    typedef std::random_access_iterator_tag     iterator_category;
    typedef std::ptrdiff_t                      difference_type;
    typedef _T                                  value_type;
    typedef _T&                                 reference;
protected:
    
public:
    pointer current_ = nullptr;
    pointer begin_ = nullptr;
    pointer end_ = nullptr;

    __map_pointer map_ = nullptr;
    __deque_iterator();
    
    template <typename _U>
    __deque_iterator(const __deque_iterator<_U, buff_size> &__d);

    __deque_iterator(pointer __begin, pointer __end, pointer __current, __map_pointer __map);

    __deque_iterator(const __deque_iterator &__d);
    
    void _assign(difference_type __n = 0);
    reference operator*();
    
    __deque_iterator& operator+=(difference_type __n);
    __deque_iterator& operator-=(difference_type __n);
    __deque_iterator operator-(difference_type __n);
    
    difference_type operator-(const __deque_iterator &__it);       
    __deque_iterator operator+(difference_type __n);

    __deque_iterator& operator++();

    __deque_iterator& operator=(const __deque_iterator &__it);
    __deque_iterator& operator=(__deque_iterator &&__it);        
    __deque_iterator operator++(int);
    __deque_iterator& operator--();

    __deque_iterator operator--(int);
    bool operator==(const __deque_iterator &__it);
    bool operator!=(const __deque_iterator &__it);    
};


namespace s21{
    template <typename _T, class _Allocator = std::allocator<_T>>
    class deque{
    public:
        typedef typename _Allocator::value_type                                                     value_type;
        typedef typename _Allocator::reference                                                      reference;
        typedef typename _Allocator::const_reference                                                const_reference;
        typedef typename std::allocator_traits<_Allocator>::template rebind_alloc<value_type>       alloc_type;
        typedef __deque_iterator<_T>                                                                iterator;
        typedef __deque_iterator<const _T>                                                          const_iterator;
        typedef std::reverse_iterator<iterator>                                                     reverse_iterator;
        typedef std::reverse_iterator<const_iterator>                                               const_reverse_iterator;
        typedef typename _Allocator::pointer                                                        pointer;
        typedef typename _Allocator::size_type                                                      size_type;

        typedef typename std::allocator_traits<_Allocator>::template rebind_alloc<value_type>       __value_alloc;
        typedef std::allocator_traits<__value_alloc>                                                __value_traits;

        typedef typename __deque_iterator<_T>::__map_pointer                                        __map_pointer;
        typedef typename std::allocator_traits<_Allocator>::template rebind_alloc<pointer>    __map_alloc;
        typedef std::allocator_traits<__map_alloc>                                                  __map_traits;
        struct __deque_range{
            
        };
    protected:
        alloc_type alloc_;

        size_type __chunk_size = 8;
        size_type size_ = 0;

        __value_alloc val_alloc_;

        __map_alloc map_alloc_;
        __map_pointer map_ = nullptr;
        size_type __map_size = 0;

        iterator head_;
        iterator tail_;

    public: 
        deque();        
        deque(std::initializer_list<value_type> const &__il);
        deque(const deque &__dq);
        deque(deque &&__dq);
        ~deque();
        deque& operator=(deque &&__dq);
        iterator begin();
        iterator end();
        const_iterator begin() const;        
        const_iterator end() const;
        reverse_iterator rbegin();        
        reverse_iterator rend();
        const_reference front();
        const_reference back();
        bool empty();
        size_type size();
        void clear();
        size_type capacity();
        void push_front(const_reference __ref);

        void push_back(const_reference __ref);
        void insert(iterator __pos, const_reference __ref);

        void insert(iterator __pos, size_type __n, const_reference __ref);
        void shrink_to_fit();
        
        template <class _InputIter, typename = typename std::enable_if<!std::is_integral<_InputIter>::value>::type>
        void insert(iterator __pos, _InputIter __f, _InputIter __l);
        void pop_back();
        void pop_front();        
        void erase(iterator __pos);
    
    private:
        void _move(deque &&__dq);
        template <class _InputIter>
        void _construct(_InputIter __b, _InputIter __e);
        bool _has_avaliable_space(bool in_front = true);

        void _increase_map(bool in_front = true, size_type __n = 1);

        pointer  __create_chunk();
        pointer __copy_chunk(pointer __src);
        void __clear_chunk(pointer __chunk);
        void _deallocate();   
    };
};

#include "iterator.tpp"
#include "deque.tpp"