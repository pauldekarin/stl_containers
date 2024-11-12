#pragma once

#include <set>
#include <memory>
#include <iostream>
#include <initializer_list>


template<typename _T, class _Compare = std::less<_T>, class _Allocator = std::allocator<_T>>
class __tree{
public:
    struct __node{
        _T value_;

        __node *left_ = nullptr;
        __node *right_ = nullptr;
        __node *parent_ = nullptr;

        __node(const _T &__value): value_(__value){};
        __node(const __node& __oth){
            this->left_ = __oth.left_;
            this->right_ = __oth.right_;
            this->parent_ = __oth.parent_;
            this->value_ = __oth.value_;
        }
        __node(__node&& __oth){
            if(this != &__oth){
                this->left_ = __oth.left_;
                this->right_ = __oth.right_;
                this->parent_ = __oth.parent_;
                this->value_ = __oth.value_;

                __oth.left_ = nullptr;
                __oth.right_ = nullptr;
                __oth.parent_ = nullptr;
            }
        }

        bool equal(const __node &__oth){
            return (
                __oth.left_ == this-->left_ && 
                __oth.right_ == this->right_ &&
                __oth.parent_ == this->parent_ && 
                __oth.value_ == this->value_
            );
        }

        bool operator==(const __node &__oth){
            return this->equal(__oth);
        }
        bool operator!=(const __node &__oth){
            return !this->equal(__oth);
        }
    };

    using __node_allocator = typename std::allocator_traits<_Allocator>::template rebind_alloc<__node>;
    using __alloc_traits = std::allocator_traits<__node_allocator>;



    using alloc_type = _Allocator;
    using value_type = _T;
    using reference = typename alloc_type::reference;
    using size_type = typename alloc_type::size_type;

protected:
    __node *root_ = nullptr;
    __node_allocator alloc_;
    size_type size_ = 0;

public:

    __tree() = default;
    __tree(const _T &__value):root_(_create_node(__value)){
        
    }
    ~__tree(){
        this->_clear(this->root_);
    }

    void insert(const _T &__value, _Compare comp = _Compare()){
        if(this->root_ == nullptr){
            this->root_ = _create_node(__value);
        }else{
            _insert_node(this->root_, __value);
        }
        this->size_++;
    }

    void remove(__node *__n){
        if(__n != nullptr){
            if(__n->left_ != nullptr) __n->left_->parent_ = __n->parent_;
            if(__n->right_ != nullptr) __n->right_->parent_ = __n->parent_;
            if(__n->parent_ != nullptr){
                if(__n->parent_->left_ == __n){
                    __n->parent_->left_ = __n;
                }else{
                    __n->parent_->right_ = __n;
                }
            }
            _destroy_node(__n);
            --this->size_;
        }
    }

    __node *lower_bound(const _T &__t, _Compare comp = _Compare()){
        __node *__n = this->root_;
       if(__n != nullptr){
            while(__n != nullptr && __n->left_ != nullptr) __n = __n->left_;
            while(__n != nullptr && comp(__n->value_, __t)) {
                __n = this->_next_node(__n);
            }
       }
       return __n;
    }


    __node* find(const _T &__value, _Compare comp = _Compare()){
        __node *__current = this->root_;

        while(__current){
            if(comp(__value, __current->value_)){
                __current = __current->left_;
            }else if(comp(__current->value_, __value)){
                __current = __current->right_;
            }else{
                return __current;
            }
        }
        return nullptr;
    }

    __node* get_root() const noexcept{
        return this->root_;
    }
    
    size_type size() const{
        return this->size_;
    }

private:
    void _insert_node(__node *_node, const _T &_value, const _Compare comp = _Compare()){
        if(comp(_value, _node->value_)){
            if(_node->left_ == nullptr){
                _node->left_ = _create_node(_value, _node);
            }else{
                _insert_node(_node->left_, _value);
            }
        }else{
            if(_node->right_ == nullptr){
                _node->right_ = _create_node(_value, _node);
            }else{              
                _insert_node(_node->right_, _value);
            }
        }
    }

    __node* _create_node(const _T &_value, __node *_parent = nullptr){
        __node *__n = __alloc_traits::allocate(this->alloc_, 1);
        __alloc_traits::construct(this->alloc_, __n, _value);
        __n->parent_ = _parent;
        return __n;
    }

    void _destroy_node(__node *__n){
        __alloc_traits::destroy(this->alloc_, __n);
        __alloc_traits::deallocate(this->alloc_, __n, 1);
    }

    void _clear(__node *__n){
        if(__n != nullptr){
            _clear(__n->left_);
            _clear(__n->right_);
            _destroy_node(__n);
        }
    }

    __node *_next_node(__node *__n){
        if (__n->right_ != nullptr) {
            __n = __n->right_;
            while (__n->left_ != nullptr) {
                __n = __n->left_;
            }
        } else {
            __node* __p = __n->parent_;
            while (__p != nullptr && __n == __p->right_) {
                __n = __p;
                __p = __p->parent_;
            }
            __n = __p;
        }

        return __n;
    }
};

template<typename _T, typename _Node>
class SetIterator{
protected:
    _Node *node_;
public:

    SetIterator(_Node *__node):node_(__node){

    }
    ~SetIterator(){

    }
    _Node* get() const{
        return this->node_;
    }

    _T operator*() const{
        if(this->node_ == nullptr){
            return _T{};
        }
        return node_->value_;
    }

    SetIterator& operator++() {
        if (this->node_ == nullptr) {
            throw std::runtime_error("SetIterator<_T, _Key>: Attempted to increment past end of set");
        }

        if (this->node_->right_ != nullptr) {
            this->node_ = this->node_->right_;
            while (this->node_->left_ != nullptr) {
                this->node_ = this->node_->left_;
            }
        } else {
            _Node* parent = this->node_->parent_;
            while (parent != nullptr && this->node_ == parent->right_) {
                this->node_ = parent;
                parent = parent->parent_;
            }
            this->node_ = parent;
        }

        return *this;
    }

    SetIterator operator++(int){
        SetIterator __tmp(this->node_);
        ++(*this);
        return __tmp;
    }

    SetIterator& operator--(){
        if(this->node_ == nullptr){
            throw std::runtime_error("SetIterator<_T,_Key> Segmentation fault operator--");
        }

        if(this->node_->left_ != nullptr){
            this->node_ = this->node_->left_;
            while(this->node_->right_ != nullptr) this->node_ = this->node_->right_;
        }else{
            if(this->node_->parent_ != nullptr && this->node_->parent_->right_ == this->node_){
                this->node_ = this->node_->parent_;
            }else{
                this->node_ = this->node_->left_;
            }
        }

        return *this;
    }

    SetIterator operator--(int){
        SetIterator __tmp(this->node_);
        --(*this);
        return __tmp;
    }

    bool operator==(const SetIterator &__oth){
        if(__oth.node_ == nullptr && this->node_ == nullptr) return true;
        if(__oth.node_ == nullptr || this->node_ == nullptr) return false;
        return __oth.node_ == this->node_;
    }

    bool operator!=(const SetIterator &__oth){
        if(__oth.node_ == nullptr && this->node_ == nullptr) return false;
        if(__oth.node_ == nullptr || this->node_ == nullptr) return true;
        return __oth.node_ != this->node_;
    }
};

namespace s21{
    template <typename _Key, class _Compare = std::less<_Key>, class _Allocator = std::allocator<_Key> >
    class set{
    public:

        using key_type = _Key;
        using value_type = key_type;
        using allocator_type = _Allocator;
        using reference = typename allocator_type::reference;
        using const_reference = typename allocator_type::const_reference;
        using size_type = typename allocator_type::size_type;
        using tree_type = __tree<value_type, _Compare, allocator_type>;
        using tree_allocator = typename std::allocator_traits<allocator_type>::template rebind_alloc<tree_type>;
        using __alloc_traits = std::allocator_traits<tree_allocator>;

        using iterator = SetIterator<value_type, typename tree_type::__node>;
        
        class reverse_iterator: public iterator{
            public:
            reverse_iterator(typename tree_type::__node *__n):iterator(__n){}
            reverse_iterator(const reverse_iterator &__oth):iterator(__oth.node_){}

            reverse_iterator& operator++(){
                
            }
            reverse_iterator operator++(int){
                reverse_iterator __tmp(*this);
                this->node_ = (--iterator(this->node_)).get();
                return __tmp;
            }
        };

    protected:
        tree_type *tree_ = nullptr;
        tree_allocator alloc_;

    private:

    public:
        set():
            tree_(__alloc_traits::allocate(this->alloc_, 1))
        {

        }
        set(std::initializer_list<value_type> const &__il):
            tree_(__alloc_traits::allocate(this->alloc_, 1))
        {   
            for(auto it = __il.begin(); it != __il.end(); it++){
                this->tree_->insert(*it);
            }
        }
        set(const set &__oth){
            
        }
        set(set &&__oth){
            
        }
        ~set(){
            this->clear();
            __alloc_traits::deallocate(this->alloc_, this->tree_, 1);
        }

        void clear(){
        }
        set& operator=(set &&__oth){
            
        }

        inline bool empty() const noexcept{
            return this->size() == 0;
        }
        size_type size(){
            return this->tree_->size();
        }
        size_type max_size(){
            return std::allocator_traits<allocator_type>::max_size(this->alloc_);
        }

        void insert(const _Key& __value){
            if(this->tree_->find(__value) == nullptr){
                this->tree_->insert(__value);
            }
        }

        void erase(_Key &__k){
            this->tree_->remove(this->tree_->find(__k));
        }

        void erase(iterator __it){
            if(__it.get() == nullptr){
                throw std::invalid_argument("s21::set segmentation fault erase");
            }
            this->tree_->remove(this->tree_->find(*__it));
        }

        void erase(iterator __f, iterator __l){
            while(__f++ != __l){
                this->erase(__f);
            }
        }


        iterator find(const _Key &__value){
            return iterator(this->tree_->find(__value));
        }

        iterator begin(){
            typename tree_type::__node *__n = this->tree_->get_root();
            while(__n != nullptr &&  __n->left_ != nullptr) __n = __n->left_;
            return iterator(__n);
        }

        iterator end(){
            return iterator(nullptr);
        }

        reverse_iterator rbegin(){
            typename tree_type::__node *__n = this->tree_->get_root();
            while(__n != nullptr && __n->right_ != nullptr) __n = __n->right_;
            return reverse_iterator(__n);
        }

        reverse_iterator rend(){
            return reverse_iterator(nullptr);
        }

        iterator lower_bound(const _Key &__k){
            return iterator(this->tree_->lower_bound(__k));
        }
    };
}