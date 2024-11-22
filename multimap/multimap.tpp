#pragma once
#include "multimap.h"

namespace s21{
    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    multimap<_Key, _Value, _Compare, _Allocator>::multimap(){

    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    multimap<_Key, _Value, _Compare, _Allocator>::multimap(std::initializer_list<std::pair<const key_type, value_type>> const& __il){
        for( 
            typename std::initializer_list<std::pair<const key_type, value_type>>::const_iterator it =  __il.begin();
            it != __il.end();
            it++
        ){
            this->tree_.insert(*it);
        }
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    multimap<_Key, _Value, _Compare, _Allocator>::multimap(const multimap& __oth):tree_(__oth.tree_){
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    multimap<_Key, _Value, _Compare, _Allocator>::multimap(multimap&& __oth){
        this->tree_ = std::move(__oth.tree);
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    multimap<_Key, _Value, _Compare, _Allocator>::~multimap(){
        this->tree_.clear();
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    multimap<_Key, _Value, _Compare, _Allocator>& 
    multimap<_Key, _Value, _Compare, _Allocator>::operator=(multimap&& __oth){
        if(this != &__oth){
            this->tree_ = std::move(__oth.tree_);
        }
        return *this;
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    typename multimap<_Key, _Value, _Compare, _Allocator>::reference 
    multimap<_Key, _Value, _Compare, _Allocator>::at(const key_type& __key){
        iterator __it = this->tree_.find(__key);

        if(__it == this->tree_.end()){
            throw std::invalid_argument("at invalid key");
        }

        return __it->second;
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    typename multimap<_Key, _Value, _Compare, _Allocator>::iterator 
    multimap<_Key, _Value, _Compare, _Allocator>::begin(){
        return this->tree_.begin();
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    typename multimap<_Key, _Value, _Compare, _Allocator>::iterator 
    multimap<_Key, _Value, _Compare, _Allocator>::end(){
        return this->tree_.end();
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    typename multimap<_Key, _Value, _Compare, _Allocator>::const_iterator
    multimap<_Key, _Value, _Compare, _Allocator>::begin() const{
        return this->tree_.begin();
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    typename multimap<_Key, _Value, _Compare, _Allocator>::const_iterator
    multimap<_Key, _Value, _Compare, _Allocator>::end() const{
        return this->tree_.end();
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    bool 
    multimap<_Key, _Value, _Compare, _Allocator>::empty() const{
        return this->size() == 0;
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    typename multimap<_Key, _Value, _Compare, _Allocator>::size_type 
    multimap<_Key, _Value, _Compare, _Allocator>::size() const{
        return static_cast<size_type>(this->tree_.size());
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    typename multimap<_Key, _Value, _Compare, _Allocator>::size_type 
    multimap<_Key, _Value, _Compare, _Allocator>::max_size() const{
        return this->tree_->max_size();
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    void 
    multimap<_Key, _Value, _Compare, _Allocator>::clear(){
        this->tree_.clear();
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    std::pair<typename multimap<_Key, _Value, _Compare, _Allocator>::iterator, bool> 
    multimap<_Key, _Value, _Compare, _Allocator>::insert(const_reference __ref){
        if(this->tree_.find(__ref) == this->tree_.end()){
            return {this->tree_.insert(__ref), true};
        }else{
            return {this->end(), false};
        }
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    std::pair<typename multimap<_Key, _Value, _Compare, _Allocator>::iterator, bool> 
    multimap<_Key, _Value, _Compare, _Allocator>::insert(const key_type& __key, const mapped_type& __val){
        return this->insert({__key, __val});
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    void 
    multimap<_Key, _Value, _Compare, _Allocator>::erase(iterator __pos){
        if(this->empty()){
            throw std::out_of_range("s21::multimap erase empty");
        }
        
        if(__pos == this->end()){
            throw std::invalid_argument("s21::multimap invalid erase iterator");
        }

        this->tree_.erase(__pos);
    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    void 
    multimap<_Key, _Value, _Compare, _Allocator>::swap(multimap& __oth){

    }

    template <typename _Key, typename _Value, class _Compare, class _Allocator>
    void 
    multimap<_Key, _Value, _Compare, _Allocator>::merge(multimap& __oth){
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
    multimap<_Key, _Value, _Compare, _Allocator>::contains(const key_type  &__key) const{
        return this->tree_.find(__key) != this->tree_.end();
    }

}