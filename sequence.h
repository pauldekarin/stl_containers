#pragma once

#include <memory>
#include <iostream>
#include <initializer_list>
#include <iterator>

namespace s21{
    template<typename _T, class _Iterator = _T*, class _Allocator = std::allocator<_T>>
    class sequence{
    public:
        using alloc_type = _Allocator;
        using reference = typename alloc_type::reference;
        using const_reference = typename alloc_type::const_reference;
        using size_type = typename alloc_type::size_type;

        using iterator = _Iterator;
        using const_iterator = const iterator;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    protected:
        alloc_type alloc_;
        size_type size_ = 0;
        iterator data_ = nullptr;

    public:
        sequence():data_(this->alloc_.allocate(1)){
            this->alloc.construct(this->data_, _T());
        }
        sequence(const std::initializer_list<_T> &__il):
            data_(this->alloc_.allocate(__il.size())), size_(__il.size())
        {
            for(auto it = __il.begin(); it != __il.end() ; it++){
                this->alloc_.construct(this->data_ + (it - __il.begin()), *it);
            }
        }
        sequence(size_type _n, _T& _t = _T()):data_(this->alloc_.allocate(_n)), size_(_n){
            for(size_type _i = 0; _i < _n; _i++){
                this->alloc_.construct(this->data_ + _i, _t);
            }
        }
        sequence(const sequence &_s):data_(this->alloc_.allocate(_s.size_)), size_(_s.size_){
            for(size_type _i = 0; _i < _s.size_; _i++){
                this->alloc_.construct(this->data_ + _i, _s.data_[_i]);
            }
        }
        ~sequence(){
            this->clear();
            this->alloc_.deallocate(this->data_, this->size_ + 1);
        }
        void clear(){
            for(size_type _i = 0; _i < this->size_; _i++){
                this->alloc_.destroy(this->data_ + _i);
            }
        }

        iterator begin(){
            return this->data_;
        }
        iterator end(){
            return this->data_ + this->size_;
        }

        reverse_iterator rbegin(){
            return reverse_iterator(this->end());
        }  

        reverse_iterator rend(){
            return reverse_iterator(this->begin());
        }

        sequence& operator=(const sequence &_s){
            if(&this != _s){
                this->clear();
                this->alloc_.deallocate(this->data_, this->size_ + 1);

                this->data_ = this->alloc_.allocate(_s.size_ + 1);
                for(size_type _i = 0; _i < _s.size_; _i++){
                    this->alloc.construct(this->data_ + _i, _s.data_[_i]);
                }
                this->size_ = _s.size_;
            }

            return *this;
        }

        size_type size() const{
            return this->size_;
        }

        void resize(size_type __sz){
            _T* __tmp = this->alloc_.allocate(__sz);
            for(size_type _i = 0; _i < std::min(__sz, this->size_); _i++){
                this->alloc_.construct(__tmp + _i, this->data_[_i]);
            }

            this->clear();
            this->alloc_.deallocate(this->data_, this->size_ + 1);

            this->size_ = __sz;
            this->data_ = __tmp;
        }

        bool empty(){
            return this->size_ == 0;
        }


        void insert(iterator __it, const _T &__value){
            iterator _lt = this->data_;
            iterator __tmp = this->alloc_.allocate(this->size_ + 2);

            for(size_type _i = 0; _i < this->size_ + 2; _i++){
                if(_lt == __it){
                    this->alloc_.construct(__tmp + _i, __value);
                    ++_i;
                }
                this->alloc_.construct(__tmp + _i, *_lt);
                _lt++;
            }

            this->clear();
            this->alloc_.deallocate(this->data_, this->size_ + 1);
            
            this->size_ = this->size_ + 1;
            this->data_ = __tmp;
        }

        void insert(iterator __it, size_type __n, const _T &__value){
            size_type __pos = __it - this->begin();

            for(size_type _i = 0; _i < __n; _i++){
                this->insert( this->begin() + __pos, __value );
            }
        }

        template<class _InputIter>
        void insert(iterator __it, _InputIter __beg, _InputIter __end){
            size_type __pos = __it - this->begin();

            while(__beg != __end){
                this->insert(this->begin() + __pos, *__beg);
                __pos++;
                __beg++;
            }
        }

        void erase(iterator __it){
            iterator __tmp = this->alloc_.allocate(this->size_);
            iterator __beg = this->begin();
            size_type _i = 0;

            while(__beg != this->end()){
                if(__beg != __it){
                    this->alloc_.construct(__tmp + _i, *__beg);
                    _i++;
                }
                __beg++;
            }

            this->clear();
            this->alloc_.deallocate(this->data_, this->size_);

            this->data_ = __tmp;
            this->size_--;
        }

        void erase(iterator __b, iterator __e){
            size_type __pos = __b - this->begin();
            size_type __n = __e - __b;

            for(size_type _i = 0; _i < __n; _i++){
                this->erase(this->begin() + __pos);
            }
        }

        void push_back(const _T &__t){
            this->insert(this->end(), __t);
        }

        void pop_back(){
            this->erase(std::prev(this->end()));
        }

        reference back(){
            return *(this->data_ + this->size_ - 1);
        }

        reference front(){
            return *(this->begin());
        }
    };
}