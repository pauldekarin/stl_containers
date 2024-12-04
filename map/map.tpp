#pragma once
#include "map.h"

namespace s21{
    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    map<_Key, _Value, _Compare, _Allocator>::map(){

    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    map<_Key, _Value, _Compare, _Allocator>::map(std::initializer_list<std::pair<const key_type, mapped_type>> const& __il){
        for( 
            typename std::initializer_list<std::pair<const key_type, mapped_type>>::const_iterator it =  __il.begin();
            it != __il.end();
            it++
        ){
            this->tree_.insert(*it);
        }
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    map<_Key, _Value, _Compare, _Allocator>::map(const map& __oth):tree_(__oth.tree_){
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    map<_Key, _Value, _Compare, _Allocator>::map(map&& __oth){
        this->tree_ = std::move(__oth.tree);
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    map<_Key, _Value, _Compare, _Allocator>::~map(){
        this->tree_.clear();
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    map<_Key, _Value, _Compare, _Allocator>& 
    map<_Key, _Value, _Compare, _Allocator>::operator=(map&& __oth){
        if(this != &__oth){
            this->tree_ = std::move(__oth.tree_);
        }
        return *this;
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    typename map<_Key, _Value, _Compare, _Allocator>::reference 
    map<_Key, _Value, _Compare, _Allocator>::at(const key_type& __key){
        iterator __it = this->tree_.find({__key, mapped_type()});

        if(__it == this->tree_.end()){
            throw std::invalid_argument("at invalid key");
        }

        return __it->second;
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    typename map<_Key, _Value, _Compare, _Allocator>::reference 
    map<_Key, _Value, _Compare, _Allocator>::operator[](const key_type& __key){
        iterator __it = this->tree_.find({__key, mapped_type()});

        if(__it == this->tree_.end()){
            this->tree_.insert({__key, mapped_type()});
        }

        return __it->second;
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    typename map<_Key, _Value, _Compare, _Allocator>::iterator 
    map<_Key, _Value, _Compare, _Allocator>::begin(){
        return this->tree_.begin();
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    typename map<_Key, _Value, _Compare, _Allocator>::iterator 
    map<_Key, _Value, _Compare, _Allocator>::end(){
        return this->tree_.end();
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    typename map<_Key, _Value, _Compare, _Allocator>::const_iterator
    map<_Key, _Value, _Compare, _Allocator>::begin() const{
        return this->tree_.begin();
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    typename map<_Key, _Value, _Compare, _Allocator>::const_iterator
    map<_Key, _Value, _Compare, _Allocator>::end() const{
        return this->tree_.end();
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    bool 
    map<_Key, _Value, _Compare, _Allocator>::empty() const{
        return this->size() == 0;
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    typename map<_Key, _Value, _Compare, _Allocator>::size_type 
    map<_Key, _Value, _Compare, _Allocator>::size() const{
        return static_cast<size_type>(this->tree_.size());
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    typename map<_Key, _Value, _Compare, _Allocator>::size_type 
    map<_Key, _Value, _Compare, _Allocator>::max_size() const{
        return this->tree_->max_size();
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    void 
    map<_Key, _Value, _Compare, _Allocator>::clear(){
        this->tree_.clear();
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    std::pair<typename map<_Key, _Value, _Compare, _Allocator>::iterator, bool> 
    map<_Key, _Value, _Compare, _Allocator>::insert(const_reference __ref){
        if(this->tree_.find(__ref) == this->tree_.end()){
            return {this->tree_.insert(__ref), true};
        }else{
            return {this->tree_.end(), false};
        }
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    std::pair<typename map<_Key, _Value, _Compare, _Allocator>::iterator, bool> 
    map<_Key, _Value, _Compare, _Allocator>::insert(const key_type& __key, const mapped_type& __val){
        return this->insert({__key, __val});
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    std::pair<typename map<_Key, _Value, _Compare, _Allocator>::iterator, bool> 
    map<_Key, _Value, _Compare, _Allocator>::insert_or_assign(const key_type& __key, const mapped_type& __val){
        reference __ref(__key, __val);
        iterator __it = this->tree_.find(__ref);

        if(__it == this->tree_.end()){
            __it = this->tree_.insert(__ref);
        }else{
            __it->second = __val;
        }

        return {__it, true};
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    template <class... Args>
    std::pair<typename map<_Key, _Value, _Compare, _Allocator>::iterator, bool>
    map<_Key, _Value, _Compare, _Allocator>::insert_many(Args&&... args){
        static_assert((std::is_constructible<value_type, Args&&>::value && ...), "map insert_many must be convertible std::pair<key_type, value_type>");
        std::pair<iterator, bool> __res = {end(), false};
        ((__res = insert(std::forward<Args>(args))), ...);
        return __res;
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    void 
    map<_Key, _Value, _Compare, _Allocator>::erase(iterator __pos){
        if(this->empty()){
            throw std::out_of_range("s21::map erase empty");
        }
        
        if(__pos == this->end()){
            throw std::invalid_argument("s21::map invalid erase iterator");
        }

        this->tree_.erase(__pos);
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    void 
    map<_Key, _Value, _Compare, _Allocator>::swap(map& __oth){

    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    void 
    map<_Key, _Value, _Compare, _Allocator>::merge(map& __oth){
        for(iterator __it = __oth.begin(); __it != __oth.end(); __it++){
            std::pair<iterator, bool> __res = this->insert(*__it);

            if(__res.first != this->end()){
                __oth.erase(__it);
                __it = __oth.begin();
            }
        }
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    bool 
    map<_Key, _Value, _Compare, _Allocator>::contains(const key_type  &__key){
        return this->tree_.find(__key) != this->tree_.end();
    }
}