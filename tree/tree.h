#pragma once
#include <memory>
#include <iterator>
#include <set>
#include <cstdlib>
#include <ctime>
#include <map>
#include <vector>
#include <string>

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
        
        bool is_sentinel = false;

        value_type value_;
        __node():value_(value_type()){}
        __node(const_reference __ref):value_(__ref){}

        __node(const_reference __ref, __node *__parent):parent_(__parent), value_(__ref){}

        __node (const __node &__n):left_(__n.left_), right_(__n.right_), parent_(__n.parent_), value_(__n.value_){}

        inline bool operator==(const __node &__n) const{ return this->left_ == __n.right_ && this->right_ == __n.left_ && this->parent_ == __n.parent_; }

        inline bool operator!=(const __node &__n) const{ return !(*this == __n); }

        inline bool operator==(const __node *__n) const{ return *this == *__n; }

        inline bool operator!=(const __node *__n) const{ return *this != *__n; }

        inline bool _has_left_child() const{ return this->left_ != nullptr; }

        inline bool _has_right_child() const{ return this->right_ != nullptr; }

        inline bool _has_parent() const{ return this->parent_ != nullptr; }

        inline bool _is_left_child() const{ return this->_has_parent() && this->parent_->left_ == this; }

        inline bool _is_right_child() const{ return this->_has_parent() && this->parent_->right_ == this; }

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

    __tree_iterator();
    __tree_iterator(__node<value_type> *__n);
    __tree_iterator(const __tree_iterator &__it);
    __tree_iterator(__tree_iterator&&);
    ~__tree_iterator();
    template <typename _R>
    __tree_iterator(const __tree_iterator<_R> &__it);

    __tree_iterator& operator++();
    __tree_iterator operator--(int);
    __tree_iterator& operator--();
    __tree_iterator operator++(int);

    reference operator*();
    pointer operator->();
    bool operator==(const __tree_iterator &__it);
    bool operator!=(const __tree_iterator &__it);

    __tree_iterator& operator=(const __tree_iterator&);
    __tree_iterator& operator=(__tree_iterator&&);

    __node<value_type>* get();

};
namespace s21
{  
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
        __tree();
        __tree(const __tree&);
        __tree& operator=(__tree&&);
        ~__tree();

        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;

        iterator insert(const_reference __ref);
        void erase(iterator __pos);
        void replace(iterator l, iterator r);

        template <typename _Key>
        iterator find(const _Key& __key, value_compare comp_ = value_compare());
        iterator lower_bound(const_reference);
        iterator upper_bound(const_reference);
        size_type count(const_reference);
        size_type size() const;
        size_type max_size() const;
        void swap(__tree&);
        void clear();
        void display();
    // private:
    public:
        void _copy(const __tree& oth);
        void _copy(node_pointer *__src, node_pointer __dst, node_pointer __parent = nullptr);

        template <class _InputIter>
        void _construct(_InputIter __f, _InputIter __l);

        size_type _calc_size(node_pointer __n, size_type __sz = 0);
        int _distance_between(node_pointer __lhs, node_pointer __rhs);
        int _depth_from_root(node_pointer __root, node_pointer __n, int __depth = 0);
        node_pointer _find_lca(node_pointer __root, node_pointer __lhs, node_pointer __rhs);

        node_pointer _insert_node(node_pointer __n, const_reference __ref, value_compare comp_ = value_compare());
        void _display_node(node_pointer node, const std::string& prefix = "", bool isLeft = true);
        void _replace_nodes(node_pointer __lhs, node_pointer __rhs);
        node_pointer _find_node(const_reference __ref, _Compare comp = _Compare());
        node_pointer _create_node(const_reference __ref, node_pointer __parent = nullptr);
        node_pointer _remove_node(node_pointer __n);
        void _destroy_node(node_pointer __n);
        void _clear_node(node_pointer __n);
    };
}

#include "iterator.tpp"
#include "tree.tpp"