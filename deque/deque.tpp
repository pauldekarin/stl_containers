#pragma once

#include "deque.h"

namespace s21{
    template <typename _T, class _Allocator>
    deque<_T, _Allocator>::deque(){
        this->_increase_map();
    }
    
    template <typename _T, class _Allocator>
    deque<_T, _Allocator>::deque(std::initializer_list<value_type> const &__il){
        this->_construct(__il.begin(), __il.end());
    }

    template <typename _T, class _Allocator>
    deque<_T, _Allocator>::deque(const deque &__dq){
        this->_construct(__dq.begin(), __dq.end());
    }

    template <typename _T, class _Allocator>
    deque<_T, _Allocator>::deque(deque &&__dq){
        
        this->_move(std::move(__dq));
    }

    template <typename _T, class _Allocator>
    deque<_T, _Allocator>::~deque(){
        this->_deallocate();
    }

    template <typename _T, class _Allocator>
    deque<_T, _Allocator>& deque<_T, _Allocator>::operator=(deque &&__dq){
        if(this != &__dq){
            this->_deallocate();
            this->_move(std::move(__dq));
        }

        return *this;
    }

    template <typename _T, class _Allocator>
    typename deque<_T, _Allocator>::iterator 
    deque<_T, _Allocator>::begin(){
        return this->head_;
    }

    template <typename _T, class _Allocator>
    typename deque<_T, _Allocator>::iterator 
    deque<_T, _Allocator>::end(){
        return this->tail_;
    }

    template <typename _T, class _Allocator>
    typename deque<_T, _Allocator>::const_iterator 
    deque<_T, _Allocator>::begin() const{
        return const_iterator(this->head_);
    }

    template <typename _T, class _Allocator>
    typename deque<_T, _Allocator>::const_iterator 
    deque<_T, _Allocator>::end() const{
        return const_iterator(this->tail_);
    }

    template <typename _T, class _Allocator>
    typename deque<_T, _Allocator>::reverse_iterator 
    deque<_T, _Allocator>::rbegin(){
        return reverse_iterator(this->tail_);
    }
    template <typename _T, class _Allocator>
    typename deque<_T, _Allocator>::reverse_iterator 
    deque<_T, _Allocator>::rend(){
        return reverse_iterator(this->head_);
    }

    template <typename _T, class _Allocator>
    typename deque<_T, _Allocator>::const_reference 
    deque<_T, _Allocator>::front(){
        return *this->head_;
    }

    template <typename _T, class _Allocator>
    typename deque<_T, _Allocator>::const_reference 
    deque<_T, _Allocator>::back(){
        return *(this->tail_ - 1);
    }

    template <typename _T, class _Allocator>
    bool deque<_T, _Allocator>::empty(){
        return this->begin() == this->end();
    }

    template <typename _T, class _Allocator>
    typename deque<_T, _Allocator>::size_type 
    deque<_T, _Allocator>::size(){
        return this->size_;
    }

    template <typename _T, class _Allocator>
    void 
    deque<_T, _Allocator>::clear(){
        if(this->map_ != nullptr){
            this->head_.map_ = this->map_ + this->__map_size / 2;
            this->tail_.map_ = this->map_ + this->__map_size / 2;
            this->head_._assign(this->__chunk_size / 2);
            this->tail_._assign(this->__chunk_size / 2);
            this->size_ = 0;
        }
    }

    template <typename _T, class _Allocator>
    typename deque<_T, _Allocator>::size_type 
    deque<_T, _Allocator>::capacity(){
        return this->__chunk_size * this->__map_size;
    }

    template <typename _T, class _Allocator>
    void 
    deque<_T, _Allocator>::push_front(const_reference __ref){
        if(!this->_has_avaliable_space()){
            this->_increase_map();
        }
        if(this->size()){
            this->head_--;
        }else{
            this->tail_++;
        }
        this->size_++;
        *this->head_ = __ref;
    }   

    template <typename _T, class _Allocator>
    void 
    deque<_T, _Allocator>::push_back(const_reference __ref){
        if(!this->_has_avaliable_space(false)){
            this->_increase_map(false);
        }
        *this->tail_++ = __ref;
        this->size_++;
    }

    template <typename _T, class _Allocator>
    void 
    deque<_T, _Allocator>::insert(iterator __pos, const_reference __ref){
        if(__pos == this->begin()){
            this->push_front(__ref);
        }else if(__pos == this->end()){
            this->push_back(__ref);
        }else{
            if(!this->_has_avaliable_space(false)){
                typename iterator::difference_type __diff = std::distance(this->begin(), __pos);
                this->_increase_map(false);
                __pos = std::next(this->begin(), __diff);
            }

            for(iterator it = this->end(); it != __pos; it--){
                *it = std::move(*(it - 1));
            }
            *__pos = __ref;
            this->tail_++;
            this->size_++;
        }
    }

    template <typename _T, class _Allocator>
    void 
    deque<_T, _Allocator>::insert(iterator __pos, size_type __n, const_reference __ref){
        typename iterator::difference_type __diff = std::distance(this->begin(), __pos);
        for(size_type __i = 0; __i < __n; __i++){
            this->insert(std::next(this->begin(), __diff), __ref);
        }
    }

    template <typename _T, class _Allocator>
    void 
    deque<_T, _Allocator>::shrink_to_fit(){
        if(this->empty()){
            this->clear();
            this->_deallocate();
            return;
        }

        if(std::distance(this->map_, this->head_.map_)){
            size_type __dist = std::distance(this->map_, this->head_.map_);
            size_type __new_size = this->__map_size - __dist;

            __map_pointer __new_map = __map_traits::allocate(this->map_alloc_, __new_size);

            for(size_type __i = 0; __i < this->__map_size - __dist; __i++){
                __map_traits::construct(this->map_alloc_, __new_map + __i, this->__copy_chunk(this->map_[__i + __dist]));
            }

            this->head_.map_ = __new_map;
            this->tail_.map_ = __new_map + std::distance(this->map_, this->tail_.map_) - __dist;

            this->head_._assign(std::distance(this->head_.begin_, this->head_.current_));
            this->tail_._assign(std::distance(this->tail_.begin_, this->tail_.current_));

            this->_deallocate();

            this->map_ = __new_map;
            this->__map_size = __new_size;
        }

        if(std::distance(this->map_, this->tail_.map_) < static_cast<typename iterator::difference_type>(this->__map_size - 1)){
            size_type __dist = this->__map_size - 1 - std::distance(this->map_, this->tail_.map_);
            size_type __offset = std::distance(this->map_, this->head_.map_);

            size_type __new_size = this->__map_size - __dist + __offset;
            __map_pointer __new_map = __map_traits::allocate(this->map_alloc_, __new_size);

            for(size_type __i = 0; __i < __new_size; __i++){
                __map_traits::construct(this->map_alloc_, __new_map + __i, this->__copy_chunk(this->map_[__i + __offset]));
            }
            this->head_.map_ = __new_map;
            this->tail_.map_ = __new_map + __new_size - 1;

            this->head_._assign(std::distance(this->head_.begin_, this->head_.current_));
            this->tail_._assign(std::distance(this->tail_.begin_, this->tail_.current_));

            this->_deallocate();

            this->map_ = __new_map;
            this->__map_size = __new_size;
        }
    }

    template <typename _T, class _Allocator>
    template <class _InputIter, typename>
    void 
    deque<_T, _Allocator>::insert(iterator __pos, _InputIter __f, _InputIter __l){
        typename iterator::difference_type __diff = std::distance(this->begin(), __pos);
        for(typename iterator::difference_type __i = __diff; __f != __l; __f++, __i++){
            this->insert(std::next(this->begin(), __i), *__f);
        }
    }

    template <typename _T, class _Allocator>
    void 
    deque<_T, _Allocator>::pop_back(){
        this->tail_--;
        this->size_--;
    }

    template <typename _T, class _Allocator>
    void 
    deque<_T, _Allocator>::pop_front(){
        this->head_++;
        this->size_--;
    }
    template <typename _T, class _Allocator>
    void 
    deque<_T, _Allocator>::erase(iterator __pos){
        if(__pos == this->begin()){
            this->pop_front();
        }else if(__pos == this->end()){
            this->pop_back();
        }else{
            for(iterator it = __pos; it != this->end(); it++){
                *it = std::move(*(it + 1));
            }
            this->tail_--;
            this->size_--;
        }
    }

    template <typename _T, class _Allocator>
    void 
    deque<_T, _Allocator>::_move(deque &&__dq){
        this->map_ = __dq.map_;
        this->head_ = __dq.head_;
        this->tail_ = __dq.tail_;
        this->__map_size = __dq.__map_size;
        this->__chunk_size = __dq.__chunk_size;
        this->size_ = __dq.size_;

        __dq.map_ = nullptr;
        __dq.size_ = 0;
        __dq.__map_size = 0;
    }

    template <typename _T, class _Allocator>
    template <class _InputIter>
    void 
    deque<_T, _Allocator>::_construct(_InputIter __b, _InputIter __e){
        while(__b != __e){
            this->push_back(*__b++);
        }
    }

    template <typename _T, class _Allocator>
    bool 
    deque<_T, _Allocator>::_has_avaliable_space(bool in_front){
        if(this->map_ == nullptr) return false;

        if(in_front){
            if(std::distance(this->map_, this->head_.map_) == 0 && this->head_.current_ == this->head_.begin_){
                return false;
            }
        }else{
            if(std::distance(this->map_, this->tail_.map_) == static_cast<typename iterator::difference_type>(this->__map_size) - 1 && this->tail_.current_ == this->tail_.end_){
                return false;
            }
        }   

        return true;
    }

    template <typename _T, class _Allocator>
    void 
    deque<_T, _Allocator>::_increase_map(bool in_front, size_type __n){
        __map_pointer __new_map = __map_traits::allocate(this->map_alloc_, this->__map_size + __n);
        if(in_front){
            for(size_type __i = 0; __i < __n; __i++){
                __new_map[__i] = this->__create_chunk();
            }
            for(size_type __i = 0; __i < this->__map_size; __i++){
                __map_traits::construct(this->map_alloc_, __new_map + __n + __i, this->__copy_chunk(this->map_[__i]));
            }

            if(this->map_ != nullptr){
                this->head_.map_ = __new_map + __n + std::distance(this->map_, this->head_.map_);
                this->tail_.map_ = __new_map + __n + std::distance(this->map_, this->tail_.map_);
            }else{
                this->head_.map_ = __new_map + __n / 2;
                this->tail_.map_ = __new_map + __n / 2;
            }
        }else{
            for(size_type __i = 0; __i < this->__map_size; __i++){
                __map_traits::construct(this->map_alloc_, __new_map + __i, this->__copy_chunk(this->map_[__i]));
            }
            for(size_type __i = this->__map_size; __i < this->__map_size + __n; __i++){
                __new_map[__i] = this->__create_chunk();
            }

            if(this->map_ != nullptr){
                this->head_.map_ = __new_map +  std::distance(this->map_, this->head_.map_);
                this->tail_.map_ = __new_map +  std::distance(this->map_, this->tail_.map_);
            }else{
                this->head_.map_ = __new_map + __n / 2;
                this->tail_.map_ = __new_map + __n / 2;
            }
        }

        if(this->map_ != nullptr){
            this->head_._assign(std::distance(this->head_.begin_, this->head_.current_));
            this->tail_._assign(std::distance(this->tail_.begin_, this->tail_.current_));
        }else{
            this->head_._assign(this->__chunk_size / 2);
            this->tail_._assign(this->__chunk_size / 2);
        }

        __n += this->__map_size;
        this->_deallocate();
        this->map_ = __new_map;
        this->__map_size = __n;
    }

    template <typename _T, class _Allocator>
    typename deque<_T, _Allocator>::pointer  
    deque<_T, _Allocator>::__create_chunk(){
        pointer __chunk = __value_traits::allocate(this->val_alloc_, this->__chunk_size);
        for(size_type __i = 0; __i < this->__chunk_size; __i++){
            __value_traits::construct(this->val_alloc_, __chunk + __i, value_type());
        }
        return __chunk;
    }

    template <typename _T, class _Allocator>
    typename deque<_T, _Allocator>::pointer 
    deque<_T, _Allocator>::__copy_chunk(pointer __src){
        pointer __dst = this->__create_chunk();
        for(size_type __i = 0; __i < this->__chunk_size; __i++){
            __dst[__i] = __src[__i];
        }
        return __dst;
    }

    template <typename _T, class _Allocator>
    void 
    deque<_T, _Allocator>::__clear_chunk(pointer __chunk){
        for(size_type __i = 0; __i < this->__chunk_size; __i++){
            __value_traits::destroy(this->val_alloc_, __chunk + __i);
        }
        __value_traits::deallocate(this->val_alloc_, __chunk, this->__chunk_size);
    }

    template <typename _T, class _Allocator>
    void 
    deque<_T, _Allocator>::_deallocate(){
        if(this->map_ != nullptr){
            for(size_type __i = 0; __i < this->__map_size; __i++){
                this->__clear_chunk(this->map_[__i]);
                __map_traits::destroy(this->map_alloc_, this->map_ + __i);
            }
            __map_traits::deallocate(this->map_alloc_, this->map_, this->__map_size);
            this->map_ = nullptr;
            this->__map_size = 0;
        }
    }
};