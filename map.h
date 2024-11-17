#pragma once

#include <iostream>
#include <memory>
#include <map>
#include <initializer_list>
#include <utility>
#include "pair.h"


namespace s21{
    template <typename _Key, typename _Value, class _Compare = std::less<_Key>, class _Allocator = std::allocator<std::pair<const _Key, _Value>> >
    class map{
    public:
        template <typename _T>
        struct __node{
        public:
            __node *left_ = nullptr;
            __node *right_ = nullptr;
            __node *parent_ = nullptr;

            bool is_sentinel_ = false;
            _T value_;

            __node(_T __t, __node *__p = nullptr):value_(__t), parent_(__p){}
            __node(const __node &_oth):left_(_oth.left_), right_(_oth.right_), value_(_oth.value_), is_sentinel_(_oth.is_sentinel_), parent_(_oth.parent_){}

           
           __node* _next_node() {
                if (this->is_sentinel_) {
                    return nullptr; // No valid next node
                }

                __node* current = this;

                if (current->right_ != nullptr) {
                    current = current->right_; 
                    while (current->left_ != nullptr) {
                        current = current->left_; 
                    }
                    return current; 
                } else {
                    __node* p = current->parent_;
                    while (p != nullptr && p->right_ == current) {
                        current = p; 
                        p = p->parent_;
                    }

                    return p; 
                }
            }

            __node *_prev_node(){
                __node *current = this;

                if(this->left_ != nullptr){
                    current = current->left_;
                    while(current->right_ != nullptr) current = current->right_;

                    return current;
                }else{
                    __node *__parent = this->parent_;
                    while(__parent != nullptr && __parent->left_ == current){
                        current = __parent;
                        __parent = __parent->parent_;
                    }
                    return __parent;
                }
            }

            bool _equal_node(const __node &__n){
                return this->left_ == __n.left_ && this->right_ == __n.right_ && this->parent_ == __n.parent_ && this->is_sentinel_ == __n.is_sentinel_ && this->value_ == __n.value_;
            }
            
            void _replace(__node *__n){
                __node __tmp(*__n);

                __n->left_ = this->left_;
                __n->right_ = this->right_;
                __n->parent_ = this->parent_;

                if(__n->left_ != nullptr) __n->left_->parent_ = __n;
                if(__n->right_ != nullptr) __n->right_->parent_ = __n;
                if(this->_has_parent() && this->_is_left_child()) __n->parent_->left_ = __n;
                else if(this->_has_parent() && this->_is_right_child()) __n->parent_->right_ = __n;
                
                
                this->left_ = __tmp.left_;
                this->right_ = __tmp.right_;
                this->parent_ = __tmp.parent_;
                if(this->left_ != nullptr) this->left_->parent_ = this;
                if(this->right_ != nullptr) this->right_->parent_ = this;

                if(__tmp._has_parent()){
                    if(__tmp.parent_->left_ == __n){
                        this->parent_->left_ = this;
                    }else{
                        this->parent_->right_ = this;
                    }
                }
            }

            void _cut(){
                if(this->left_ != nullptr) this->left_->parent_ = nullptr;
                if(this->right_ != nullptr) this->right_->parent_ = nullptr;
                if(this->_has_parent() && this->_is_left_child()) this->parent_->left_ = nullptr;
                else if(this->_has_parent() && this->_is_right_child()) this->parent_->right_ = nullptr;
            }

            void _replace_parent_node(__node *__n){
                if(_has_parent()){
                    if(_is_left_child()){
                        this->parent_->left_ = __n;
                    }else{
                        this->parent_->right_ = __n;
                    }
                }
            }

            bool _has_parent(){
                return this->parent_ != nullptr;
            }

            bool _is_left_child(){
                return this->_has_parent() && this->parent_->left_ == this;
            }

            bool _is_right_child(){
                return this->_has_parent() && this->parent_->right_ == this;
            }

            bool operator==(const __node &__n){
               return this->_equal_node(__n);
            }

            bool operator!=(const __node &__n){
                return !this->_equal_node(__n);
            }


            __node& operator=(const __node &__n){
                if(this != &__n){
                    this->left_ = __n.left_;
                    this->right_ = __n.right_;
                    this->parent_ = __n.parent_;
                    this->value_ = __n.value_;
                    this->is_sentinel_ = __n.is_sentinel_;
                }
                return *this;
            }

            __node& operator=(__node &&__oth){
                if(this != &__oth){

                }   

                return *this;
            }

            _T* operator->(){
                return &(this->value_);
            }

            _T& get(){
                return this->value_;
            }
        };

        using alloc_type = _Allocator;
        using key_type = _Key;
        using mapped_type = _Value;
        using value_type = typename alloc_type::value_type;
        using reference = typename alloc_type::reference;
        using const_referece = typename alloc_type::const_reference;
        using size_type = typename alloc_type::size_type;
        using node_type = __node<value_type>*;

        using node_allocator = typename std::allocator_traits<alloc_type>::template rebind_alloc<__node<value_type>>;
        using alloc_traits = std::allocator_traits<node_allocator>;


        template <typename _K, typename _T>
        class __map_iterator{
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = typename alloc_type::value_type;
            using pointer = typename alloc_type::pointer;
            using reference = typename alloc_type::reference;

            __map_iterator(node_type __n):node_(__n){}
            __map_iterator(const __map_iterator &_oth):node_(_oth.node_){}
            reference operator*(){
                return this->node_->value_;
            }
            
            pointer operator->(){
                return &(this->node_->value_);
            }

            node_type get() const{
                return this->node_;
            }

            __map_iterator& operator++(){
                if(this->node_ == nullptr || this->node_->is_sentinel_){
                    throw std::out_of_range("operator++ out of bounds");
                }
                this->node_ = this->node_->_next_node();

                return *this;
            }

            __map_iterator operator++(int){
                __map_iterator __tmp(*this);
                ++(*this);
                return __tmp;
            };

            __map_iterator& operator--(){
                if(this->node_ == nullptr){
                    throw std::out_of_range("operator-- out of bounds");
                }
                this->node_ = this->node_->_prev_node();

                return *this;
            }

            __map_iterator operator--(int){
                __map_iterator __tmp(*this);
                --(*this);
                return __tmp;
            }

            bool operator==(const __map_iterator &__oth) const{
                if((this->node_ == nullptr && __oth.node_ != nullptr) || (this->node_ != nullptr && __oth.node_ == nullptr)) return false;
                return this->node_ == __oth.node_;
            }

            bool operator!=(const __map_iterator &__oth) const{
                if((this->node_ == nullptr && __oth.node_ != nullptr) || (this->node_ != nullptr && __oth.node_ == nullptr)) return true;
                return this->node_ != __oth.node_;
            }

        private:
            node_type node_;
        };

        using iterator = __map_iterator<_Key, _Value>;
        using const_iterator = __map_iterator<_Key, const _Value>;

        map(){
            this->_init_sentinel();
        }

        map(std::initializer_list<value_type> const &__il){
            this->_init_sentinel();
            this->_construct(__il.begin(), __il.end());
        }

        map(const map &__m){
            this->_init_sentinel();
            this->_construct(__m.begin(), __m.end());
        }

        map(map &&__m){
            this->_init_sentinel();
            this->_move(std::move(__m));
        }

        ~map(){
            this->clear();
            this->_clear_sentinel();
        }

        map& operator=(const map &__oth){
            if(this != &__oth){
                this->_construct(__oth.begin(), __oth.end());
            }

            return *this;
        }

        map& operator=(map &&__oth){

            if(this != &__oth){
                this->_move(std::move(__oth));
            }

            return *this;
        }

        mapped_type& operator[](const key_type &__k){
            node_type __n = this->_find_node(__k);
            
            if(__n == nullptr){
                std::pair<iterator, bool> it = this->insert({__k, mapped_type()});

                __n = it.first.get();
            }

            return __n->get().second;
        }

        mapped_type& at(const _Key &__k) const{
            node_type __n = this->_find_node(__k);

            if(__n == nullptr){
                throw std::out_of_range("s21::map::at key not found");
            }

            
            return __n->get().second;
        }

        bool empty() const{
            return this->size() == 0;
        }

        size_type size() const{
            return this->size_;
        }
        
        size_type max_size(){
            return std::allocator_traits<alloc_type>::max_size(this->alloc_);
        }

        iterator begin() const{
            if(this->empty()){
                return this->end();
            }
            iterator it = iterator(this->root_);
            iterator prev_it = std::prev(it);
            while(prev_it.get() != nullptr){ 
                it = prev_it--;
            }

            return it;
        }

        iterator end() const{
            return iterator(this->sentinel_);
        }
        
        

        void clear(){
            if(!this->empty()){
                while(this->begin() != this->end()){
                    this->erase(this->begin());
                }
                this->root_ = nullptr;
                this->sentinel_->left_ = nullptr;
                this->sentinel_->right_ = nullptr;
                this->sentinel_->parent_ = nullptr;
                this->size_ = 0;
            }
        }

        std::pair<iterator, bool> insert(const value_type &__v){
            if(this->contains(__v.first)){
                return {this->end(), false};
            }

            node_type __n;

            if(this->root_ == nullptr){
                this->root_ = this->_create_node(__v);
                this->root_->left_ = nullptr;
                this->root_->right_ = this->sentinel_;
                this->root_->parent_ = nullptr;

                this->sentinel_->parent_ = this->root_;

                __n = this->root_;
            }else{
                __n = this->_insert_node(iterator(this->root_), __v);
            }

            if(__n != nullptr) this->size_++;

            return {iterator(__n), __n != nullptr};
        }
        
        std::pair<iterator, bool> insert(const _Key &__key, const _Value &__obj){
            return this->insert({__key, __obj});
        }

        std::pair<iterator, bool> insert_or_assign(const _Key &__key, const _Value &__obj){
            node_type __n = this->_find_node(__key);
            if(__n != nullptr){
                __n->value_.second = __obj;
                return {iterator(__n), true};
            }else{
                return this->insert(__key, __obj);
            }
        }

        bool contains(const _Key &__k){
            node_type __n = this->_find_node(__k);
            return __n != nullptr && !__n->is_sentinel_;
        }

        void erase(iterator __pos){
            if(this->empty() || __pos == this->end()){
                throw std::invalid_argument("erase");
            }

            if(__pos.get() == this->root_){
                this->root_ = this->_remove_node(__pos.get());
                return;
            }
            this->_remove_node(__pos.get());

            this->size_--;
        }

        void swap(map &__oth){
            if(this != &__oth){
                this->sentinel_->_replace(__oth.sentinel_);
                std::swap(this->size_, __oth.size_);
                std::swap(this->root_, __oth.root_);
            }
        }

        void merge(map &__oth){
            if(this != &__oth && !__oth.empty()){
                for(iterator it = __oth.begin(); it != __oth.end();){
                    std::pair<iterator, bool> jt = this->insert(*it);

                    if(jt.second){
                        __oth.erase(it);
                        it = __oth.begin();
                    }else{
                        it++;
                    }
                }
            }
        }
        

    protected:
        node_type root_ = nullptr;
        node_type head_ = nullptr;
        node_type sentinel_ = nullptr;
        node_allocator alloc_;
        size_type size_ = 0;

        void _move(map &&__m){
            this->root_ = __m.root_;
            this->sentinel_->left_ = __m.sentinel_->left_;
            this->sentinel_->right_ = __m.sentinel_->right_;
            this->sentinel_->parent_ = __m.sentinel_->parent_;
            this->size_ = __m.size_;
            if(this->sentinel_->parent_ != nullptr) this->sentinel_->parent_->right_ = this->sentinel_;
            
            __m.sentinel_->left_ = nullptr;
            __m.sentinel_->right_ = nullptr;
            __m.sentinel_->parent_ = nullptr;
            __m.root_ = nullptr;
            __m.size_ = 0;
        }

        template <class _InputIter>
        void _construct( _InputIter __f, _InputIter __l ){
            for(_InputIter it = __f; it != __l; it++){
                this->insert(*it);
            }
        }
        void _init_sentinel(){
            this->sentinel_ = _create_node();
            this->sentinel_->is_sentinel_ = true;
        }

        void _clear_sentinel(){
            if(this->sentinel_ != nullptr){
                alloc_traits::destroy(this->alloc_, this->sentinel_);
                alloc_traits::deallocate(this->alloc_, this->sentinel_, 1);
            }
        }

        node_type _create_node(const value_type &__v = value_type(), node_type __parent = nullptr){
            node_type __n = alloc_traits::allocate(this->alloc_, 1);
            alloc_traits::construct(this->alloc_, __n, __v, __parent);
            
            return __n;
        }

        node_type _remove_node(node_type __n){
            node_type __replaced_node = nullptr;

            if(__n->left_ == nullptr && __n->right_ == nullptr){
                __n->_replace_parent_node(nullptr);
                
                __replaced_node = __n->parent_;
            }else if(__n->left_ == nullptr){
                __n->_replace_parent_node(__n->right_);

                __n->right_->parent_ = __n->parent_;

                __replaced_node = __n->right_;
            }else if(__n->right_ == nullptr){
                __n->_replace_parent_node(__n->left_);

                __n->left_->parent_ = __n->parent_;

                __replaced_node = __n->left_;
            }else{
                node_type __next = __n->right_;
                while(__next->left_ != nullptr ) __next = __next->left_;

                if(__n->right_ == __next){
                    __n->left_->parent_ = __n->right_;
                    __n->right_->left_ = __n->left_;
                    if(__n->_has_parent() && __n->_is_left_child()) __n->parent_->left_ = __n->right_;
                    else if(__n->_has_parent() && __n->_is_right_child()) __n->parent_->right_ = __n->right_;

                    __n->right_->parent_ = __n->parent_;

                }else{
                    __n->_replace(__next);
                    __n->_cut();
                }



                __replaced_node = __next;
            }

            this->_clear_node(__n);
            return __replaced_node;
        }

        node_type _find_node(const _Key &_ref, _Compare comp = _Compare()) const{
            node_type __n = this->root_;

            while(__n != nullptr && !__n->is_sentinel_){
                if(comp(__n->value_.first, _ref)){
                    __n = __n->right_;
                }else if(comp(_ref, __n->value_.first)){
                    __n = __n->left_;
                }else{
                    return __n;
                }
            }

            return __n == this->sentinel_ ? nullptr : __n;
        }

        void _clear_node(node_type __n){
            alloc_traits::destroy(this->alloc_, __n);
            alloc_traits::deallocate(this->alloc_, __n, 1);
        }

        node_type _insert_node(iterator __pos, const value_type &__v, _Compare comp = _Compare()){
            if(comp(__v.first, __pos->first)){
                if(__pos.get()->left_ == nullptr){
                    __pos.get()->left_ = this->_create_node(__v, __pos.get());
                    return __pos.get()->left_;
                }else{
                    return _insert_node(iterator(__pos.get()->left_), __v, comp);
                }
            }else{  
                if(__pos.get()->right_ == nullptr || __pos.get()->right_ == this->sentinel_){
                    node_type __tmp = this->_create_node(__v, __pos.get());

                    if(__pos.get()->right_ == this->sentinel_){
                        __tmp->right_ = this->sentinel_;
                        this->sentinel_->parent_ = __tmp;
                    }

                    __pos.get()->right_ = __tmp;

                    return __tmp;
                }else{
                    return _insert_node(iterator(__pos.get()->right_), __v, comp);
                }
            }
        }       
    };
};