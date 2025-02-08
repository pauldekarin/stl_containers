#pragma once
#include "array.h"

namespace s21{
    template <typename _T, std::size_t _N>
    array<_T,_N>::array(){
        this->fill(value_type());
    }	
    template <typename _T, std::size_t _N>
    array<_T,_N>::array(std::initializer_list<value_type> const &__il){
        if(__il.size() > _N){
            throw std::out_of_range("list too large");
        }

        for(
            typename std::initializer_list<value_type>::iterator it = __il.begin();
            it != __il.end();
            it++
        ){
            this->data_[std::distance(__il.begin(), it)] = *it;
        }
    }	
    template <typename _T, std::size_t _N>
    array<_T,_N>::array(const array &__oth){
        std::copy( __oth.begin(), __oth.end(), this->data() );
    }
    template <typename _T, std::size_t _N>
    array<_T,_N>::array(array && __oth){
        std::copy( __oth.begin(), __oth.end(), this->data() );
    }	
    template <typename _T, std::size_t _N>
    array<_T,_N>::~array(){

    }	
    template <typename _T, std::size_t _N>
    array<_T,_N>&  array<_T, _N>::operator=(array &&__oth){
        if(this != &__oth){
            std::copy( __oth.begin(), __oth.end(), this->data() );
        }
        return *this;
    }	
    template <typename _T, std::size_t _N>
    typename array<_T,_N>::reference
    array<_T, _N>::at(size_type __pos){
        if(__pos >= _N){
            throw std::out_of_range("operator[] out of bounds");
        }

        return *(this->data_ + __pos);
    }	
    template <typename _T, std::size_t _N>
    typename array<_T,_N>::reference
    array<_T, _N>::operator[](size_type __pos){
        return this->at(__pos);
    }	
    template <typename _T, std::size_t _N>
    typename array<_T,_N>::const_reference
    array<_T, _N>::front(){
        static_assert(
            _N > 0,
            "front is empty"
        );

        return *this->data_;
    }
    template <typename _T, std::size_t _N>
    typename array<_T,_N>::const_reference
    array<_T, _N>::back(){
        static_assert(
            _N > 0,
            "back is empty"
        );

        return *(this->data_ + _N - 1);
    }
    template <typename _T, std::size_t _N>
    typename array<_T,_N>::iterator
    array<_T, _N>::data(){
        return this->data_;
    }	
    template <typename _T, std::size_t _N>
    typename array<_T,_N>::iterator
    array<_T, _N>::begin() const{
        return iterator(this->data_);
    }
    template <typename _T, std::size_t _N>
    typename array<_T,_N>::iterator
    array<_T, _N>::end() const{
        return iterator(this->data_ + _N);
    }
    template <typename _T, std::size_t _N>
    bool 
    array<_T, _N>::empty(){
        return _N == 0;
    }
    template <typename _T, std::size_t _N>
    typename array<_T,_N>::size_type 
    array<_T, _N>::size(){
        return _N;
    }	
    template <typename _T, std::size_t _N>
    typename array<_T,_N>::size_type 
    array<_T, _N>::max_size(){
        return _N;
    }
    template <typename _T, std::size_t _N>
    void 
    array<_T, _N>::swap(array& __oth){
        if(&__oth != this){
            std::swap(this->data_, __oth.data_);
        }
    }
    template <typename _T, std::size_t _N>
    void 
    array<_T, _N>::fill(const_reference value){
        for(size_type __i = 0; __i < _N; __i++){
            this->data_[__i] = value;
        }
    }
}