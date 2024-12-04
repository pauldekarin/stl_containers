#pragma once

#include "vector.h"

namespace s21{
    template<typename _T, class _Allocator>
    vector<_T, _Allocator>::vector(){}

    template<typename _T, class _Allocator>
    vector<_T, _Allocator>::vector(vector<_T, _Allocator>::size_type __n){
        this->begin_ = alloc_traits::allocate(this->alloc_, __n + 1);
        this->end_ = std::next(this->begin_, __n);
        this->cap_ = std::next(this->begin_, __n);
    }

    template<typename _T, class _Allocator>
    vector<_T, _Allocator>::vector(std::initializer_list<value_type> const &__il){
        this->__construct(__il.begin(), __il.end());
    }

    template<typename _T, class _Allocator>
    vector<_T, _Allocator>::vector(const vector &__oth){
        this->__construct(__oth.begin(), __oth.end());
    }

    template<typename _T, class _Allocator>
    vector<_T, _Allocator>::vector(vector &&__oth){
        this->__move(std::move(__oth));
    }

    template<typename _T, class _Allocator>
    vector<_T, _Allocator>::~vector(){
        this->__destroy();
    }

    template<typename _T, class _Allocator>
    vector<_T, _Allocator>& vector<_T, _Allocator>::operator=(vector &&__oth){
        this->__move(std::move(__oth));

        return *this;
    }

    template<typename _T, class _Allocator>
    typename vector<_T, _Allocator>::reference vector<_T, _Allocator>::at(size_type __pos){
        if(__pos >= this->size()){
            throw std::out_of_range("s21::vector operator[] out of bounds");
        }

        return *std::next(this->begin(), __pos);
    }

    template<typename _T, class _Allocator>
    typename vector<_T, _Allocator>::reference vector<_T, _Allocator>::operator[](size_type __pos){
        return this->at(__pos);
    }

    template<typename _T, class _Allocator>
    typename vector<_T, _Allocator>::const_reference vector<_T, _Allocator>::front(){
        if(this->empty()){
            throw std::out_of_range("front is empty");
        }

        return *this->begin();
    }

    template<typename _T, class _Allocator>
    typename vector<_T, _Allocator>::const_reference vector<_T, _Allocator>::back(){
        if(this->empty()){
            throw std::out_of_range("back is empty");
        }
        return *std::prev(this->end());
    }

    template<typename _T, class _Allocator>
    typename vector<_T, _Allocator>::pointer vector<_T, _Allocator>::data(){
        return this->begin_;
    }

    template<typename _T, class _Allocator>
    typename vector<_T, _Allocator>::iterator vector<_T, _Allocator>::begin(){
        return iterator(this->begin_);
    }

    template<typename _T, class _Allocator>
    typename vector<_T, _Allocator>::iterator vector<_T, _Allocator>::end(){
        return iterator(this->end_);
    }

    template<typename _T, class _Allocator>
    typename vector<_T, _Allocator>::const_iterator vector<_T, _Allocator>::begin() const{
        return const_iterator(this->begin_);
    }
    
    template<typename _T, class _Allocator>
    typename vector<_T, _Allocator>::const_iterator vector<_T, _Allocator>::end() const{
        return const_iterator(this->end_);
    }

    template <typename _T, class _Allocator>
    typename vector<_T, _Allocator>::reverse_iterator vector<_T, _Allocator>::rbegin(){
        return reverse_iterator(this->end());
    }

    template <typename _T, class _Allocator>
    typename vector<_T, _Allocator>::reverse_iterator vector<_T, _Allocator>::rend(){
        return reverse_iterator(this->begin());
    }

    template<typename _T, class _Allocator>
    bool vector<_T, _Allocator>::empty(){
        return this->begin_ == this->end_;
    }

    template<typename _T, class _Allocator>
    typename vector<_T, _Allocator>::size_type vector<_T, _Allocator>::size(){
        return static_cast<size_type>(std::distance(this->begin_, this->end_));
    }

    template<typename _T, class _Allocator>
    typename vector<_T, _Allocator>::size_type vector<_T, _Allocator>::max_size(){
        return static_cast<size_type>(std::allocator_traits<alloc_type>::max_size(this->alloc_));
    }

    template<typename _T, class _Allocator>
    void vector<_T, _Allocator>::reserve(size_type __s){
        if(this->capacity() < __s){
            
            pointer __ptr = alloc_traits::allocate(this->alloc_, __s);
            size_type __size = this->size();

            for(size_type __i = 0; __i < __size; __i++){
                alloc_traits::construct(this->alloc_, std::next(__ptr, __i), this->begin_[__i]);
            }

            this->__destroy();

            this->begin_ = __ptr;
            this->end_ = __ptr + __size;
            this->cap_ = __ptr + __s;
        }
    }

    template<typename _T, class _Allocator>
    typename vector<_T, _Allocator>::size_type vector<_T, _Allocator>::capacity(){
        return static_cast<size_type>(std::distance(this->begin_, this->cap_));
    }

    template<typename _T, class _Allocator>
    void vector<_T, _Allocator>::shrink_to_fit(){
        this->cap_ = this->end_;
    }

    template<typename _T, class _Allocator>
    typename vector<_T, _Allocator>::iterator vector<_T, _Allocator>::insert(iterator __pos, const_reference __ref){
        size_type __n = std::distance(this->begin(), __pos);

        if(this->size() >= this->capacity()){
            this->reserve(this->size() + 2);
        }
        
        for(iterator it = this->end(); it != std::next(this->begin(), __n) ; it--){
            *it = *std::prev(it);
        }
        *std::next(this->begin(), __n) = __ref;
        std::advance(this->end_, 1);

        return std::next(this->begin(), __n);
    }

    template <typename _T, class _Allocator>
    template <class... Args>
    typename vector<_T, _Allocator>::iterator vector<_T, _Allocator>::insert_many(const_iterator __pos, Args&&... args) {
        static_assert((std::is_convertible<Args, _T>::value && ...), "insert_many must be _T");
        ((__pos = insert(__pos, std::forward<Args>(args)), ++__pos),...);
        return std::prev(__pos);
    }

    template <typename _T, class _Allocator>
    template <class... Args>
    void vector<_T,_Allocator>::insert_many_back(Args&&... args){
        static_assert((std::is_convertible<Args, _T>::value && ...), "insert_many_back must be convertible");
        ((push_back(std::forward<Args>(args))),...);
    }


    template<typename _T, class _Allocator>
    void vector<_T, _Allocator>::clear(){
        for(size_type __i = 0; __i < this->size(); __i++){
            alloc_traits::destroy(this->alloc_, this->begin_ + __i);
        }
        this->end_ = this->begin_;
    }

    template<typename _T, class _Allocator>
    void vector<_T, _Allocator>::erase(iterator __pos){
        if(__pos == this->end()){
            throw std::invalid_argument("erase out of range");
        }

        for(iterator it = __pos; it != this->end(); it++){
            *it = std::move(*std::next(it));
        }

        pointer __tail = this->end_;
        std::advance(this->end_, -1);
        alloc_traits::destroy(this->alloc_, __tail);
    }

    template<typename _T, class _Allocator>
    void vector<_T, _Allocator>::push_back(const_reference __ref){
        this->insert(this->end(), __ref);
    }

    template<typename _T, class _Allocator>
    void vector<_T, _Allocator>::swap(vector& __v){
        if(this != &__v){
            std::swap(__v.begin_, this->begin_);
            std::swap(__v.end_, this->end_);
            std::swap(__v.cap_, this->cap_);
        }
    }

    template<typename _T, class _Allocator>
    void vector<_T, _Allocator>::pop_back(){
        if(this->empty()){
            throw std::out_of_range("s21::vector pop_back empty");
        }

        std::advance(this->end_, -1);
    }

    template <typename _T, class _Allocator>
    void vector<_T, _Allocator>::__destroy(){
        if(this->cap_){
            size_type __n = this->size();
            size_type __c = this->capacity();

            for(size_type __i = 0; __i < __n; __i++){
                alloc_traits::destroy(this->alloc_, this->begin_ + __i);
            }
            alloc_traits::deallocate(this->alloc_, this->begin_, __c);

            this->begin_ = nullptr;
            this->end_ = nullptr;
            this->cap_ = nullptr;
        }
    }

    template <typename _T, class _Allocator>
    void vector<_T, _Allocator>::__move(vector<_T, _Allocator> &&__oth){
        if(this != &__oth){

            this->begin_ = std::move(__oth.begin_);
            this->end_ = std::move(__oth.end_);
            this->cap_ = std::move(__oth.cap_);

            __oth.begin_ = nullptr;
            __oth.end_ = nullptr;
            __oth.cap_ = nullptr;
        }
    }

    template <typename _T, class _Allocator>
    template <class _InputIter>
    void vector<_T, _Allocator>::__construct(_InputIter __f, _InputIter __l){
        if(__f != __l){
            size_type __n = std::distance(__f, __l);
            this->begin_ = alloc_traits::allocate(this->alloc_, __n);
            this->end_ = std::next(this->begin_, __n);
            this->cap_ = std::next(this->begin_, __n);

            for(size_type __i = 0; __i < __n; __i++){
                alloc_traits::construct(this->alloc_, this->begin_ + __i, *std::next(__f, __i));
            }
        }
    }
}