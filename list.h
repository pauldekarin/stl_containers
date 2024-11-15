#ifndef S21_LIST
#define S21_LIST

#include <memory>
#include <iostream>
#include <list>
#include "sequence.h"

namespace s21{
    template <typename _T, class _Allocator = std::allocator<_T>>
    class list{
    public:
        struct __node{
            __node *head_ = nullptr;
            __node *foot_ = nullptr;

            _T value_;
            bool is_sentinel_ = false;
            __node(const _T &__v):value_(__v), is_sentinel_(false){}
        };

       
        using alloc_type = _Allocator;
        using value_type = typename alloc_type::value_type;
        using reference = typename alloc_type::reference;
        using const_referece = typename alloc_type::const_reference;
        using size_type = typename alloc_type::size_type;
        using pointer = typename alloc_type::pointer;

        class __list_iterator{
        private:
            __node *n_;

        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type = _T;
            using difference_type = typename alloc_type::difference_type;
            using pointer =   pointer;
            using reference =   reference;

            __list_iterator(__node *__n):n_(__n){}

            __node *get() const{
                return this->n_;
            }

            pointer operator->(){
                return &(this->n_->value_);
            }

            reference operator*(){
                return this->n_->value_;
            }

            __list_iterator& operator++(){
                if(this->n_ != nullptr && !this->n_->is_sentinel_){
                    this->n_ = this->n_->head_;
                }
                return *this;
            }

            __list_iterator operator++(int){
                __list_iterator tmp(*this);
                ++(*this);
                return tmp;
            }

            __list_iterator& operator--(){
                if(this->n_->foot_ != nullptr){
                    this->n_ = this->n_->foot_;
                }
                return *this;
            }
            
            __list_iterator operator--(int){
                __list_iterator tmp(*this);
                --(*this);
                return tmp;
            }

            __list_iterator& operator+(size_type __n){
                for(size_type _i = 0; _i < __n; _i++) if(this->n_ != nullptr) this->n_ = this->n_->head_;
                return *this;
            }

            bool operator==(const __list_iterator &__li){
                return this->n_ == __li.get();
            }

            bool operator!=(const __list_iterator &__li) const{
                return this->n_ != __li.get();
            }
        };
        using iterator = __list_iterator;
        using const_iterator = iterator;
        using node_allocator = typename std::allocator_traits<alloc_type>::template rebind_alloc<__node>;
        using alloc_traits = std::allocator_traits<node_allocator>;

    protected:
        node_allocator alloc_;
        __node *root_ = nullptr;
        __node *sentinel_ = nullptr;
        size_type size_ = 0;

    public:
        list(){
            this->_init_sentinel();
        }

        list(size_type __n){
            this->_init_sentinel();
            for(size_type _i = 0; _i < __n; _i++){
                this->insert(this->begin(), _T());
            }
        }

        list(const std::initializer_list<_T> &__il)
        {
            this->_init_sentinel();
            for(typename std::initializer_list<_T>::iterator it = __il.begin(); it != __il.end(); it++){
                this->insert(this->end(), *it);
            }
        }

        list(const list &__l){
            this->_init_sentinel();
            for(iterator it = __l.begin(); it != __l.end(); it++){
                this->insert(this->end(), *it);
            }
        }

        list(list &&__l){
            this->_init_sentinel();

            this->root_ = __l.root_;
            this->sentinel_->foot_ = __l.sentinel_->foot_;
            this->sentinel_->head_ = __l.sentinel_->head_;
            this->sentinel_->value_ = __l.sentinel_->value_;
            this->size_ = __l.size_;
            if(this->sentinel_->foot_ != nullptr) this->sentinel_->foot_->head_ = this->sentinel_;

            __l.root_ = nullptr;
            __l.sentinel_->head_ = nullptr;
            __l.sentinel_->foot_ = nullptr;
            __l.sentinel_->value_  = 0;
            __l.size_ = 0;
        }

        ~list(){
            this->clear();
            this->_clear_sentinel();
        }

        //Element access
        const_referece front(){
            if(this->empty()){
                throw std::out_of_range("list is empty");
            }else{
                return this->begin().get()->value_;
            }
        }

        const_referece back(){
            if(this->empty()){
                throw std::out_of_range("list is empty");
            }else{
                return std::prev(this->end()).get()->value_;
            }
        }

        //List Capacity
        size_type size() const{
            return this->size_;
        }
        
        size_type max_size() const{
            return std::allocator_traits<alloc_type>::max_size(this->alloc_);
        }

        inline bool empty() const{
            return this->size() == 0;
        }

        //List Modifiers

        iterator insert(iterator __pos, const_referece __value){
            __node *__n = alloc_traits::allocate(this->alloc_,1);
            alloc_traits::construct(this->alloc_, __n, __value);

            if(this->root_ == nullptr){
                this->root_ = __n;
                __n->head_ = this->sentinel_;
                __n->foot_ = nullptr;
                this->sentinel_->foot_ = this->root_;
            }else if(__pos == this->end()){
                __n->head_ = this->sentinel_;
                __n->foot_ = this->sentinel_->foot_;
                if(this->sentinel_->foot_ != nullptr) this->sentinel_->foot_->head_ = __n;
                this->sentinel_->foot_ = __n;
            }else{
                __n->head_ = __pos.get();
                __n->foot_ = __pos.get()->foot_;

                if(__pos.get()->foot_ != nullptr) __pos.get()->foot_->head_ = __n;
                __pos.get()->foot_ = __n;

                if(__pos == this->begin()) this->root_ = __n;
                else if(__pos.get()->head_ == this->sentinel_) this->sentinel_->foot_ = __n;
            }

            this->sentinel_->value_ = ++this->size_;

            return iterator(__n);
        }
        
        void clear(){
            while(this->begin() != this->end()){
                this->erase(this->begin());
            }
            this->root_ = nullptr;
            this->size_ = 0;
            
            this->sentinel_->head_ = nullptr;
            this->sentinel_->foot_ = nullptr;
            this->sentinel_->value_ = 0;
            
        }

        void erase(iterator __pos){
            if(__pos == this->end()){
                throw std::invalid_argument("can't erase end-iterator");
            }
            if(__pos.get() != nullptr){
                __node *__n = __pos.get();
                if(__n->head_ != nullptr) __n->head_->foot_ = __n->foot_;
                if(__n->foot_ != nullptr) __n->foot_->head_ = __n->head_;
                if(__n == this->root_) this->root_ = __n->head_;
                this->_clear_node(__n);
                this->sentinel_->value_ = --this->size_;
            }
        }
        
        void push_back(const_referece __ref){
            this->insert(this->end(), __ref);
        }

        void pop_back(){
            if(this->sentinel_->foot_ == nullptr){
                throw std::out_of_range("can't pop_back() empty list");
            }
            this->erase(iterator(this->sentinel_->foot_));
        }

        void push_front(const_referece __ref){
            this->insert(this->begin(), __ref);
        }

        void swap(list &__oth){
            if(this != &__oth){
                __node *__tmp_root = this->root_;
                __node *__tmp_sentinel = this->sentinel_;
                size_type __tmp_size = this->size_;

                this->root_ = __oth.root_;
                this->sentinel_ = __oth.sentinel_;
                this->size_ = __oth.size_;

                __oth.root_ = __tmp_root;
                __oth.sentinel_ = __tmp_sentinel;
                __oth.size_ = __tmp_size;
            }
        }

        template <class _Compare = std::less<_T>>
        void merge(list &__oth, _Compare comp = _Compare()){
            list __merged(this->size_ + __oth.size_);

            iterator _lhs_it = this->begin();
            iterator _merged_it = __merged.begin();
            iterator _oth_it = __oth.begin();

            while(_merged_it != __merged.end()){
                if(_lhs_it == this->end()){
                    *_merged_it = *_oth_it;
                    _oth_it++;
                }else if(_oth_it == __oth.end()){
                    *_merged_it = *_lhs_it;
                    _lhs_it++;
                }else if(comp(*_lhs_it, *_oth_it)){
                    *_merged_it = *_lhs_it;
                    _lhs_it++;
                }else{
                    *_merged_it = *_oth_it;
                    _oth_it++;
                }
                _merged_it++;
            }

            this->clear();
            __oth.clear();
            this->swap(__merged);
        }

        void splice(const_iterator __pos, list &__oth){
            if(this == &__oth){
                throw std::invalid_argument("can't splice same object");
            }
            if(__oth.size() == 0) return;

            this->size_ += __oth.size_;

            __node *pos_node = __pos.get();
            __node *oth_tail = __oth.sentinel_->foot_;
            __node *oth_root = __oth.root_;

            __oth.size_ = 0;
            __oth.root_ = nullptr;
            __oth.sentinel_->foot_ = nullptr;

            if(__pos == this->begin()){ 
                oth_tail->head_ = this->root_;
                if(this->root_ != nullptr) this->root_->foot_ = oth_tail;
                this->root_ = oth_root;
            }else if(__pos == this->end()){
                if (this->sentinel_->foot_) this->sentinel_->foot_->head_ = oth_root;
                oth_root->foot_ = this->sentinel_->foot_;
                this->sentinel_->foot_ = oth_tail;
                oth_tail->head_ = this->sentinel_;
            }else{
                oth_tail->head_ = pos_node;
                oth_root->foot_ = pos_node->foot_;
                if (pos_node->foot_) pos_node->foot_->head_ = oth_root;
                pos_node->foot_ = oth_tail;
            }
            this->sentinel_->value_ = this->size_;
        }       

        void reverse(){
            if(this->size() > 1){
                iterator __e = this->end();
                iterator __b = this->begin();

                __node *__tail = __b.get();

                for(; __b != __e;){
                    std::swap(__b.get()->foot_, __b.get()->head_);
                    __b--;
                }

                std::swap(__e.get()->foot_, __e.get()->head_);

                this->root_ = __e.get()->head_;
                this->root_->foot_ = nullptr;

                this->sentinel_->foot_ = __tail;
                this->sentinel_->head_ = nullptr;

                __tail->head_ = this->sentinel_;
            }
        }

        void unique(){
            if(this->size() > 1){
                for(iterator __b = this->begin(); __b != this->end(); __b++){
                    while(__b.get()->head_ != this->sentinel_ && __b.get()->head_->value_ == __b.get()->value_){
                        __node *__next = __b.get()->head_;
                        __b.get()->head_ = __next->head_;
                        if(__next->head_) __next->head_->foot_ = __b.get();
                        _clear_node(__next);
                        this->sentinel_->value_ = --this->size_;
                    }
                }
            }
        }

        template <typename _Compare = std::less<_T>>
        void sort(){
            this->_sort(this->begin(), this->end());
        }

        iterator begin() {
            return this->size() == 0 ? this->end() : iterator(this->root_);
        }

        iterator end() {
            return iterator(this->sentinel_);
        }

        const_iterator begin() const{
            return this->size() == 0 ? this->end() : const_iterator(this->root_);
        }

        const_iterator end() const{
            return const_iterator(this->sentinel_);
        }

        list& operator=(const list &__oth){
            if(this != &__oth){
                this->clear();
                for(iterator it = __oth.begin(); it != __oth.end(); it++){
                    this->insert(this->end(), *it);
                }
            }
            return *this;
        }

        list& operator=(list &&__oth){
            if(this != &__oth){
                this->clear();
                
                this->root_ = __oth.root_;
                this->sentinel_->foot_ = __oth.sentinel_->foot_;
                this->sentinel_->head_ = __oth.sentinel_->head_;
                this->sentinel_->value_ = __oth.sentinel_->value_;
                if(this->sentinel_->foot_ != nullptr) this->sentinel_->foot_->head_ = this->sentinel_;
                this->size_ = __oth.size_;

                __oth.root_ = nullptr;
                __oth.sentinel_->head_ = nullptr;
                __oth.sentinel_->foot_ = nullptr;
                __oth.sentinel_->value_  = 0;
                __oth.size_ = 0;
            }
            return *this;
        }

    private:
        template <typename _Compare = std::less<_T>>
        void _sort(iterator __begin, iterator __end, _Compare comp = _Compare()) {
            for(iterator _it = __begin; _it != std::prev(__end); _it++){
                for(iterator _jt = __begin; _jt != std::prev(__end); _jt++){
                    if(!comp(*_jt, *std::next(_jt))){
                        std::swap(_jt.get()->value_, std::next(_jt).get()->value_);
                    }
                }
            }   
        }


        void _clear_node(__node *__n){
            if(__n != nullptr){
                alloc_traits::destroy(this->alloc_, __n);
                alloc_traits::deallocate(this->alloc_, __n, 1);
            }
        }    

        void _init_sentinel(){
            this->sentinel_ = alloc_traits::allocate(this->alloc_, 1);
            alloc_traits::construct(this->alloc_, this->sentinel_, 0);
            this->sentinel_->head_ = nullptr;
            this->sentinel_->foot_ = nullptr;
            this->sentinel_->is_sentinel_ = true;
        }

        void _clear_sentinel(){
            if(this->sentinel_ != nullptr){
                this->_clear_node(this->sentinel_);
                this->sentinel_ = nullptr;
            }
        }
    };
};

#endif