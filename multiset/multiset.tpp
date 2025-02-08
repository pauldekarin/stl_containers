#pragma once
#include "multiset.h"

namespace s21{
    template <typename _T, class _Compare, class _Allocator>
    multiset<_T, _Compare, _Allocator>::multiset(){

    }	
    
    template <typename _T, class _Compare, class _Allocator>
    multiset<_T, _Compare, _Allocator>::multiset(std::initializer_list<value_type> const &__il){
        this->tree_._construct(__il.begin(), __il.end());
    }	
    
    template <typename _T, class _Compare, class _Allocator>
    multiset<_T, _Compare, _Allocator>::multiset(const multiset &s){
        this->tree_._copy(s.tree_);
    }
    
    template <typename _T, class _Compare, class _Allocator>
    multiset<_T, _Compare, _Allocator>::multiset(multiset &&s){
        this->tree_._copy(s.tree_);
        s.tree_.clear();
    }
    
    template <typename _T, class _Compare, class _Allocator>
    multiset<_T, _Compare, _Allocator>::~multiset(){
        this->tree_.clear();
    }	
    
    template <typename _T, class _Compare, class _Allocator>
    multiset<_T, _Compare, _Allocator>& 
    multiset<_T, _Compare, _Allocator>::operator=(multiset &&s){
        if(this != &s){
            this->tree_ = std::move(s.tree_);
        }
        return *this;
    }	
    
    template <typename _T, class _Compare, class _Allocator>
    typename multiset<_T, _Compare, _Allocator>::iterator 
    multiset<_T, _Compare, _Allocator>::begin(){
        return this->tree_.begin();                
    }	
    
    template <typename _T, class _Compare, class _Allocator>
    typename multiset<_T, _Compare, _Allocator>::iterator 
    multiset<_T, _Compare, _Allocator>::end(){
        return this->tree_.end();
    }	

    template <typename _T, class _Compare, class _Allocator>
    typename multiset<_T, _Compare, _Allocator>::reverse_iterator 
    multiset<_T, _Compare, _Allocator>::rbegin(){
        return reverse_iterator(this->tree_.end());
    }

    template <typename _T, class _Compare, class _Allocator>
    typename multiset<_T, _Compare, _Allocator>::reverse_iterator 
    multiset<_T, _Compare, _Allocator>::rend(){
        return reverse_iterator(this->tree_.begin());
    }
    
    template <typename _T, class _Compare, class _Allocator>
    bool 
    multiset<_T, _Compare, _Allocator>::empty(){
        return this->tree_.size() == 0;
    }
    
    template <typename _T, class _Compare, class _Allocator>
    typename multiset<_T, _Compare, _Allocator>::size_type 
    multiset<_T, _Compare, _Allocator>::size(){
        return this->tree_.size();
    }
    
    template <typename _T, class _Compare, class _Allocator>
    typename multiset<_T, _Compare, _Allocator>::size_type 
    multiset<_T, _Compare, _Allocator>::max_size(){
        return this->tree_.max_size();
    }	
    
    template <typename _T, class _Compare, class _Allocator>
    void 
    multiset<_T, _Compare, _Allocator>::clear(){
        this->tree_.clear();
    }
    
    template <typename _T, class _Compare, class _Allocator>
    std::pair<typename multiset<_T, _Compare, _Allocator>::iterator, bool> 
    multiset<_T, _Compare, _Allocator>::insert(const_reference __ref){
        return {this->tree_.insert(__ref), true};
    }
    
    template <typename _T, class _Compare, class _Allocator>
    template <class... Args>
    std::pair<typename multiset<_T, _Compare, _Allocator>::iterator, bool>
    multiset<_T, _Compare, _Allocator>::insert_many(Args&&... args){
        static_assert((std::is_convertible<Args, _T>::value && ...), "multiset insert_many must be convertible to value_type");
        std::pair<iterator, bool> __res = {end(), false};
        ((__res = insert(std::forward<Args>(args))), ...);
        return __res;
    }

    template <typename _T, class _Compare, class _Allocator>
    void 
    multiset<_T, _Compare, _Allocator>::erase(iterator __pos){
        if(this->empty()){
            throw std::out_of_range("s21::multiset erase empty");
        }
        this->tree_.erase(__pos);
    }

    template <typename _T, class _Compare, class _Allocator>
    void 
    multiset<_T, _Compare, _Allocator>::erase(iterator __f, iterator __l){
        if(this->empty()){
            throw std::out_of_range("s21:: multiset erase empty");
        }

        while(__f != __l){
            this->tree_.erase(__f++);
        }
    }
    template <typename _T, class _Compare, class _Allocator>
    void 
    multiset<_T, _Compare, _Allocator>::erase(const_reference __ref){
        iterator __it = this->tree_.find(__ref);
        while(__it != this->tree_.end()){
            this->tree_.erase(__it);
            __it = this->tree_.find(__ref);
        }
    }
    
    template <typename _T, class _Compare, class _Allocator>
    void 
    multiset<_T, _Compare, _Allocator>::swap(multiset& __oth){
        if(this != &__oth){
            this->tree_.swap(__oth.tree_);
        }
    }
    
    template <typename _T, class _Compare, class _Allocator>
    void 
    multiset<_T, _Compare, _Allocator>::merge(multiset& __oth){
        if(this != &__oth){
            for(
                iterator __it = __oth.begin();
                __it != __oth.end();
                __it++
            ){
                this->tree_.insert(*__it);
            }
            __oth.clear();
        }
    }
    
    template <typename _T, class _Compare, class _Allocator>
    typename multiset<_T, _Compare, _Allocator>::iterator 
    multiset<_T, _Compare, _Allocator>::find(const_reference __ref){
        return this->tree_.find(__ref);
    }

    template <typename _T, class _Compare, class _Allocator>
    typename multiset<_T, _Compare, _Allocator>::iterator 
    multiset<_T, _Compare, _Allocator>::lower_bound(const_reference __ref){
        return this->tree_.lower_bound(__ref);
    }
    
    template <typename _T, class _Compare, class _Allocator>
    typename multiset<_T, _Compare, _Allocator>::iterator 
    multiset<_T, _Compare, _Allocator>::upper_bound(const_reference __ref){
        return this->tree_.upper_bound(__ref);
    }
    
    template <typename _T, class _Compare, class _Allocator>
    typename multiset<_T, _Compare, _Allocator>::size_type 
    multiset<_T, _Compare, _Allocator>::count(const_reference __ref){
        return this->tree_.count(__ref);
    }
    
    template <typename _T, class _Compare, class _Allocator>
    bool 
    multiset<_T, _Compare, _Allocator>::contains(const_reference __ref){
        return this->tree_.find(__ref) != this->tree_.end();
    }
}