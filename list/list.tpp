#pragma once
#include "list.h"

namespace s21{
    template <typename _T, class _Allocator>    
    list<_T, _Allocator>::list(){
        this->_init_sentinel();
    }
    template <typename _T, class _Allocator>
    list<_T, _Allocator>::list(size_type __n){
        this->_init_sentinel();
        for(size_type _i = 0; _i < __n; _i++){
            this->insert(this->begin(), _T());
        }
    }
    template <typename _T, class _Allocator>
    list<_T, _Allocator>::list(const std::initializer_list<_T> &__il)
    {
        this->_init_sentinel();
        for(typename std::initializer_list<_T>::iterator it = __il.begin(); it != __il.end(); it++){
            this->insert(this->end(), *it);
        }
    }
    template <typename _T, class _Allocator>
    list<_T, _Allocator>::list(const list &__l){
        this->_init_sentinel();
        for(iterator it = __l.begin(); it != __l.end(); it++){
            this->insert(this->end(), *it);
        }
    }
    template <typename _T, class _Allocator>
    list<_T, _Allocator>::list(list &&__l){
        this->_init_sentinel();

        this->root_ = __l.root_;
        this->sentinel_->foot_ = __l.sentinel_->foot_;
        this->sentinel_->head_ = __l.sentinel_->head_;
        this->sentinel_->value_ = __l.sentinel_->value_;
        this->size_ = __l.size_;
        if(this->sentinel_->foot_ != nullptr) this->sentinel_->foot_->head_ = this->sentinel_;

        __l.root_ = nullptr;
        __l.sentinel_->head_ = nullptr;
        __l.sentinel_->foot_ = nullptr;
        __l.sentinel_->value_  = 0;
        __l.size_ = 0;
    }
    template <typename _T, class _Allocator>
    list<_T, _Allocator>::~list(){
        this->clear();
        this->_clear_sentinel();
    }

    template <typename _T, class _Allocator>    
    typename list<_T, _Allocator>::const_reference
    list<_T, _Allocator>::front(){
        if(this->empty()){
            throw std::out_of_range("list is empty");
        }else{
            return this->begin().get()->value_;
        }
    }

    template <typename _T, class _Allocator>
    typename list<_T, _Allocator>::const_reference list<_T, _Allocator>::back(){
        if(this->empty()){
            throw std::out_of_range("list is empty");
        }else{
            return std::prev(this->end()).get()->value_;
        }
    }


    template <typename _T, class _Allocator>    //List Capacity
    typename list<_T, _Allocator>::size_type 
    list<_T, _Allocator>::size() const noexcept{
        return this->size_;
    }

    template <typename _T, class _Allocator>    
    typename list<_T, _Allocator>::size_type 
    list<_T, _Allocator>::max_size() const{
        return std::allocator_traits<alloc_type>::max_size(this->alloc_);
    }

    template <typename _T, class _Allocator>
    inline bool 
    list<_T, _Allocator>::empty() const{
        return this->size() == 0;
    }

    //List Modifiers
    template <typename _T, class _Allocator>
    typename list<_T, _Allocator>::iterator 
    list<_T, _Allocator>::insert(iterator __pos, const_reference __value){
        node_pointer __n = alloc_traits::allocate(this->alloc_,1);
        alloc_traits::construct(this->alloc_, __n, __value);

        if(this->root_ == nullptr){
            this->root_ = __n;
            __n->head_ = this->sentinel_;
            __n->foot_ = nullptr;
            this->sentinel_->foot_ = this->root_;
        }else if(__pos == this->end()){
            __n->head_ = this->sentinel_;
            __n->foot_ = this->sentinel_->foot_;
            if(this->sentinel_->foot_ != nullptr) this->sentinel_->foot_->head_ = __n;
            this->sentinel_->foot_ = __n;
        }else{
            __n->head_ = __pos.get();
            __n->foot_ = __pos.get()->foot_;

            if(__pos.get()->foot_ != nullptr) __pos.get()->foot_->head_ = __n;
            __pos.get()->foot_ = __n;

            if(__pos == this->begin()) this->root_ = __n;
            else if(__pos.get()->head_ == this->sentinel_) this->sentinel_->foot_ = __n;
        }

        this->sentinel_->value_ = ++this->size_;

        return iterator(__n);
    }

    template <typename _T, class _Allocator>
    template <class... Args>
    typename list<_T, _Allocator>::iterator list<_T, _Allocator>::insert_many(const_iterator __pos, Args&&... args){
        static_assert((std::is_convertible<Args, _T>::value && ...), "insert_many arguments must be _T");
        ((__pos = insert(__pos, std::forward<Args>(args)), ++__pos), ...);
        return std::prev(__pos);
    }

    template <typename _T, class _Allocator>
    template <class... Args>
    void list<_T, _Allocator>::insert_many_back(Args&&... args){
        static_assert((std::is_convertible<Args, _T>::value && ...), "insert_many_back must be convertible");
        ((push_back(std::forward<Args>(args))), ...);
    }

    template <typename _T, class _Allocator>
    template <class... Args>
    void list<_T, _Allocator>::insert_many_front(Args&&... args){
        static_assert((std::is_convertible<Args, _T>::value && ...), "list insert_many_front must be convertible");
        iterator it = begin();
        ((it = insert(it, std::forward<Args>(args)), ++it), ...);
    }

    template <typename _T, class _Allocator>    
    void 
    list<_T, _Allocator>::clear(){
        while(this->begin() != this->end()){
            this->erase(this->begin());
        }
        this->root_ = nullptr;
        this->size_ = 0;
        
        this->sentinel_->head_ = nullptr;
        this->sentinel_->foot_ = nullptr;
        this->sentinel_->value_ = 0;
        
    }

    template <typename _T, class _Allocator>
    void 
    list<_T, _Allocator>::erase(iterator __pos){
        if(__pos == this->end()){
            throw std::invalid_argument("can't erase end-iterator");
        }
        if(__pos.get() != nullptr){
            node_pointer __n = __pos.get();
            if(__n->head_ != nullptr) __n->head_->foot_ = __n->foot_;
            if(__n->foot_ != nullptr) __n->foot_->head_ = __n->head_;
            if(__n == this->root_) this->root_ = __n->head_;
            this->_clear_node(__n);
            this->sentinel_->value_ = --this->size_;
        }
    }

    template <typename _T, class _Allocator>    
    void list<_T, _Allocator>::push_back(const_reference __ref){
        this->insert(this->end(), __ref);
    }

    template <typename _T, class _Allocator>
    void 
    list<_T, _Allocator>::pop_back(){
        if(this->sentinel_->foot_ == nullptr){
            throw std::out_of_range("can't pop_back() empty list");
        }
        this->erase(iterator(this->sentinel_->foot_));
    }
    
    template <typename _T, class _Allocator>
    void 
    list<_T, _Allocator>::push_front(const_reference __ref){
        this->insert(this->begin(), __ref);
    }

    template <typename _T, class _Allocator>
    void 
    list<_T, _Allocator>::swap(list &__oth){
        if(this != &__oth){
            node_pointer __tmp_root = this->root_;
            node_pointer __tmp_sentinel = this->sentinel_;
            size_type __tmp_size = this->size_;

            this->root_ = __oth.root_;
            this->sentinel_ = __oth.sentinel_;
            this->size_ = __oth.size_;

            __oth.root_ = __tmp_root;
            __oth.sentinel_ = __tmp_sentinel;
            __oth.size_ = __tmp_size;
            
        }
    }
    template <typename _T, class _Allocator>
    template <class _Compare>
    void 
    list<_T, _Allocator>::merge(list &__oth, _Compare comp){
        list __merged(this->size_ + __oth.size_);

        iterator _lhs_it = this->begin();
        iterator _merged_it = __merged.begin();
        iterator _oth_it = __oth.begin();

        while(_merged_it != __merged.end()){
            if(_lhs_it == this->end()){
                *_merged_it = *_oth_it;
                _oth_it++;
            }else if(_oth_it == __oth.end()){
                *_merged_it = *_lhs_it;
                _lhs_it++;
            }else if(comp(*_lhs_it, *_oth_it)){
                *_merged_it = *_lhs_it;
                _lhs_it++;
            }else{
                *_merged_it = *_oth_it;
                _oth_it++;
            }
            _merged_it++;
        }

        this->clear();
        __oth.clear();
        this->swap(__merged);
    }

    template <typename _T, class _Allocator>
    void 
    list<_T, _Allocator>::splice(const_iterator __pos, list &__oth){
        if(this == &__oth){
            throw std::invalid_argument("can't splice same object");
        }
        if(__oth.size() == 0) return;

        this->size_ += __oth.size_;

        node_pointer pos_node = reinterpret_cast<node_pointer>(__pos.get());
        node_pointer oth_tail = __oth.sentinel_->foot_;
        node_pointer oth_root = __oth.root_;

        __oth.size_ = 0;
        __oth.root_ = nullptr;
        __oth.sentinel_->foot_ = nullptr;

        if(__pos == this->begin()){ 
            oth_tail->head_ = this->root_;
            if(this->root_ != nullptr) this->root_->foot_ = oth_tail;
            this->root_ = oth_root;
        }else if(__pos == this->end()){
            if (this->sentinel_->foot_) this->sentinel_->foot_->head_ = oth_root;
            oth_root->foot_ = this->sentinel_->foot_;
            this->sentinel_->foot_ = oth_tail;
            oth_tail->head_ = this->sentinel_;
        }else{
            oth_tail->head_ = pos_node;
            oth_root->foot_ = pos_node->foot_;
            if (pos_node->foot_) pos_node->foot_->head_ = oth_root;
            pos_node->foot_ = oth_tail;
        }
        this->sentinel_->value_ = this->size_;
    }     

    template <typename _T, class _Allocator>
    void 
    list<_T, _Allocator>::reverse(){
        if(this->size() > 1){
            iterator __e = this->end();
            iterator __b = this->begin();

            node_pointer __tail = __b.get();

            for(; __b != __e;){
                std::swap(__b.get()->foot_, __b.get()->head_);
                __b--;
            }

            std::swap(__e.get()->foot_, __e.get()->head_);

            this->root_ = __e.get()->head_;
            this->root_->foot_ = nullptr;

            this->sentinel_->foot_ = __tail;
            this->sentinel_->head_ = nullptr;

            __tail->head_ = this->sentinel_;
        }
    }

    template <typename _T, class _Allocator>
    void 
    list<_T, _Allocator>::unique(){
        if(this->size() > 1){
            for(iterator __b = this->begin(); __b != this->end(); __b++){
                while(__b.get()->head_ != this->sentinel_ && __b.get()->head_->value_ == __b.get()->value_){
                    node_pointer __next = __b.get()->head_;
                    __b.get()->head_ = __next->head_;
                    if(__next->head_) __next->head_->foot_ = __b.get();
                    _clear_node(__next);
                    this->sentinel_->value_ = --this->size_;
                }
            }
        }
    }

    template <typename _T, class _Allocator>
    template <typename _Compare>
    void list<_T, _Allocator>::sort(){
        this->_sort(this->begin(), this->end());
    }

    template <typename _T, class _Allocator>
    typename list<_T, _Allocator>::iterator 
    list<_T, _Allocator>::begin() {
        return this->size() == 0 ? this->end() : iterator(this->root_);
    }

    template <typename _T, class _Allocator>
    typename list<_T, _Allocator>::iterator 
    list<_T, _Allocator>::end() {
        return iterator(this->sentinel_);
    }

    template <typename _T, class _Allocator>
    typename list<_T, _Allocator>::const_iterator 
    list<_T, _Allocator>::begin() const{
        return this->size() == 0 ? this->end() : const_iterator(iterator(this->root_));
    }

    template <typename _T, class _Allocator>
    typename list<_T, _Allocator>::const_iterator 
    list<_T, _Allocator>::end() const{
        return const_iterator(iterator(this->sentinel_));
    }

    template <typename _T, class _Allocator>
    list<_T, _Allocator>& 
    list<_T, _Allocator>::operator=(const list &__oth){
        if(this != &__oth){
            this->clear();
            for(iterator it = __oth.begin(); it != __oth.end(); it++){
                this->insert(this->end(), *it);
            }
        }
        return *this;
    }

    template <typename _T, class _Allocator>
    list<_T, _Allocator>& 
    list<_T, _Allocator>::operator=(list &&__oth){
        if(this != &__oth){
            this->clear();
            
            this->root_ = __oth.root_;
            this->sentinel_->foot_ = __oth.sentinel_->foot_;
            this->sentinel_->head_ = __oth.sentinel_->head_;
            this->sentinel_->value_ = __oth.sentinel_->value_;
            if(this->sentinel_->foot_ != nullptr) this->sentinel_->foot_->head_ = this->sentinel_;
            this->size_ = __oth.size_;

            __oth.root_ = nullptr;
            __oth.sentinel_->head_ = nullptr;
            __oth.sentinel_->foot_ = nullptr;
            __oth.sentinel_->value_  = 0;
            __oth.size_ = 0;
        }
        return *this;
    }
    template <typename _T, class _Allocator>
    template <typename _Compare>
    void 
    list<_T, _Allocator>::_sort(iterator __begin, iterator __end, _Compare comp) {
        for(iterator _it = __begin; _it != std::prev(__end); _it++){
            for(iterator _jt = __begin; _jt != std::prev(__end); _jt++){
                if(!comp(*_jt, *std::next(_jt))){
                    std::swap(_jt.get()->value_, std::next(_jt).get()->value_);
                }
            }
        }   
    }

    template <typename _T, class _Allocator>
    void 
    list<_T, _Allocator>::_clear_node(node_pointer __n){
        if(__n != nullptr){
            alloc_traits::destroy(this->alloc_, __n);
            alloc_traits::deallocate(this->alloc_, __n, 1);
        }
    }   
    
    template <typename _T, class _Allocator>
    void 
    list<_T, _Allocator>::_init_sentinel(){
        this->sentinel_ = alloc_traits::allocate(this->alloc_, 1);
        alloc_traits::construct(this->alloc_, this->sentinel_, 0);
        this->sentinel_->head_ = nullptr;
        this->sentinel_->foot_ = nullptr;
        this->sentinel_->is_sentinel_ = true;
    }

    template <typename _T, class _Allocator>
    void 
    list<_T, _Allocator>::_clear_sentinel(){
        if(this->sentinel_ != nullptr){
            this->_clear_node(this->sentinel_);
            this->sentinel_ = nullptr;
        }
    }
};