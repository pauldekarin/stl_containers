#pragma
#include "list.h"
template <typename _T>
__list_iterator<_T>::__list_iterator(){}

template <typename _T>
__list_iterator<_T>::__list_iterator(__node *__n):n_(__n){}

template <typename _T>
typename __list_iterator<_T>::__node* 
__list_iterator<_T>::get() const{
    return this->n_;
}

template <typename _T>
template <typename _U, typename>
__list_iterator<_T>::__list_iterator(const __list_iterator<_U>& __it)
    : n_(reinterpret_cast<__node*>(__it.n_)) {}


template <typename _T>
typename __list_iterator<_T>::pointer 
__list_iterator<_T>::operator->(){
    return &(this->n_->value_);
}
template <typename _T>
typename __list_iterator<_T>::reference 
__list_iterator<_T>::operator*(){
    return this->n_->value_;
}
template <typename _T>
__list_iterator<_T>& 
__list_iterator<_T>::operator++(){
    if(this->n_ != nullptr && !this->n_->is_sentinel_){
        this->n_ = this->n_->head_;
    }
    return *this;
}
template <typename _T>
__list_iterator<_T> 
__list_iterator<_T>::operator++(int){
    __list_iterator tmp(*this);
    ++(*this);
    return tmp;
}
template <typename _T>
__list_iterator<_T>& 
__list_iterator<_T>::operator--(){
    if(this->n_->foot_ != nullptr){
        this->n_ = this->n_->foot_;
    }
    return *this;
}
template <typename _T>
__list_iterator<_T>
__list_iterator<_T>::operator--(int){
    __list_iterator tmp(*this);
    --(*this);
    return tmp;
}
template <typename _T>
__list_iterator<_T>& 
__list_iterator<_T>::operator+(difference_type __n){
    for(difference_type _i = 0; _i < __n; _i++) if(this->n_ != nullptr) this->n_ = this->n_->head_;
    return *this;
}
template <typename _T>
bool 
__list_iterator<_T>::operator==(const __list_iterator &__li) const{
    return this->n_ == __li.get();
}
template <typename _T>
bool 
__list_iterator<_T>::operator!=(const __list_iterator &__li) const{
    return this->n_ != __li.get();
}