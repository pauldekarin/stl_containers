#pragma once

#include <memory>
#include <vector>
#include <iostream>
#include <initializer_list>

namespace s21{
    template <typename T, class Allocator = std::allocator<T>>
    class vector{
    public:
        using allocator_type = Allocator;
        using size_type = typename Allocator::size_type;
        using difference_type = typename Allocator::difference_type;
        using reference = typename Allocator::reference;
        using const_reference = typename Allocator::const_reference;
        using pointer = typename Allocator::pointer;
        using const_pointer = typename Allocator::const_pointer;
        using value_type = T;
        using iterator = pointer;
        using const_iterator = const_pointer;


    protected:
        allocator_type alloc_;
    
    private:
        pointer data_;

        size_type capacity_;
        size_type size_;

        iterator begin_;
        iterator end_;
    public:
        vector(const Allocator &alloc = Allocator()):size_(0), capacity_(1), alloc_(alloc), data_(alloc_.allocate(1)), begin_(data_),end_(data_) {

        }
        vector(size_type n, const T &value = T(), const Allocator &alloc = Allocator()):
        size_(n), capacity_(n), alloc_(alloc), data_(alloc_.allocate(n)), begin_(data_), end_(data_ + n)
        {
            for(size_type i = 0; i < n; i++){
                alloc_.construct(data_ + i, value);
            }
        }
        vector(const vector &oth):
        size_(oth.size_), capacity_(oth.capacity_),alloc_(oth.alloc_), data_(alloc_.allocate(size_))
        {
            for(size_type i = 0; i < this->size_; i++){
                alloc_.construct(this->data_ + i, oth.data_[i]);
            }
        }
        vector(vector &&oth):
        size_(oth.size_), capacity_(oth.capacity_),alloc_(oth.alloc_), data_(oth.data_)
        {
            oth.data_ = nullptr;
        }
        pointer data(){
            return this->data_;
        }
        const_pointer data() const noexcept{
            return this->data_;
        }
        vector(std::initializer_list<T> __il):
        alloc_(Allocator()),
        size_(__il.size()),
        capacity_(__il.size()),
        data_(alloc_.allocate(__il.size()))
        {
            const T* _it = __il.begin();
            while(_it != __il.end()){
                this->alloc_.construct(this->data_ + (_it - __il.begin()), *_it++);
            }
        }
        ~vector(){
            if(this->data_ != nullptr){

                this->clear();
                this->alloc_.deallocate(this->data_, this->capacity_);
                this->data_ = nullptr;
                this->capacity_ = 0;
            }
        }
        iterator begin(){
            return this->data_;
        }
        const_iterator begin() const{
            return this->data_;
        }

        void reserve(size_type __capacity){
            if(__capacity > this->capacity_){
                T* __new_data = this->alloc_.allocate(__capacity);
                for(size_type i = 0; i < this->size_; i++){
                    this->alloc_.construct(__new_data + i, std::move(this->data_[i]));
                    this->alloc_.destroy(this->data_ + i);
                }
                this->alloc_.deallocate(this->data_, this->capacity_);
                this->data_ = __new_data;
                this->capacity_ = __capacity;
            }
        }

        void resize(size_type __sz){
            if(this->size_ < __sz){
                this->reserve(__sz * 2);
            }else if(this->size_ > __sz){
                for(size_type i = __sz; i < this->size_; i++){
                    this->alloc_.destroy(this->data_ + i);
                }
            }
            this->size_ = __sz;
        }

        void push_back(const T &__ref){
            this->alloc_.construct(this->data_ + this->size_++, __ref);
            if(this->size_ == this->capacity_){
                this->reserve(this->capacity_ * 2);
            }
        }

        void push_back(T &&__ref){
            this->alloc_.construct(this->data_ + this->size_++, std::move(__ref));
            if(this->size_ == this->capacity_){
                this->reserve(this->capacity_ * 2);
            }
        }
        
        void pop_back(){
            if(this->empty()) throw std::out_of_range("s21::vector cant pop empty container");
            this->alloc_.destroy(this->data_ + this->size_-- - 1);
        }

        iterator end(){
            return this->data_ + this->size_;
        }
        const_iterator end() const{
            return this->data_ + this->size_;
        }

        inline size_type size() const{
            return this->size_;
        }
        inline size_type capacity() const {
            return this->capacity_;
        }
        inline bool empty() const noexcept{
            return this->size_ == 0;
        }

        reference operator[](size_type index){
            if(index >= this->size_) throw std::out_of_range("s21::vector index out of bounds");
            return this->data_[index];
        }
        const_reference operator[](size_type index) const{
            if(index >= this->size_) throw std::out_of_range("s21::vector index out of bounds");
            return this->data_[index];
        }  

        reference at(size_type index){
            if(index >= this->size_) throw std::out_of_range("s21::vector index out of bounds");
            return this->data_[index];
        }
        const_reference at(size_type index) const{
            if(index >= this->size_) throw std::out_of_range("s21::vector idnex out of bounds");
            return this->data_[index];
        }

        vector& operator=(std::initializer_list<T> &__il);

        void clear(){
            for(size_type i = 0; i < this->size_; i++){
                this->alloc_.destroy(this->data_ + i);
            }
            this->size_ = 0;
        }
    };
};