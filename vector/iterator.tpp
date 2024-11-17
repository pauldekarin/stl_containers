#pragma once

#include "vector.h"


namespace s21{
    template <typename _T>
    __vec_iterator<_T>::__vec_iterator(){}

    template <typename _T>
    __vec_iterator<_T>::__vec_iterator(__vec_iterator<_T>::pointer __p): __ptr__(__p){}
    
    template <typename _T>
    __vec_iterator<_T>::__vec_iterator(const __vec_iterator<_T> &__i): __ptr__(__i.__ptr__){}

    template <typename _T>
    __vec_iterator<_T>& __vec_iterator<_T>::operator++(){
        this->__ptr__++;
        return *this;
    }

    template <typename _T>
    __vec_iterator<_T> __vec_iterator<_T>::operator++(int){
        __vec_iterator __tmp(*this);
        ++(*this);
        return __tmp;
    }   

    template <typename _T>
    __vec_iterator<_T>& __vec_iterator<_T>::operator--(){
        this->__ptr__--;
        return *this;
    }

    template <typename _T>
    __vec_iterator<_T> __vec_iterator<_T>::operator--(int){
        __vec_iterator __tmp(*this);
        --(*this);
        return __tmp;
    }

    template <typename _T>
    __vec_iterator<_T>& __vec_iterator<_T>::operator+=(difference_type __n){
        this->__ptr__ += __n;
        return *this;
    }

    template <typename _T>
    __vec_iterator<_T>& __vec_iterator<_T>::operator-=(difference_type __n){
        this->__ptr__ -= __n;
        return *this;
    }


    template <typename _T>
    typename __vec_iterator<_T>::difference_type __vec_iterator<_T>::operator-(__vec_iterator& __i){
        return this->__ptr__ - __i.__ptr__;
    }


    template <typename _T>
    __vec_iterator<_T> __vec_iterator<_T>::operator+(difference_type __n){
        return __vec_iterator<_T>(this->__ptr__ + __n);
    }

    template <typename _T>
    bool __vec_iterator<_T>::operator==(const __vec_iterator& __vi){
        return this->__ptr__ == __vi.__ptr__;
    }

    template <typename _T>
    bool __vec_iterator<_T>::operator!=(const __vec_iterator& __vi){
        return this->__ptr__ != __vi.__ptr__;
    }

    template <typename _T>
    typename __vec_iterator<_T>::reference __vec_iterator<_T>::operator*(){
        return *(this->__ptr__);
    }

    template <typename _T>
    typename __vec_iterator<_T>::pointer __vec_iterator<_T>::operator->(){
        return this->__ptr__;
    }
}