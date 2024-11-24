#pragma once

#include "tree.h"

namespace s21
{
    template <typename _T, class _Compare, class _Allocator>
    __tree<_T, _Compare, _Allocator>::__tree(){}

    template <typename _T, class _Compare, class _Allocator>
    __tree<_T, _Compare, _Allocator>::__tree(const __tree &__oth){
        this->_copy(&this->root_, __oth.root_);
        node_pointer __n = this->root_;
        while(__n->right_ != nullptr) __n = __n->right_;
        this->sentinel_ = __n;
    }


    template <typename _T, class _Compare, class _Allocator>
    __tree<_T, _Compare, _Allocator>& 
    __tree<_T, _Compare, _Allocator>::operator=(__tree &&__oth){
        if(this != &__oth){
            this->clear();

            this->root_ = __oth.root_;
            this->sentinel_ = __oth.sentinel_;
            this->size_ = __oth.size_;
            std::swap(this->comp_, __oth.comp_);
            std::__swap_allocator(this->node_alloc_, __oth.node_alloc_);

            __oth.root_ = nullptr;
            __oth.sentinel_ = nullptr;
            __oth.size_ = 0;
        }

        return *this;
    }

    template <typename _T, class _Compare, class _Allocator>
    __tree<_T, _Compare, _Allocator>::~__tree(){
        this->clear();
    }

    template <typename _T, class _Compare, class _Allocator>
    typename __tree<_T, _Compare, _Allocator>::iterator 
    __tree<_T, _Compare, _Allocator>::begin(){
        if(this->root_ == nullptr){
            return iterator(this->sentinel_);
        }
        node_pointer __n = this->root_;
        while(__n != nullptr && __n->left_ != nullptr) __n = __n->left_;
        return iterator(__n);
    }

    template <typename _T, class _Compare, class _Allocator>
    typename __tree<_T, _Compare, _Allocator>::iterator 
    __tree<_T, _Compare, _Allocator>::end(){
        return iterator(this->sentinel_); 
    }

    template <typename _T, class _Compare, class _Allocator>
    typename __tree<_T, _Compare, _Allocator>::const_iterator 
    __tree<_T, _Compare, _Allocator>::begin() const{
        if(this->root_ == nullptr){
            return const_iterator(iterator(this->sentinel_));
        }
        node_pointer __n = this->root_;
        while(__n != nullptr && __n->left_ != nullptr) __n = __n->left_;
        return const_iterator(iterator( __n));
    }

    template <typename _T, class _Compare, class _Allocator>
    typename __tree<_T, _Compare, _Allocator>::const_iterator 
    __tree<_T, _Compare, _Allocator>::end() const{
        return const_iterator(iterator(this->sentinel_));
    }


    template <typename _T, class _Compare, class _Allocator>
    typename __tree<_T, _Compare, _Allocator>::iterator 
    __tree<_T, _Compare, _Allocator>::insert(const_reference __ref){
        this->size_++;
        if(this->sentinel_ == nullptr){
            this->sentinel_ = this->_create_node(value_type());
        }

        if(this->root_ == nullptr){
            this->root_ = this->_create_node(__ref);
            this->root_->right_ = this->sentinel_;
            this->sentinel_->parent_ = this->root_;
            return iterator(this->root_);
        }else{
            return iterator(this->_insert_node(this->root_, __ref));
        }
    }

    template <typename _T, class _Compare, class _Allocator>
    void 
    __tree<_T, _Compare, _Allocator>::erase(iterator __pos){
        node_pointer __r = this->_remove_node(__pos.get());
        if(__pos.get() == this->root_){
            this->root_ = __r;
        }
        this->size_--;
    }

    template <typename _T, class _Compare, class _Allocator>
    template <typename _Key>
    typename __tree<_T, _Compare, _Allocator>::iterator 
    __tree<_T, _Compare, _Allocator>::find(const _Key& __key, value_compare comp_){
        node_pointer __n = this->root_;

        while(__n != nullptr){
            if(comp_(__key, __n->value_)){
                __n = __n->left_;
            }else if(comp_(__n->value_, __key)){
                __n = __n->right_;
            }else{
                break;
            }
        }
        return iterator( __n == nullptr ? this->sentinel_ : __n );
    }
    
    template <typename _T, class _Compare, class _Allocator>
    typename __tree<_T, _Compare, _Allocator>::iterator __tree<_T, _Compare, _Allocator>::lower_bound(const_reference __ref){
        node_pointer __n = this->root_;
        node_pointer __res = nullptr;

        while(__n != nullptr && __n != this->sentinel_){
            if(!this->comp_(__n->value_, __ref)){
                __res = __n;
                __n = __n->left_;
            }else{
                __n = __n->right_;
            }
        }
        
        return iterator(__res == nullptr ? this->sentinel_ : __res);
    }
    
    template <typename _T, class _Compare, class _Allocator>
    typename __tree<_T, _Compare, _Allocator>::iterator __tree<_T, _Compare, _Allocator>::upper_bound(const_reference __ref){
        node_pointer __n = this->root_;
        node_pointer __res = nullptr;

        while(__n != nullptr && __n != this->sentinel_){
            if(this->comp_(__ref, __n->value_)){
                __res = __n;
                __n = __n->left_;
            }else{
                __n = __n->right_;
            }
        }

        return iterator(__res == nullptr ? this->sentinel_ : __res);
    }

    template <typename _T, class _Compare, class _Allocator>
    void 
    __tree<_T, _Compare, _Allocator>::replace(iterator l, iterator r){
        this->_replace_nodes(l.get(), r.get());
    }

    template <typename _T, class _Compare, class _Allocator>
    typename __tree<_T, _Compare, _Allocator>::size_type 
    __tree<_T, _Compare, _Allocator>::count(const_reference __ref){
        size_type __count = 0;
        iterator __lb = this->lower_bound(__ref);
        if(__lb != this->end() && *__lb == __ref){
            for(iterator __ub = this->upper_bound(__ref); __lb != __ub; __lb++, __count++);
        }
        return __count;
    }
    
    template <typename _T, class _Compare, class _Allocator>
    typename __tree<_T, _Compare, _Allocator>::size_type 
    __tree<_T, _Compare, _Allocator>::size() const{
        return this->size_;
    }

    template <typename _T, class _Compare, class _Allocator>
    typename __tree<_T, _Compare, _Allocator>::size_type 
    __tree<_T, _Compare, _Allocator>::max_size() const{
        return std::allocator_traits<__node_alloc>::max_size(this->node_alloc_);
    }   

    template <typename _T, class _Compare, class _Allocator>
    void 
    __tree<_T, _Compare, _Allocator>::clear(){
        this->_clear_node(this->root_);
        this->sentinel_ = this->root_ = nullptr;
        this->size_ = 0;
    }

    template <typename _T, class _Compare, class _Allocator>
    void 
    __tree<_T, _Compare, _Allocator>::display(){
        this->_display_node(this->root_);
    }

    template <typename _T, class _Compare, class _Allocator>    
    void 
    __tree<_T, _Compare, _Allocator>::_copy(node_pointer *__src, node_pointer __dst, node_pointer __parent){
        if(__dst == nullptr){
            return;
        }

        *__src = this->_create_node(__dst->value_, __parent);
        this->_copy(&((*__src)->left_), __dst->left_, *__src);
        this->_copy(&((*__src)->right_), __dst->right_, *__src);
    }

    template <typename _T, class _Compare, class _Allocator>
    void 
    __tree<_T, _Compare, _Allocator>::_display_node(node_pointer node, const std::string& prefix, bool isLeft)
    {
        if( node != nullptr )
        {
            std::cout << prefix;

            std::cout << (isLeft ? "├──" : "└──" );

            // print the value of the node
            std::cout << node->value_ << std::endl;

            // enter the next tree level - left and right branch
            _display_node(node->left_, prefix + (isLeft ? "│   " : "    "), true);
            _display_node(node->right_, prefix + (isLeft ? "│   " : "    "), false);
        }
    }

    template <typename _T, class _Compare, class _Allocator>    
    template <class _InputIter>
    void 
    __tree<_T, _Compare, _Allocator>::_construct(_InputIter __f, _InputIter __l){
        while(__f != __l){
            this->insert(*__f);
            __f++;

        }
    }

    template <typename _T, class _Compare, class _Allocator>
    typename __tree<_T, _Compare, _Allocator>::size_type 
    __tree<_T, _Compare, _Allocator>::_calc_size(node_pointer __n, size_type __sz){
        if(__n == nullptr){
            return __sz;
        }
        size_type _l_size = this->_calc_size(__n->left_, __sz + 1);
        size_type _r_size = this->_calc_size(__n->right_, __sz + 1);
        
        return _l_size + _r_size;
    }

    template <typename _T, class _Compare, class _Allocator>
    typename __tree<_T, _Compare, _Allocator>::node_pointer 
    __tree<_T, _Compare, _Allocator>::_remove_node(node_pointer __n){
        node_pointer __replaced = nullptr;

        if(__n->right_ == nullptr && __n->left_ == nullptr){
            __n->_change_node_for_parent(nullptr);
        }else{
            node_type __tmp = *__n;

            if(__n->right_ && __n->right_ != this->sentinel_){
                __replaced = __n->right_;
                while(__replaced->left_) __replaced = __replaced->left_;

            }else{
                if(__n->left_){

                    __replaced = __n->left_;
                    while(__replaced != nullptr && __replaced->right_ != nullptr) __replaced = __replaced->right_;
                }else{
                    __replaced = this->sentinel_;
                }
            }

            this->_replace_nodes(__replaced, __n);

            if(__n->right_ != nullptr){
                __n->_change_node_for_parent(__n->right_);
            }else{
                __n->_change_node_for_parent(__n->left_);

            }
        }

        this->_destroy_node(__n);

        return __replaced;
    }

    template <typename _T, class _Compare, class _Allocator>
    void __tree<_T, _Compare, _Allocator>::swap(__tree& __oth){
        if(this != &__oth){
            std::swap(this->root_, __oth.root_);
            std::swap(this->sentinel_, __oth.sentinel_);
            std::swap(this->size_, __oth.size_);
            std::swap(this->comp_, __oth.comp_);
            std::__swap_allocator(this->node_alloc_, __oth.node_alloc_);
        }
    }


    template <typename _T, class _Compare, class _Allocator>
    void 
    __tree<_T, _Compare, _Allocator>::_replace_nodes(node_pointer __lhs, node_pointer __rhs) {
        if (__lhs == __rhs) {
            return; 
        }

        if (__lhs->parent_ == __rhs || __rhs->parent_ == __lhs) {
            node_pointer __lw = __lhs;
            node_pointer __up = __rhs;

            if (__lw->left_ == __up || __lw->right_ == __up) {
                __lw = __rhs;
                __up = __lhs;
            }

            if(__up == this->root_){
                this->root_ = __lw;
            }

            node_type __tmp = *__up; 

            __up->left_ = __lw->left_;
            __up->right_ = __lw->right_;
            __up->parent_ = __lw;

            if (__up->right_ != nullptr) __up->right_->parent_ = __up;
            if (__up->left_ != nullptr) __up->left_->parent_ = __up;

            if (__tmp.left_ == __lw) {
                __lw->left_ = __up;
                __lw->right_ = __tmp.right_;
                if (__lw->right_) __lw->right_->parent_ = __lw;
            } else {
                __lw->right_ = __up;
                __lw->left_ = __tmp.left_;
                if (__lw->left_) __lw->left_->parent_ = __lw;
            }
            __lw->parent_ = __tmp.parent_;
            if (__tmp.parent_ != nullptr) {
                if (__tmp.parent_->left_ == __up) {
                    __tmp.parent_->left_ = __lw;
                } else {
                    __tmp.parent_->right_ = __lw;
                }
            }

        } else {  
            node_type __tmp = *__lhs;
            node_type __lhs_parent = __lhs->parent_ != nullptr ? *(__lhs->parent_) : node_type();
            node_type __rhs_parent = __rhs->parent_ != nullptr ? *(__rhs->parent_) : node_type();
            

            if (__lhs == this->root_) {
                this->root_ = __rhs;  
            }else if(__rhs == this->root_){
                this->root_ = __lhs;
            }
            __lhs->left_ = __rhs->left_;
            __lhs->right_ = __rhs->right_;
            __lhs->parent_ = __rhs->parent_;

            if (__lhs->left_ != nullptr) {
                __lhs->left_->parent_ = __lhs;
            }
            if (__lhs->right_ != nullptr) {
                __lhs->right_->parent_ = __lhs;
            }
            if (__lhs->parent_ != nullptr) {
                if (__rhs_parent.left_ == __rhs) {
                    __lhs->parent_->left_ = __lhs;
                } else {
                    __lhs->parent_->right_ = __lhs;
                }
            }

            __rhs->left_ = __tmp.left_;
            __rhs->right_ = __tmp.right_;
            __rhs->parent_ = __tmp.parent_;

            if (__rhs->left_ != nullptr) {
                __rhs->left_->parent_ = __rhs;
            }
            if (__rhs->right_ != nullptr) {
                __rhs->right_->parent_ = __rhs;
            }
            if (__tmp.parent_ != nullptr) {
                if (__lhs_parent.left_ == __lhs) {
                    __rhs->parent_->left_ = __rhs;
                } else {
                    __rhs->parent_->right_ = __rhs;
                }
            }
        }
    }


    template <typename _T, class _Compare, class _Allocator>
    int 
    __tree<_T, _Compare, _Allocator>::_distance_between(node_pointer __lhs, node_pointer __rhs){
        if(__lhs == __rhs){
            return 0;
        }else{
            node_pointer _lca = this->_find_lca(this->root_, __lhs, __rhs);

            if(!_lca){
                return -1;
            }

            return this->_depth_from_root(_lca, __lhs) + this->_depth_from_root(_lca, __rhs);
        }
    }

    template <typename _T, class _Compare, class _Allocator>
    int 
    __tree<_T, _Compare, _Allocator>::_depth_from_root(node_pointer __root, node_pointer __n, int __depth){
        if(__root == nullptr){
            return -1;
        }

        if(__root == __n){
            return __depth;
        }

        int _l_depth = this->_depth_from_root(__root->left_, __n, __depth + 1);
        if(_l_depth != -1){
            return _l_depth;
        }

        return this->_depth_from_root(__root->right_, __n, __depth + 1);
    }

    template <typename _T, class _Compare, class _Allocator>
    typename __tree<_T, _Compare, _Allocator>::node_pointer 
    __tree<_T, _Compare, _Allocator>::_find_lca(node_pointer __root, node_pointer __lhs, node_pointer __rhs){
        if(__root == nullptr || __root == __lhs || __root == __rhs){
            return __root;
        }

        node_pointer _left_lca = this->_find_lca(__root->left_, __lhs, __rhs);
        node_pointer _right_lca = this->_find_lca(__root->right_, __lhs, __rhs);

        if(_left_lca && _right_lca){
            return __root;
        }

        return (_left_lca != nullptr) ?  _left_lca : _right_lca;
    }

    template <typename _T, class _Compare, class _Allocator>
    void 
    __tree<_T, _Compare, _Allocator>::_clear_node(node_pointer __n){
        if(__n != nullptr){
            this->_clear_node(__n->left_);
            this->_clear_node(__n->right_);
            this->_destroy_node(__n);
        }
    }

    template <typename _T, class _Compare, class _Allocator>
    typename __tree<_T, _Compare, _Allocator>::node_pointer 
    __tree<_T, _Compare, _Allocator>::_insert_node(node_pointer __n, const_reference __ref, value_compare comp_){
        if(comp_(__ref, __n->value_)){
            if(__n->left_ == nullptr){
                __n->left_ = this->_create_node(__ref, __n);
                return __n->left_;
            }else{
                return this->_insert_node(__n->left_, __ref);
            }
        }else{
            if(__n->right_ == nullptr){
                __n->right_ = this->_create_node(__ref, __n);
                return __n->right_;
            }else if(__n->right_ == this->sentinel_){
                __n->right_ = this->_create_node(__ref, __n);
                __n->right_->right_ = this->sentinel_;
                this->sentinel_->parent_ = __n->right_;
                return __n->right_;
            }else{
                return this->_insert_node(__n->right_, __ref);
            }
        }   
    }

    template <typename _T, class _Compare, class _Allocator>
    typename __tree<_T, _Compare, _Allocator>::node_pointer 
    __tree<_T, _Compare, _Allocator>::_find_node(const_reference __ref, _Compare comp){
        node_pointer __n = this->root_;

        while(__n != nullptr){
            if(comp(__ref, __n->value_)){
                __n = __n->left_;
            }else if(comp(__n->value_, __ref)){
                __n = __n->right_;
            }else{
                break;
            }
        }
        
        return __n == nullptr ? this->sentinel_ : __n;
    }

    template <typename _T, class _Compare, class _Allocator>
    typename __tree<_T, _Compare, _Allocator>::node_pointer 
    __tree<_T, _Compare, _Allocator>::_create_node(const_reference __ref, node_pointer __parent){
        node_pointer __n = __node_traits::allocate(this->node_alloc_, 1);
        __node_traits::construct(this->node_alloc_, __n, __ref, __parent);
        return __n;
    }

    template <typename _T, class _Compare, class _Allocator>
    void
    __tree<_T, _Compare, _Allocator>::_destroy_node(node_pointer __n){
        __node_traits::destroy(this->node_alloc_, __n);
        __node_traits::deallocate(this->node_alloc_, __n, 1);
    }

}