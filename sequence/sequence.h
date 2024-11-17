#pragma once

#include <memory>
#include <iostream>
#include <initializer_list>
#include <iterator>

namespace s21{
    template<typename _T, class _Allocator = std::allocator<_T>>
    class sequence{
    public:

        using alloc_type = _Allocator;
        using reference = typename alloc_type::reference;
        using value_type = typename alloc_type::value_type;
        using const_reference = typename alloc_type::const_reference;
        using size_type = typename alloc_type::size_type;
        using pointer = typename alloc_type::pointer;

        class __iterator{
        public:
            typedef typename alloc_type::difference_type        difference_type;
            typedef typename sequence::value_type               value_type;
            typedef typename sequence::pointer                  pointer;
            typedef typename sequence::reference                reference;
            typedef typename std::random_access_iterator_tag    iterator_category;
            typedef typename sequence::size_type                size_type;

            __iterator(pointer __p):__ptr(__p){}
            __iterator(const __iterator &__it): __ptr(__it.__ptr){}

            ~__iterator(){

            }
            __iterator& operator++(){
                this->__ptr++;
                return *this;
            }
            __iterator operator++(int){
                __iterator __tmp(*this);
                ++(*this);
                return __tmp;
            }
            __iterator& operator--(){
                this->__ptr--;
                return *this;
            }
            __iterator operator--(int){
                __iterator __tmp(*this);
                --(*this);
                return __tmp;
            }

            __iterator& operator+(size_type __n){
                this->__ptr += __n;
                return *this;
            }
            
            __iterator& operator+=(size_type __n){
                this->__ptr += __n;
                return *this;
            }

            size_type operator-(const __iterator &__it){
                return __it.__ptr - this->__ptr;
            }

            bool operator==(const __iterator& __it){
                return this->__ptr == __it.__ptr;
            }
            bool operator!=(const __iterator& __it){
                return this->__ptr != __it.__ptr;
            }


            reference operator*(){
                return *this->__ptr;
            }
            pointer get() const {
                return this->__ptr;
            }

        protected:
            pointer __ptr;
        };


        using iterator = __iterator;
        using const_iterator = const iterator;
        using reverse_iterator = _VSTD::reverse_iterator<iterator>;
        using const_reverse_iterator = _VSTD::reverse_iterator<const_iterator>;
        using alloc_traits = _VSTD::allocator_traits<alloc_type>;

    protected:
        alloc_type alloc_;
        size_type size_ = 0;
        pointer data_ = nullptr;

    public:
        sequence():data_(alloc_traits::allocate(this->alloc_, 1)){
            alloc_traits::construct(this->alloc_, this->data_, value_type());
        }
        sequence(const std::initializer_list<_T> &__il):
            data_(alloc_traits::allocate(this->alloc_, 1)), size_(__il.size())
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

        iterator begin() const{
            return iterator(this->data_);
        }
        iterator end() const{
            return iterator(this->data_ + this->size_);
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
            pointer __tmp = alloc_traits::allocate(this->alloc_, __sz  + 1);
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


        void insert(iterator __pos, const _T &__value){
            iterator __it = __pos;
            size_type __n = std::distance(__pos, this->end());

            for(size_type __i = 0; __i <= __n; __i++){
                *std::next(__it) = std::move(*__it);
            }
            
            *__pos = __value;
        }

        void insert(iterator __it, size_type __n, const _T &__value){
            size_type __pos = std::distance(this->begin(), __it);

            for(size_type _i = 0; _i < __n; _i++){
                this->insert( std::next(this->begin(), __pos), __value );
            }
        }

        template<class _InputIter>
        void insert(iterator __it, _InputIter __beg, _InputIter __end){
            size_type __pos = std::distance(this->begin(), __it);

            while(__beg != __end){
                this->insert(std::next(this->begin(), __pos), *__beg);
                __pos++;
                __beg++;
            }
        }

        void erase(iterator __it){
            pointer __tmp = this->alloc_.allocate(this->size_);
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
            size_type __pos = std::distance(this->begin(), __b);
            size_type __n = std::distance(__b, __e);

            for(size_type _i = 0; _i < __n; _i++){
                this->erase(std::next(this->begin, __pos));
            }
        }

        void push_back(const _T &__t){
            this->insert(this->end(), __t);
        }

        void pop_back(){
            this->erase(std::prev(this->end()));
        }

        reference back(){
            return *(this->end());
        }

        reference front(){
            return *(this->begin());
        }
    };
}