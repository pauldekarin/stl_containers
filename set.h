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

        __node(const _T &__value): value_(__value){}
    };

    using __node_allocator = typename std::allocator_traits<_Allocator>::template rebind_alloc<__node>;
    using __alloc_traits = std::allocator_traits<__node_allocator>;



    using alloc_type = _Allocator;
    using value_type = _T;
    using reference = typename alloc_type::reference;
protected:
    __node *root_ = nullptr;
    __node_allocator alloc_;

public:


    __tree(const _T &__value):root_(_create_node(__value)){
        
    }

    __node* insert(const _T &__value, _Compare comp = _Compare()){
        if(this->root_ == nullptr){
            this->root_ = _create_node(__value);
        }else{
            _insert_node(this->root_, __value);
        }
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

private:
    void _insert_node(__node *_node, const _T &_value, const _Compare comp = _Compare()){
        if(comp(_value, _node->value_)){
            if(_node->left_ != nullptr){
                _node->left_ = _create_node(_value, _node);
            }else{
                _node->left_ = _insert_node(_node->left_, _value);
            }
        }else{
            if(_node->right_ != nullptr){
                _node->right_ = _create_node(_value, _node);
            }else{
                _node->right_ = _insert_node(_node->right_, _value);
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
};

template<typename _T, typename _Node>
class SetIterator{
private:
    _Node *node_;

public:
    SetIterator(_Node *__node):node_(__node){

    }

    _T& operator*() const{
        return node_->value_;
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
        using iterator = SetIterator<value_type, typename __tree<value_type, _Compare, allocator_type>::__node>;
    protected:
        __tree<_Key, _Compare, _Allocator> *tree_ = nullptr;
        allocator_type alloc_;

    private:

    public:
        set(){

        }
        set(std::initializer_list<value_type> const &__il){
            
        }
        set(const set &__oth){
            
        }
        set(set &&__oth){
            
        }
        ~set(){
            
        }
        set& operator=(set &&__oth){
            
        }

        bool empty(){
            
        }
        size_type size(){
            
        }
        size_type max_size(){
            return std::allocator_traits<allocator_type>::max_size(this->alloc_);
        }

        void insert(const _Key& __value){
            if(tree_ == nullptr){
                tree_ = new __tree(__value);
            }
        }

        iterator find(const _Key &__value){
            return iterator(this->tree_->find(__value));
        }

        iterator begin(){
            
        }
    };
}