#pragma once
#include "queue.h"

namespace s21{
    template <typename _T, class _Container>
    queue<_T, _Container>::queue(){

    }

    template <typename _T, class _Container>
    queue<_T, _Container>::queue(std::initializer_list<value_type> const &__il):c_(__il){
        
    }

    template <typename _T, class _Container>
    queue<_T, _Container>::queue(const queue<_T, _Container> &__q):c_(__q.c_){

    }

    template <typename _T, class _Container>
    queue<_T, _Container>::queue(queue<_T, _Container> &&__q):c_(std::move(__q.c_)){

    }

    template <typename _T, class _Container>
    queue<_T, _Container>::~queue(){
        this->c_.clear();
    }

    template <typename _T, class _Container>
    queue<_T, _Container>& queue<_T, _Container>::operator=(queue &&__q){
        if(this != &__q){
            this->c_ = std::move(__q.c_);
        }
        return *this;
    }

    template <typename _T, class _Container>
    typename queue<_T, _Container>::const_reference queue<_T, _Container>::front(){
        return this->c_.front();
    }

    template <typename _T, class _Container>
    typename queue<_T, _Container>::const_reference queue<_T, _Container>::back(){
        return this->c_.back();
    }

    template <typename _T, class _Container>
    bool queue<_T, _Container>::empty(){
        return this->c_.empty();
    }   

    template <typename _T, class _Container>
    typename queue<_T, _Container>::size_type queue<_T, _Container>::size(){
        return this->c_.size();
    }

    template <typename _T, class _Container>
    void queue<_T, _Container>::push(const_reference __ref){
        this->c_.push_back(__ref);
    }
    template <typename _T, class _Container>
    template <class... Args>
    void queue<_T, _Container>::insert_many_back(Args&&... args){
        static_assert((std::is_convertible<Args, _T>::value && ...), "queue insert many back must be convertible args");
        ((push(std::forward<Args>(args))), ...);
    }
    template <typename _T, class _Container>
    void queue<_T, _Container>::pop(){
        this->c_.erase(this->c_.begin());
    }

    template <typename _T, class _Container>
    void queue<_T, _Container>::swap(queue &__q){
        if(this != &__q){
            std::swap(this->c_, __q.c_);
        }
    }

}
