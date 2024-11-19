#pragma once

#include <memory>
#include <deque>
#include <iostream>
#include <type_traits>
#include "../utility/utility.hpp"

namespace s21{
    template <typename _T, size_t buff_size = 8>
    struct __deque_iterator{
    public:
        typedef _T**                                __map_pointer;
        typedef _T*                                 pointer;
        typedef std::random_access_iterator_tag     iterator_category;
        typedef std::ptrdiff_t                      difference_type;
        typedef _T                                  value_type;
        typedef _T&                                 reference;
    protected:
        
    public:
        pointer current_ = nullptr;
        pointer begin_ = nullptr;
        pointer end_ = nullptr;

        __map_pointer map_ = nullptr;
        __deque_iterator(){}
        
        template <typename _U>
        __deque_iterator(const __deque_iterator<_U, buff_size> &__d):begin_(__d.begin_), end_(__d.end_), current_(__d.current_), map_(const_cast<__map_pointer>(__d.map_)){}

        __deque_iterator(pointer __begin, pointer __end, pointer __current, __map_pointer __map):begin_(__begin), end_(__end), current_(__current),map_(__map){}

        __deque_iterator(const __deque_iterator &__d):begin_(__d.begin_), end_(__d.end_), current_(__d.current_), map_(__d.map_){}
        
        void _assign(difference_type __n = 0){
            this->begin_ = *this->map_;
            this->end_ = this->begin_ + buff_size - 1;
            this->current_ = this->begin_ + __n;
        }

        reference operator*(){
            return *this->current_;
        }

        
        __deque_iterator& operator+=(difference_type __n){
            *this = *this + __n;
            return *this;
        }

        __deque_iterator& operator-=(difference_type __n){
            *this = *this - __n;
            return *this;
        }

        __deque_iterator operator-(difference_type __n){
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
        
        difference_type operator-(const __deque_iterator &__it){
            difference_type __n = 0;
            for(__deque_iterator __jt = __it ; __jt != *this;__n++, __jt++);
            return __n;
        }
        __deque_iterator operator+(difference_type __n){
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

        __deque_iterator& operator++(){
            if(this->current_ == this->end_){
                this->map_++;
                this->_assign();
            }else{
                this->current_++;
            }

            return *this;
        }

        __deque_iterator& operator=(const __deque_iterator &__it){
            if(this != &__it){

                this->begin_ = __it.begin_;
                this->end_ = __it.end_;
                this->current_ = __it.current_;
                this->map_ = __it.map_;
            }
            
            return *this;
        }

        __deque_iterator& operator=(__deque_iterator &&__it){
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
        }
        __deque_iterator operator++(int){
            __deque_iterator __tmp(*this);
            ++(*this);
            return __tmp;
        }

        __deque_iterator& operator--(){
            if(this->current_ == this->begin_){
                this->map_--;
                this->_assign(buff_size - 1);
            }else{
                this->current_--;
            }

            return *this;
        }

        __deque_iterator operator--(int){
            __deque_iterator __tmp(*this);
            --(*this);
            return __tmp;
        }

        bool operator==(const __deque_iterator &__it){
            return this->begin_ == __it.begin_ && this->end_ == __it.end_ && this->current_ == __it.current_ && this->map_ == __it.map_;
        }

        bool operator!=(const __deque_iterator &__it){
            return !(*this == __it);
        }
    };

    template <typename _T, class _Allocator = std::allocator<_T>>
    class deque{
    public:
        typedef typename _Allocator::value_type                                                     value_type;
        typedef typename _Allocator::reference                                                      reference;
        typedef typename _Allocator::const_reference                                                const_reference;
        typedef typename std::allocator_traits<_Allocator>::template rebind_alloc<value_type>       alloc_type;
        typedef __deque_iterator<_T>                                                                iterator;
        typedef __deque_iterator<const _T>                                                          const_iterator;
        typedef std::reverse_iterator<iterator>                                                     reverse_iterator;
        typedef std::reverse_iterator<const_iterator>                                               const_reverse_iterator;
        typedef typename _Allocator::pointer                                                        pointer;
        typedef typename _Allocator::size_type                                                      size_type;

        typedef typename std::allocator_traits<_Allocator>::template rebind_alloc<value_type>       __value_alloc;
        typedef std::allocator_traits<__value_alloc>                                                __value_traits;

        typedef typename __deque_iterator<_T>::__map_pointer                                        __map_pointer;
        typedef typename std::allocator_traits<_Allocator>::template rebind_alloc<pointer>    __map_alloc;
        typedef std::allocator_traits<__map_alloc>                                                  __map_traits;
        struct __deque_range{
            
        };
    protected:
        alloc_type alloc_;

        size_type __chunk_size = 8;
        size_type size_ = 0;

        __value_alloc val_alloc_;

        __map_alloc map_alloc_;
        __map_pointer map_ = nullptr;
        size_type __map_size = 0;

        iterator head_;
        iterator tail_;

    public: 
        deque(){
            this->_increase_map();
        }
        
        deque(std::initializer_list<value_type> const &__il){
            this->_construct(__il.begin(), __il.end());
        }

        deque(const deque &__dq){
            this->_construct(__dq.begin(), __dq.end());
        }

        deque(deque &&__dq){
            
            this->_move(std::move(__dq));
        }

        ~deque(){
            this->_deallocate();
        }

        deque& operator=(deque &&__dq){
            if(this != &__dq){
                this->_deallocate();
                this->_move(std::move(__dq));
            }

            return *this;
        }

        iterator begin(){
            return this->head_;
        }

        iterator end(){
            return this->tail_;
        }

        const_iterator begin() const{
            return const_iterator(this->head_);
        }
        const_iterator end() const{
            return const_iterator(this->tail_);
        }

        reverse_iterator rbegin(){
            return reverse_iterator(this->tail_);
        }
        reverse_iterator rend(){
            return reverse_iterator(this->head_);
        }

        const_reference front(){
            return *this->head_;
        }

        const_reference back(){
            return *(this->tail_ - 1);
        }

        bool empty(){
            return this->begin() == this->end();
        }

        size_type size(){
            return this->size_;
        }

        void clear(){
            if(this->map_ != nullptr){
                this->head_.map_ = this->map_ + this->__map_size / 2;
                this->tail_.map_ = this->map_ + this->__map_size / 2;
                this->head_._assign(this->__chunk_size / 2);
                this->tail_._assign(this->__chunk_size / 2);
                this->size_ = 0;
            }
        }

        size_type capacity(){
            return this->__chunk_size * this->__map_size;
        }

        void push_front(const_reference __ref){
            if(!this->_has_avaliable_space()){
                this->_increase_map();
            }
            if(this->size()){
                this->head_--;
            }else{
                this->tail_++;
            }
            this->size_++;
            *this->head_ = __ref;
        }   

        void push_back(const_reference __ref){
            if(!this->_has_avaliable_space(false)){
                this->_increase_map(false);
            }
            *this->tail_++ = __ref;
            this->size_++;
        }

        void insert(iterator __pos, const_reference __ref){
            if(__pos == this->begin()){
                this->push_front(__ref);
            }else if(__pos == this->end()){
                this->push_back(__ref);
            }else{
                if(!this->_has_avaliable_space(false)){
                    typename iterator::difference_type __diff = std::distance(this->begin(), __pos);
                    this->_increase_map(false);
                    __pos = std::next(this->begin(), __diff);
                }

                for(iterator it = this->end(); it != __pos; it--){
                    *it = std::move(*(it - 1));
                }
                *__pos = __ref;
                this->tail_++;
                this->size_++;
            }
        }

        void insert(iterator __pos, size_type __n, const_reference __ref){
            typename iterator::difference_type __diff = std::distance(this->begin(), __pos);
            for(size_type __i = 0; __i < __n; __i++){
                this->insert(std::next(this->begin(), __diff), __ref);
            }
        }

        void shrink_to_fit(){
            if(this->empty()){
                this->clear();
                this->_deallocate();
                return;
            }

            if(std::distance(this->map_, this->head_.map_)){
                size_type __dist = std::distance(this->map_, this->head_.map_);
                size_type __new_size = this->__map_size - __dist;

                __map_pointer __new_map = __map_traits::allocate(this->map_alloc_, __new_size);

                for(size_type __i = 0; __i < this->__map_size - __dist; __i++){
                    __map_traits::construct(this->map_alloc_, __new_map + __i, this->__copy_chunk(this->map_[__i + __dist]));
                }

                this->head_.map_ = __new_map;
                this->tail_.map_ = __new_map + std::distance(this->map_, this->tail_.map_) - __dist;

                this->head_._assign(std::distance(this->head_.begin_, this->head_.current_));
                this->tail_._assign(std::distance(this->tail_.begin_, this->tail_.current_));

                this->_deallocate();

                this->map_ = __new_map;
                this->__map_size = __new_size;
            }

            if(std::distance(this->map_, this->tail_.map_) < this->__map_size - 1){
                size_type __dist = this->__map_size - 1 - std::distance(this->map_, this->tail_.map_);
                size_type __offset = std::distance(this->map_, this->head_.map_);

                size_type __new_size = this->__map_size - __dist + __offset;
                __map_pointer __new_map = __map_traits::allocate(this->map_alloc_, __new_size);

                for(size_type __i = 0; __i < __new_size; __i++){
                    __map_traits::construct(this->map_alloc_, __new_map + __i, this->__copy_chunk(this->map_[__i + __offset]));
                }
                this->head_.map_ = __new_map;
                this->tail_.map_ = __new_map + __new_size - 1;

                this->head_._assign(std::distance(this->head_.begin_, this->head_.current_));
                this->tail_._assign(std::distance(this->tail_.begin_, this->tail_.current_));

                this->_deallocate();

                this->map_ = __new_map;
                this->__map_size = __new_size;
            }
        }

        template <class _InputIter, typename = typename std::enable_if<!std::is_integral<_InputIter>::value>::type>
        void insert(iterator __pos, _InputIter __f, _InputIter __l){
            typename iterator::difference_type __diff = std::distance(this->begin(), __pos);
            for(typename iterator::difference_type __i = __diff; __f != __l; __f++, __i++){
                this->insert(std::next(this->begin(), __i), *__f);
            }
        }

        void pop_back(){
            this->tail_--;
            this->size_--;
        }

        void pop_front(){
            this->head_++;
            this->size_--;
        }
        void erase(iterator __pos){
            if(__pos == this->begin()){
                this->pop_front();
            }else if(__pos == this->end()){
                this->pop_back();
            }else{
                for(iterator it = __pos; it != this->end(); it++){
                    *it = std::move(*(it + 1));
                }
                this->tail_--;
                this->size_--;
            }
        }
    
    private:
        void _move(deque &&__dq){
            this->map_ = __dq.map_;
            this->head_ = __dq.head_;
            this->tail_ = __dq.tail_;
            this->__map_size = __dq.__map_size;
            this->__chunk_size = __dq.__chunk_size;
            this->size_ = __dq.size_;

            __dq.map_ = nullptr;
            __dq.size_ = 0;
            __dq.__map_size = 0;
        }

        template <class _InputIter>
        void _construct(_InputIter __b, _InputIter __e){
            while(__b != __e){
                this->push_back(*__b++);
            }
        }

        bool _has_avaliable_space(bool in_front = true){
            if(this->map_ == nullptr) return false;

            if(in_front){
                if(std::distance(this->map_, this->head_.map_) == 0 && this->head_.current_ == this->head_.begin_){
                    return false;
                }
            }else{
                if(std::distance(this->map_, this->tail_.map_) == this->__map_size - 1 && this->tail_.current_ == this->tail_.end_){
                    return false;
                }
            }   

            return true;
        }

        void _increase_map(bool in_front = true, size_type __n = 1){
            __map_pointer __new_map = __map_traits::allocate(this->map_alloc_, this->__map_size + __n);
            if(in_front){
                for(size_type __i = 0; __i < __n; __i++){
                    __new_map[__i] = this->__create_chunk();
                }
                for(size_type __i = 0; __i < this->__map_size; __i++){
                    __map_traits::construct(this->map_alloc_, __new_map + __n + __i, this->__copy_chunk(this->map_[__i]));
                }

                if(this->map_ != nullptr){
                    this->head_.map_ = __new_map + __n + std::distance(this->map_, this->head_.map_);
                    this->tail_.map_ = __new_map + __n + std::distance(this->map_, this->tail_.map_);
                }else{
                    this->head_.map_ = __new_map + __n / 2;
                    this->tail_.map_ = __new_map + __n / 2;
                }
            }else{
                for(size_type __i = 0; __i < this->__map_size; __i++){
                    __map_traits::construct(this->map_alloc_, __new_map + __i, this->__copy_chunk(this->map_[__i]));
                }
                for(size_type __i = this->__map_size; __i < this->__map_size + __n; __i++){
                    __new_map[__i] = this->__create_chunk();
                }

                if(this->map_ != nullptr){
                    this->head_.map_ = __new_map +  std::distance(this->map_, this->head_.map_);
                    this->tail_.map_ = __new_map +  std::distance(this->map_, this->tail_.map_);
                }else{
                    this->head_.map_ = __new_map + __n / 2;
                    this->tail_.map_ = __new_map + __n / 2;
                }
            }

            if(this->map_ != nullptr){
                this->head_._assign(std::distance(this->head_.begin_, this->head_.current_));
                this->tail_._assign(std::distance(this->tail_.begin_, this->tail_.current_));
            }else{
                this->head_._assign(this->__chunk_size / 2);
                this->tail_._assign(this->__chunk_size / 2);
            }

            __n += this->__map_size;
            this->_deallocate();
            this->map_ = __new_map;
            this->__map_size = __n;
        }

        pointer  __create_chunk(){
            pointer __chunk = __value_traits::allocate(this->val_alloc_, this->__chunk_size);
            for(size_type __i = 0; __i < this->__chunk_size; __i++){
                __value_traits::construct(this->val_alloc_, __chunk + __i, value_type());
            }
            return __chunk;
        }

        pointer __copy_chunk(pointer __src){
            pointer __dst = this->__create_chunk();
            for(size_type __i = 0; __i < this->__chunk_size; __i++){
                __dst[__i] = __src[__i];
            }
            return __dst;
        }

        void __clear_chunk(pointer __chunk){
            for(size_type __i = 0; __i < this->__chunk_size; __i++){
                __value_traits::destroy(this->val_alloc_, __chunk + __i);
            }
            __value_traits::deallocate(this->val_alloc_, __chunk, this->__chunk_size);
        }

        void _deallocate(){
            if(this->map_ != nullptr){
                for(size_type __i = 0; __i < this->__map_size; __i++){
                    this->__clear_chunk(this->map_[__i]);
                    __map_traits::destroy(this->map_alloc_, this->map_ + __i);
                }
                __map_traits::deallocate(this->map_alloc_, this->map_, this->__map_size);
                this->map_ = nullptr;
                this->__map_size = 0;
            }

            // this->map_ = nullptr;
            // this->__map_size = 0;
            // this->size_ = 0;
        }
    };
};