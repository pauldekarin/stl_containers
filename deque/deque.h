#pragma once

#include <memory>
#include <deque>

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

        __deque_iterator(pointer __begin, pointer __end, pointer __current, __map_pointer __map):begin_(__begin), end_(__end), current_(__current),map_(__map){

        }

        __deque_iterator(const __deque_iterator &__d):begin_(__d.begin_), end_(__d.end_), current_(__d.current_), map_(__d.map_){}
        
        reference operator*(){
            return *this->current_;
        }

        __deque_iterator& operator+=(difference_type __n){
            while(__n > buff_size){
                this->map_++;
                __n -= buff_size;
            }
            if(std::distance(this->current_, this->end_) < __n){
                this->map_++;
                __n -= std::distance(this->current_, this->end_) + 1;
            }
            this->begin_ = *this->map_;
            this->end_ = this->begin_ + buff_size - 1;
            this->current_ = this->begin_ + __n;
            
            return *this;
        }

        __deque_iterator& operator++(){
            if(this->current_ == this->end_){
                this->map_++;
                this->begin_ = *this->map_;
                this->end_ = this->begin_ + buff_size - 1;
                this->current_ = this->begin_;
            }else{
                this->current_++;
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
                this->begin_ = *this->map_;
                this->end_ = this->begin_ + buff_size - 1;
                this->current_ = this->end_;
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
            return this->begin_ == __it.begin_ && this->end_ == __it.end_ && this->current_ == __it.current_;
        }

        bool operator!=(const __deque_iterator &__it){
            return *this != __it;
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
        size_type __map_size = 8;

        iterator head_;
        iterator tail_;

    public: 
        deque(){
            this->map_ = __map_traits::allocate(this->map_alloc_, this->__map_size);
            for(size_type __i = 0; __i < this->__map_size; __i++){
                this->map_[__i] = this->__create_chunk();
            }
            size_type __mid_idx = this->__map_size / 2;
            // this->map_[ __mid_idx ] = this->__create_chunk();

            this->head_.map_ =  this->tail_.map_ = this->map_ + __mid_idx;
            this->head_.begin_ = this->tail_.begin_ = this->map_[ __mid_idx ];
            this->head_.end_ = this->tail_.end_ = this->head_.begin_ + this->__chunk_size - 1;

            this->head_.current_ = this->head_.begin_ + this->__chunk_size / 2;
            this->tail_.current_ = this->tail_.begin_ + this->__chunk_size / 2 + 1;
        }
        
        iterator begin(){
            return this->head_;
        }

        iterator end(){
            return std::next(this->tail_);
        }

        void push_front(const_reference __ref){
            this->head_--;
            this->size_++;
            *this->head_ = __ref;
        }   

        void push_back(const_reference __ref){
            this->tail_++;
            this->size_++;
            *this->tail_ = __ref;
        }
    
    private:
        void __resize_map(){

        }

        pointer  __create_chunk(){
            pointer __chunk = __value_traits::allocate(this->val_alloc_, this->__chunk_size);
            for(size_type __i = 0; __i < this->__chunk_size; __i++){
                __value_traits::construct(this->val_alloc_, __chunk + __i, value_type());
            }
            return __chunk;
        }
    };
};