#pragma once

#include <iostream>
#include <memory>
#include <map>
#include <initializer_list>
#include <utility>
#include "pair.h"


namespace s21{
    template <typename _Key, typename _Value, class _Compare = std::less<std::pair<_Key, _Value>>, class _Allocator = std::allocator<std::pair<const _Key, _Value>> >
    class map{
    public:
        template <typename _T>
        struct __node{
            __node *left_ = nullptr;
            __node *right_ = nullptr;
            bool is_senitinel_ = false;
            _T value_;

            __node(_T __t):value_(__t){}
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
            using value_type = value_type;
            using difference_type = typename alloc_type::difference_type;
            using pointer = typename alloc_type::pointer;
            using reference = reference;

            __map_iterator(node_type __n):node_(__n){}

            reference operator*(){
                return this->node_->value_;
            }
            
            pointer operator->(){
                return &(this->node_->value_);
            }

            node_type get() const{
                return this->node_;
            }
        
        private:
            node_type node_;
        };

        using iterator = __map_iterator<_Key, _Value>;
        using const_iterator = __map_iterator<_Key, const _Value>;

        map(){

        }

        map(std::initializer_list<value_type> const &__il){
            
        }

        map(const map &__m){

        }

        map(map &&__m){

        }

        ~map(){

        }

        map& operator=(const map &__oth){
            
        }

        map& operator=(map &&__oth){

        }

        void clear(){

        }

        std::pair<iterator, bool> insert(const value_type &__v){
            if(this->root_ == nullptr){
                this->root_ = this->_create_node(__v);
                this->root_->left_ = nullptr;
                this->root_->right_ = this->sentinel_;

                this->sentinel_->left_ = this->root_;

                return {iterator(this->root_), true};
            }

            node_type __n = this->_insert_node(iterator(this->root_), __v);

            return {iterator(__n), true};
        }

    protected:
        node_type root_ = nullptr;
        node_type sentinel_ = nullptr;
        node_allocator alloc_;

        void _init_sentinel(){
            this->sentinel_ = _create_node(0);
            this->sentinel_->is_senitinel_ = true;
        }

        void _clear_sentinel(){

        }

        node_type _create_node(const value_type &__v){
            node_type __n = alloc_traits::allocate(this->alloc_, 1);
            alloc_traits::construct(this->alloc_, __n, __v);
            
            return __n;
        }

        void _clear_node(node_type __n){
            alloc_traits::destroy(this->alloc_, __n);
            alloc_traits::deallocate(this->alloc_, __n, 1);
        }

        node_type _insert_node(iterator __pos, const value_type &__v, _Compare comp = _Compare()){
            if(comp(__v, *__pos)){
                if(__pos.get()->left_ == nullptr){
                    __pos.get()->left_ = this->_create_node(__v);
                    return __pos.get()->left_;
                }else{
                    return _insert_node(iterator(__pos.get()->left_), __v, comp);
                }
            }else{  
                if(__pos.get()->right_ == nullptr){
                    __pos.get()->right_ = this->_create_node(__v);
                    return __pos.get()->right_;
                }else{
                    return _insert_node(iterator(__pos.get()->right_), __v, comp);
                }
            }
        }       
    };
};