#pragma once
#include "tree.h"


template <typename _T>
__tree_iterator<_T>::__tree_iterator(){}

template <typename _T>
__tree_iterator<_T>::__tree_iterator(__tree_iterator &&__tr):n_(__tr.n_){
    __tr.n_ = nullptr;
}


template <typename _T>
__tree_iterator<_T>& __tree_iterator<_T>::operator=(const __tree_iterator& __tr){
    if(this != &__tr){
        this->n_ = __tr.n_;
    }
    return *this;
}

template <typename _T>
__tree_iterator<_T>& __tree_iterator<_T>::operator=(__tree_iterator&& __tr){
    if(this != &__tr){
        this->n_ = __tr.n_;
        __tr.n_ = nullptr;
    }
    return *this;
}

template <typename _T>
__tree_iterator<_T>::__tree_iterator(__node<value_type> *__n):n_(__n){}

template <typename _T>
__tree_iterator<_T>::__tree_iterator(const __tree_iterator &__it):n_(__it.n_){}

template <typename _T>
template <typename _R>
__tree_iterator<_T>::__tree_iterator(const __tree_iterator<_R> &__it):n_(reinterpret_cast<__node<value_type>*>(__it.n_)){
    
}

template <typename _T>
__tree_iterator<_T>::~__tree_iterator(){}

template <typename _T>
__tree_iterator<_T>& __tree_iterator<_T>::operator++(){
    if(this->n_ == nullptr){
        throw std::out_of_range("");
    }

    if(this->n_->right_ != nullptr){
        this->n_ = this->n_->right_;
        while(this->n_->left_ != nullptr) this->n_ = this->n_->left_;
    }else{
        __node<value_type> *__p = this->n_->parent_;
        while(__p != nullptr && __p->right_ == this->n_){
            this->n_ = __p;
            __p = __p->parent_;
        }
        this->n_ = __p;
    }

    return *this;
}

template <typename _T>
__tree_iterator<_T> __tree_iterator<_T>::operator--(int){
    __tree_iterator __tmp(*this);
    --(*this);
    return __tmp;
}

template <typename _T>
__tree_iterator<_T>& __tree_iterator<_T>::operator--(){
    if(this->n_ == nullptr){
        throw std::out_of_range("");
    }   

    if(this->n_->left_ != nullptr){
        this->n_ = this->n_->left_;
        while(this->n_->right_ != nullptr) this->n_ = this->n_->right_;
    }else{
        __node<value_type> *__p = this->n_->parent_;
        while(__p != nullptr && __p->left_ == this->n_){
            this->n_ = __p;
            __p = __p->parent_;
        }
        this->n_ = __p;
    }

    return *this;
}

template <typename _T>
__tree_iterator<_T> __tree_iterator<_T>::operator++(int){
    __tree_iterator __tmp(*this);
    ++(*this);
    return __tmp;
}

template <typename _T>
bool __tree_iterator<_T>::operator==(const __tree_iterator &__it){
    return this->n_ == __it.n_;
}

template <typename _T>
bool __tree_iterator<_T>::operator!=(const __tree_iterator &__it){
    return this->n_ != __it.n_;
}

template <typename _T>
typename __tree_iterator<_T>::template __node<typename __tree_iterator<_T>::value_type>* __tree_iterator<_T>::get(){
    return this->n_;
}

template <typename _T>
typename __tree_iterator<_T>::reference __tree_iterator<_T>::operator*(){
    return this->n_->value_;
}

template <typename _T>
typename __tree_iterator<_T>::pointer  __tree_iterator<_T>::operator->(){
    return &(this->n_->value_);
}




    