#pragma once
#include "deque.h"
template <typename _T, size_t buff_size>
__deque_iterator<_T, buff_size>::__deque_iterator(){}

template <typename _T, size_t buff_size>
template <typename _U>
__deque_iterator<_T, buff_size>::__deque_iterator(const __deque_iterator<_U, buff_size> &__d):begin_(__d.begin_), end_(__d.end_), current_(__d.current_), map_(const_cast<__map_pointer>(__d.map_)){}

template <typename _T, size_t buff_size>
__deque_iterator<_T, buff_size>::__deque_iterator(pointer __begin, pointer __end, pointer __current, __map_pointer __map):begin_(__begin), end_(__end), current_(__current),map_(__map){}

template <typename _T, size_t buff_size>
__deque_iterator<_T, buff_size>::__deque_iterator(const __deque_iterator &__d):begin_(__d.begin_), end_(__d.end_), current_(__d.current_), map_(__d.map_){}

template <typename _T, size_t buff_size>
void 
__deque_iterator<_T, buff_size>::_assign(difference_type __n){
    this->begin_ = *this->map_;
    this->end_ = this->begin_ + buff_size - 1;
    this->current_ = this->begin_ + __n;
}
template <typename _T, size_t buff_size>
typename __deque_iterator<_T, buff_size>::reference 
__deque_iterator<_T, buff_size>::operator*(){
    return *this->current_;
}

template <typename _T, size_t buff_size>
__deque_iterator<_T, buff_size>& 
__deque_iterator<_T, buff_size>::operator+=(difference_type __n){
    *this = *this + __n;
    return *this;
}
template <typename _T, size_t buff_size>
__deque_iterator<_T, buff_size>& 
__deque_iterator<_T, buff_size>::operator-=(difference_type __n){
    *this = *this - __n;
    return *this;
}
template <typename _T, size_t buff_size>
__deque_iterator<_T, buff_size> 
__deque_iterator<_T, buff_size>::operator-(difference_type __n){
    __deque_iterator __it(*this);

    while(__n >= buff_size){
        __it.map_--;
        __n -= buff_size;
    }

    if(std::distance(__it.begin_, __it.current_) < __n){
        __it.map_--;
        __n = buff_size + std::distance(__it.begin_, __it.current_) - __n;
    }else{
        __n = std::distance(__it.begin_, __it.current_) - __n;
    }

    __it._assign(__n);

    return __it;
}

template <typename _T, size_t buff_size>
typename __deque_iterator<_T, buff_size>::difference_type 
__deque_iterator<_T, buff_size>::operator-(const __deque_iterator &__it){
    difference_type __n = 0;
    for(__deque_iterator __jt = __it ; __jt != *this;__n++, __jt++);
    return __n;
}

template <typename _T, size_t buff_size>
__deque_iterator<_T, buff_size> 
__deque_iterator<_T, buff_size>::operator+(difference_type __n){
    __deque_iterator __it(*this);

    while(__n > buff_size){
        __it.map_++;
        __n -= buff_size;
    }

    if(std::distance(__it.begin_, __it.current_) + __n >= buff_size){
        __it.map_++;
        __n -= std::distance(__it.current_, __it.end_) + 1;
    }else{
        __n += std::distance(__it.begin_, __it.current_);
    }
    __it._assign(__n);

    return __it;
}
template <typename _T, size_t buff_size>
__deque_iterator<_T, buff_size>& 
__deque_iterator<_T, buff_size>::operator++(){
    if(this->current_ == this->end_){
        this->map_++;
        this->_assign();
    }else{
        this->current_++;
    }

    return *this;
}
template <typename _T, size_t buff_size>
__deque_iterator<_T, buff_size>& 
__deque_iterator<_T, buff_size>::operator=(const __deque_iterator &__it){
    if(this != &__it){

        this->begin_ = __it.begin_;
        this->end_ = __it.end_;
        this->current_ = __it.current_;
        this->map_ = __it.map_;
    }
    
    return *this;
}
template <typename _T, size_t buff_size>
__deque_iterator<_T, buff_size>& 
__deque_iterator<_T, buff_size>::operator=(__deque_iterator &&__it){
    if(this != &__it){
        this->begin_ = __it.begin_;
        this->end_ = __it.end_;
        this->current_ = __it.current_;
        this->map_ = __it.map_;

        __it.begin_ = nullptr;
        __it.current_ = nullptr;
        __it.end_ = nullptr;
        __it.map_ = nullptr;
    }

    return *this;
}template <typename _T, size_t buff_size>
__deque_iterator<_T, buff_size>
__deque_iterator<_T, buff_size>::operator++(int){
    __deque_iterator __tmp(*this);
    ++(*this);
    return __tmp;
}
template <typename _T, size_t buff_size>
__deque_iterator<_T, buff_size>& 
__deque_iterator<_T, buff_size>::operator--(){
    if(this->current_ == this->begin_){
        this->map_--;
        this->_assign(buff_size - 1);
    }else{
        this->current_--;
    }

    return *this;
}

template <typename _T, size_t buff_size>
__deque_iterator<_T, buff_size> 
__deque_iterator<_T, buff_size>::operator--(int){
    __deque_iterator __tmp(*this);
    --(*this);
    return __tmp;
}
template <typename _T, size_t buff_size>
bool 
__deque_iterator<_T, buff_size>::operator==(const __deque_iterator &__it){
    return this->begin_ == __it.begin_ && this->end_ == __it.end_ && this->current_ == __it.current_ && this->map_ == __it.map_;
}
template <typename _T, size_t buff_size>
bool 
__deque_iterator<_T, buff_size>::operator!=(const __deque_iterator &__it){
    return !(*this == __it);
}