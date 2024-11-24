#pragma once
#include "set.h"

namespace s21{
    template <typename _T, class _Compare, class _Allocator>
    set<_T, _Compare, _Allocator>::set(){

    }	
    
    template <typename _T, class _Compare, class _Allocator>
    set<_T, _Compare, _Allocator>::set(std::initializer_list<value_type> const &__il){
        this->tree_._construct(__il.begin(), __il.end());
    }	
    
    template <typename _T, class _Compare, class _Allocator>
    set<_T, _Compare, _Allocator>::set(const set &s){
        this->tree_._copy(s.tree_);
    }
    
    template <typename _T, class _Compare, class _Allocator>
    set<_T, _Compare, _Allocator>::set(set &&s){
        this->tree_._copy(s.tree_);
        s.tree_.clear();
    }
    
    template <typename _T, class _Compare, class _Allocator>
    set<_T, _Compare, _Allocator>::~set(){
        this->tree_.clear();
    }	
    
    template <typename _T, class _Compare, class _Allocator>
    set<_T, _Compare, _Allocator>& 
    set<_T, _Compare, _Allocator>::operator=(set &&s){
        if(this != &s){
            this->tree_ = std::move(s.tree_);
        }
        return *this;
    }	
    
    template <typename _T, class _Compare, class _Allocator>
    typename set<_T, _Compare, _Allocator>::iterator 
    set<_T, _Compare, _Allocator>::begin(){
        return this->tree_.begin();                
    }	
    
    template <typename _T, class _Compare, class _Allocator>
    typename set<_T, _Compare, _Allocator>::iterator 
    set<_T, _Compare, _Allocator>::end(){
        return this->tree_.end();
    }	

    template <typename _T, class _Compare, class _Allocator>
    typename set<_T, _Compare, _Allocator>::iterator 
    set<_T, _Compare, _Allocator>::begin() const{
        return this->tree_.begin();            
    }

    template <typename _T, class _Compare, class _Allocator>
    typename set<_T, _Compare, _Allocator>::iterator 
    set<_T, _Compare, _Allocator>::end() const{
        return this->tree_.end();
    }

    template <typename _T, class _Compare, class _Allocator>
    typename set<_T, _Compare, _Allocator>::reverse_iterator 
    set<_T, _Compare, _Allocator>::rbegin(){
        return reverse_iterator(this->tree_.end());
    }

    template <typename _T, class _Compare, class _Allocator>
    typename set<_T, _Compare, _Allocator>::reverse_iterator 
    set<_T, _Compare, _Allocator>::rend(){
        return reverse_iterator(this->tree_.begin());
    }

    template <typename _T, class _Compare, class _Allocator>
    typename set<_T, _Compare, _Allocator>::reverse_iterator 
    set<_T, _Compare, _Allocator>::rbegin() const{
        return reverse_iterator(this->tree_.end());
    }
    
    template <typename _T, class _Compare, class _Allocator>
    typename set<_T, _Compare, _Allocator>::reverse_iterator 
    set<_T, _Compare, _Allocator>::rend() const{
        return reverse_iterator(this->tree_.begin());
    }
    
    template <typename _T, class _Compare, class _Allocator>
    bool 
    set<_T, _Compare, _Allocator>::empty(){
        return this->tree_.size() == 0;
    }
    
    template <typename _T, class _Compare, class _Allocator>
    typename set<_T, _Compare, _Allocator>::size_type 
    set<_T, _Compare, _Allocator>::size(){
        return this->tree_.size();
    }
    
    template <typename _T, class _Compare, class _Allocator>
    typename set<_T, _Compare, _Allocator>::size_type 
    set<_T, _Compare, _Allocator>::max_size(){
        return this->tree_.max_size();
    }	
    
    template <typename _T, class _Compare, class _Allocator>
    void 
    set<_T, _Compare, _Allocator>::clear(){
        this->tree_.clear();
    }
    
    template <typename _T, class _Compare, class _Allocator>
    std::pair<typename set<_T, _Compare, _Allocator>::iterator, bool> 
    set<_T, _Compare, _Allocator>::insert(const_reference __ref){
        if(this->tree_.find(__ref) == this->tree_.end()){
            return {this->tree_.insert(__ref), true};
        }
        return {this->end(), false};
    }
    
    template <typename _T, class _Compare, class _Allocator>
    void 
    set<_T, _Compare, _Allocator>::erase(iterator __pos){
        if(this->empty()){
            throw std::out_of_range("s21::set erase empty");
        }
        this->tree_.erase(__pos);
    }

    template <typename _T, class _Compare, class _Allocator>
    void 
    set<_T, _Compare, _Allocator>::erase(iterator __f, iterator __l){
        if(this->empty()){
            throw std::out_of_range("s21:: set erase empty");
        }

        while(__f != __l){
            this->tree_.erase(__f++);
        }
    }
    template <typename _T, class _Compare, class _Allocator>
    void 
    set<_T, _Compare, _Allocator>::erase(const_reference __ref){
        iterator __it = this->tree_.find(__ref);
        if(__it != this->tree_.end()){
            this->tree_.erase(__it);
        }
    }
    
    template <typename _T, class _Compare, class _Allocator>
    void 
    set<_T, _Compare, _Allocator>::swap(set& __oth){
        if(this != &__oth){
            this->tree_.swap(__oth.tree_);
        }
    }
    
    template <typename _T, class _Compare, class _Allocator>
    void 
    set<_T, _Compare, _Allocator>::merge(set& __oth){
        if(this != &__oth){
            for(
                iterator __it = __oth.begin();
                __it != __oth.end();
            ){
                if(this->tree_.find(*__it) == this->tree_.end()){
                    this->tree_.insert(*__it);
                    __oth.erase(__it);
                    __it = __oth.begin();
                }else{
                    __it++;
                }
            }
        }
    }
    
    template <typename _T, class _Compare, class _Allocator>
    typename set<_T, _Compare, _Allocator>::iterator 
    set<_T, _Compare, _Allocator>::find(const_reference __ref){
        return this->tree_.find(__ref);
    }

    template <typename _T, class _Compare, class _Allocator>
    typename set<_T, _Compare, _Allocator>::iterator 
    set<_T, _Compare, _Allocator>::lower_bound(const_reference __ref){
        return this->tree_.lower_bound(__ref);
    }
    
    template <typename _T, class _Compare, class _Allocator>
    typename set<_T, _Compare, _Allocator>::iterator 
    set<_T, _Compare, _Allocator>::upper_bound(const_reference __ref){
        return this->tree_.upper_bound(__ref);
    }
    
    template <typename _T, class _Compare, class _Allocator>
    typename set<_T, _Compare, _Allocator>::size_type 
    set<_T, _Compare, _Allocator>::count(const_reference __ref){
        return this->contains(__ref) ? 1 : 0;
    }
    
    template <typename _T, class _Compare, class _Allocator>
    bool 
    set<_T, _Compare, _Allocator>::contains(const_reference __ref){
        return this->tree_.find(__ref) != this->tree_.end();
    }
}