#pragma once
#include <memory>
#include <iterator>
#include <set>
#include <cstdlib>
#include <ctime>
#include <map>
#include <vector>
#include <string>
namespace s21
{  
    template <typename _T>
    class __tree_iterator{  
    public:
        typedef _T* pointer;
        typedef _T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef _T& reference;
        typedef const _T& const_reference;
        typedef std::size_t size_type;

        template <typename _U>
        struct __node{
            typedef _U value_type;

            __node *left_ = nullptr;
            __node *right_ = nullptr;
            __node *parent_ = nullptr;
            
            value_type value_;
            __node():value_(value_type()){}
            __node(const_reference __ref):value_(__ref){}

            __node(const_reference __ref, __node *__parent):value_(__ref), parent_(__parent){}

            __node (const __node &__n):left_(__n.left_), right_(__n.right_), parent_(__n.parent_), value_(__n.value_){}

            inline bool operator==(const __node &__n){ return this->left_ == __n.right_ && this->right_ == __n.left_ && this->parent_ == __n.parent_; }

            inline bool operator!=(const __node &__n){ return !(*this == __n); }

            inline bool operator==(const __node *__n){ return *this == *__n; }

            inline bool operator!=(const __node *__n){ return *this != *__n; }

            inline bool _has_left_child(){ return this->left_ != nullptr; }

            inline bool _has_right_child(){ return this->right_ != nullptr; }

            inline bool _has_parent(){ return this->parent_ != nullptr; }

            inline bool _is_left_child(){ return this->_has_parent() && this->parent_->left_ == this; }

            inline bool _is_right_child(){ return this->_has_parent() && this->parent_->right_ == this; }

            void _change_node_for_parent(__node *__new_node = nullptr){
                if(this->_is_left_child()){
                    this->parent_->left_ = __new_node;
                }else if(this->_is_right_child()){
                    this->parent_->right_ = __new_node;
                }

                if(__new_node != nullptr){
                    __new_node->parent_ = this->parent_;
                }
            }
            
        };

        __node<value_type> *n_ = nullptr;

        __tree_iterator(){}
        __tree_iterator(__node<value_type> *__n):n_(__n){}
        __tree_iterator(const __tree_iterator &__it):n_(__it.n_){}
        template <typename _R>
        __tree_iterator(const __tree_iterator<_R> &__it):n_(reinterpret_cast<__node<value_type>*>(__it.n_)){
            
        }
        ~__tree_iterator(){}


        __tree_iterator& operator++(){
            if(this->n_ == nullptr){
                throw std::out_of_range("");
            }

            if(this->n_->right_ != nullptr){
                this->n_ = this->n_->right_;
                while(this->n_->left_ != nullptr) this->n_ = this->n_->left_;
            }else{
                __node<value_type> *__p = this->n_->parent_;
                while(__p != nullptr && __p->right_ == this->n_){
                    this->n_ = __p;
                    __p = __p->parent_;
                }
                this->n_ = __p;
            }

            return *this;
        }

        __tree_iterator operator--(int){
            __tree_iterator __tmp(*this);
            --(*this);
            return __tmp;
        }

        __tree_iterator& operator--(){
            if(this->n_ == nullptr){
                throw std::out_of_range("");
            }   

            if(this->n_->left_ != nullptr){
                this->n_ = this->n_->left_;
                while(this->n_->right_ != nullptr) this->n_ = this->n_->right_;
            }else{
                __node<value_type> *__p = this->n_->parent_;
                while(__p != nullptr && __p->left_ == this->n_){
                    this->n_ = __p;
                    __p = __p->parent_;
                }
                this->n_ = __p;
            }

            return *this;
        }

        __tree_iterator operator++(int){
            __tree_iterator __tmp(*this);
            ++(*this);
            return __tmp;
        }

        bool operator==(const __tree_iterator &__it){
            return this->n_ == __it.n_;
        }

        bool operator!=(const __tree_iterator &__it){
            return this->n_ != __it.n_;
        }

        __node<value_type>* get(){
            return this->n_;
        }

        reference operator*(){
            return this->n_->value_;
        }
        pointer operator->(){
            return &(this->n_->value_);
        }
    };

    template <typename _T, class _Compare = std::less<_T>, class _Allocator = std::allocator<_T>> 
    class __tree{
    public:
        typedef _Allocator allocator_type;
        typedef _Compare value_compare;
        typedef typename allocator_type::value_type value_type;
        typedef typename std::allocator_traits<allocator_type>::template rebind_alloc<value_type> __val_alloc;
        typedef std::allocator_traits<__val_alloc> __val_traits;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::size_type size_type;
        typedef __tree_iterator<value_type> iterator;
        typedef __tree_iterator<const value_type> const_iterator;
        typedef typename iterator::template __node<value_type> node_type;
        typedef node_type*  node_pointer;

        typedef typename std::allocator_traits<allocator_type>::template rebind_alloc<node_type> __node_alloc;
        typedef std::allocator_traits<__node_alloc> __node_traits;

    protected:
        __node_alloc node_alloc_;
        _Compare comp_;
        node_pointer root_ = nullptr;
        node_pointer sentinel_ = nullptr;
        size_type size_ = 0;

    public:    
        __tree(){
        }

        __tree(const __tree &__oth){
            this->_copy(&this->root_, __oth.root_);
            node_pointer __n = this->root_;
            while(__n->right_ != nullptr) __n = __n->right_;
            this->sentinel_ = __n;
        }

        __tree& operator=(__tree &&__oth){
            if(this != &__oth){
                this->root_ = __oth.root_;
                this->sentinel_ = __oth.sentinel_;
                this->size_ = __oth.size_;

                __oth.root_ = nullptr;
                __oth.sentinel_ = nullptr;
                __oth.size_ = 0;
            }

            return *this;
        }

        ~__tree(){
            this->clear();
        }

        iterator begin(){
            if(this->root_ == nullptr){
                return iterator(this->sentinel_);
            }
            node_pointer __n = this->root_;
            while(__n != nullptr && __n->left_ != nullptr) __n = __n->left_;
            return iterator(__n);
        }

        iterator end(){
            return iterator(this->sentinel_); 
        }

        const_iterator begin() const{
            if(this->root_ == nullptr){
                return const_iterator(iterator(this->sentinel_));
            }
            node_pointer __n = this->root_;
            while(__n != nullptr && __n->left_ != nullptr) __n = __n->left_;
            return const_iterator(iterator( __n));
        }

        const_iterator end() const{
            return const_iterator(iterator(this->sentinel_));
        }


        iterator insert(const_reference __ref){
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

        void erase(iterator __pos){
            node_pointer __r = this->_remove_node(__pos.get());
            if(__pos.get() == this->root_){
                this->root_ = __r;
            }
            this->size_--;
        }

        template <typename _Key>
        iterator find(const _Key& __key, value_compare comp_ = value_compare()){
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



        void replace(iterator l, iterator r){
            this->_replace_nodes(l.get(), r.get());
        }

        size_type size() const{
            return this->size_;
        }

        size_type max_size() const{
            return std::allocator_traits<__node_alloc>::max_size(this->node_alloc_);
        }   

        void clear(){
            this->_clear_node(this->root_);
            this->sentinel_ = this->root_ = nullptr;
            this->size_ = 0;
        }

        void display(){
            this->_display_node(this->root_);
        }
    // private:
    public:
        void _copy(node_pointer *__src, node_pointer __dst, node_pointer __parent = nullptr){
            if(__dst == nullptr){
                return;
            }

            *__src = this->_create_node(__dst->value_, __parent);
            this->_copy(&((*__src)->left_), __dst->left_, *__src);
            this->_copy(&((*__src)->right_), __dst->right_, *__src);
        }

        void _display_node(node_pointer node, const std::string& prefix = "", bool isLeft = true)
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
        template <class _InputIter>
        void _construct(_InputIter __f, _InputIter __l){
            while(__f != __l){
                this->insert(*__f);
                __f++;

            }
        }

        size_type _calc_size(node_pointer __n, size_type __sz = 0){
            if(__n == nullptr){
                return __sz;
            }
            size_type _l_size = this->_calc_size(__n->left_, __sz + 1);
            size_type _r_size = this->_calc_size(__n->right_, __sz + 1);
            
            return _l_size + _r_size;
        }

        node_pointer _remove_node(node_pointer __n){
            node_pointer __replaced = nullptr;

            if(__n->right_ == nullptr && __n->left_ == nullptr){
                __n->_change_node_for_parent(nullptr);
            }else{
                node_type __tmp = *__n;

                if(__n->right_ && __n->right_ != this->sentinel_){
                    __replaced = __n->right_;
                    while(__replaced->left_) __replaced = __replaced->left_;

                }else{
                    __replaced = __n->left_;
                    while(__replaced->right_) __replaced = __replaced->right_;
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

       

        void _replace_nodes(node_pointer __lhs, node_pointer __rhs) {
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


        int _distance_between(node_pointer __lhs, node_pointer __rhs){
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
        
        int _depth_from_root(node_pointer __root, node_pointer __n, int __depth = 0){
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

        node_pointer _find_lca(node_pointer __root, node_pointer __lhs, node_pointer __rhs){
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

        void _clear_node(node_pointer __n){
            if(__n != nullptr){
                this->_clear_node(__n->left_);
                this->_clear_node(__n->right_);
                this->_destroy_node(__n);
            }
        }

        node_pointer _insert_node(node_pointer __n, const_reference __ref, value_compare comp_ = value_compare()){
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

        node_pointer _find_node(const_reference __ref, _Compare comp = _Compare()){
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

        node_pointer _create_node(const_reference __ref, node_pointer __parent = nullptr){
            node_pointer __n = __node_traits::allocate(this->node_alloc_, 1);
            __node_traits::construct(this->node_alloc_, __n, __ref, __parent);
            return __n;
        }

        void _destroy_node(node_pointer __n){
            __node_traits::destroy(this->node_alloc_, __n);
            __node_traits::deallocate(this->node_alloc_, __n, 1);
        }

    };
}


#include "tree.tpp"