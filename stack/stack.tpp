#pragma once
#include "stack.h"

namespace s21{
    template <typename _T, class _Container>        
    stack<_T, _Container>::stack(){

    }

    template <typename _T, class _Container>        
    stack<_T, _Container>::stack(std::initializer_list<value_type> &__il){
        this->c_ = _Container(__il);
    }

    template <typename _T, class _Container>        
    stack<_T, _Container>::stack(const stack<_T, _Container>& __s){
        this->c_ = _Container(__s);
    }

    template <typename _T, class _Container>        
    stack<_T, _Container>::stack(stack<_T, _Container>&& __s){
        this->c_ = __s.c_;
        __s.c_ = _Container();
    }

    template <typename _T, class _Container>        
    stack<_T, _Container>::~stack(){
        this->c_.clear();
    }

    template <typename _T, class _Container>        
    stack<_T, _Container>& stack<_T, _Container>::operator=(stack &&__s){
        if(this != &__s){
            this->c_ = __s.c_;
            __s.c_ = _Container();
        }
    }

    template <typename _T, class _Container>        
    typename stack<_T, _Container>::const_reference stack<_T, _Container>::top(){
        return this->c_.back();
    }

    template <typename _T, class _Container>        
    bool stack<_T, _Container>::empty(){
        return this->c_.empty();
    }

    template <typename _T, class _Container>        
    typename stack<_T, _Container>::size_type stack<_T, _Container>::size(){
        return this->c_.size();
    }

    template <typename _T, class _Container>        
    void stack<_T, _Container>::push(const_reference __ref){
        this->c_.push_back(__ref);
    }

    template <typename _T, class _Container>        
    void stack<_T, _Container>::pop(){
        this->c_.pop_back();
    }

    template <typename _T, class _Container>        
    void stack<_T, _Container>::swap(stack &&__s){
        std::swap(this->c_, __s.c_);
    }

}