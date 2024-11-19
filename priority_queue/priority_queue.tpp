#pragma once
#include "priority_queue.h"
namespace s21{
    template<typename _T, class _Container, class _Compare>
    priority_queue<_T, _Container, _Compare>::priority_queue(){

    }

    template<typename _T, class _Container, class _Compare>
    priority_queue<_T, _Container, _Compare>::priority_queue(std::initializer_list<value_type> const &__il):c_(__il){
        
    }

    template<typename _T, class _Container, class _Compare>
    priority_queue<_T, _Container, _Compare>::priority_queue(const priority_queue &__pq):c_(__pq.c){
    }

    template<typename _T, class _Container, class _Compare>
    priority_queue<_T, _Container, _Compare>::priority_queue(priority_queue<_T, _Container, _Compare> &&__pq){
        this->c_ = __pq.c_;
        __pq.c_ = _Container();
    }

    template<typename _T, class _Container, class _Compare>
    priority_queue<_T, _Container, _Compare>::~priority_queue(){

    }

    template<typename _T, class _Container, class _Compare>
    priority_queue<_T, _Container, _Compare>& priority_queue<_T, _Container, _Compare>::operator=(priority_queue &&__pq){
        if(this != &__pq){
            this->c_ = std::move(__pq.c_);
            __pq.c_ = _Container();
        }
    }

    template<typename _T, class _Container, class _Compare>
    bool priority_queue<_T, _Container, _Compare>::empty(){
        return this->c_.empty();
    }

    template<typename _T, class _Container, class _Compare>
    typename priority_queue<_T, _Container, _Compare>::size_type priority_queue<_T, _Container, _Compare>::size(){
        return this->c_.size();
    }

    template<typename _T, class _Container, class _Compare>
    typename priority_queue<_T, _Container, _Compare>::const_reference priority_queue<_T, _Container, _Compare>::top(){
        return this->c_.back();
    }   

    template<typename _T, class _Container, class _Compare>
    void priority_queue<_T, _Container, _Compare>::push(const_reference __ref){
        typename _Container::iterator it = this->c_.begin();
        while(it != this->c_.end() && this->comp_(*it, __ref)) it++;
        this->c_.insert(it, __ref);
    }

    template<typename _T, class _Container, class _Compare>
    void priority_queue<_T, _Container, _Compare>::pop(){
        this->c_.pop_back();
    }

    template<typename _T, class _Container, class _Compare>
    void priority_queue<_T, _Container, _Compare>::swap(priority_queue<_T, _Container,_Compare> &__pq){
        if(this != &__pq){
            std::swap(this->c_, __pq.c_);
        }
    }

}
