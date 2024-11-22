#pragma once
#include <utility>
#include <memory>
#include <map>
#include "../tree/tree.h"

namespace s21{
    template <typename _Key, typename _Value, class _Compare = std::less<_Key>, class _Allocator = std::allocator< std::pair<const _Key, _Value>> >
    class multimap{
    public:
        typedef _Allocator allocator_type;
        typedef _Key key_type;
        typedef _Value mapped_type;
        typedef _Compare key_compare;
        typedef typename allocator_type::value_type value_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::size_type size_type;
        
        class value_compare{
            friend class multimap;
        public:
            key_compare comp_;

            value_compare(){}

            value_compare(key_compare __comp) : comp_(__comp){}

            bool operator()(const value_type &__lhs, const value_type &__rhs) const{
                if(!this->comp_(__lhs.first, __rhs.first) && !this->comp_(__rhs.first, __lhs.first)){
                    return this->comp_(__lhs.second, __rhs.second);
                }
                return this->comp_(__lhs.first, __rhs.first);
            }

            bool operator()(const key_type &__key, const value_type &__pair) const{
                return this->comp_(__key, __pair.first);
            }

            bool operator()(const value_type &__pair, const key_type &__key) const{
                return this->comp_(__pair.first, __key);
            }
        };

        typedef s21::__tree<value_type, value_compare, allocator_type> __base;
        typedef typename __base::iterator iterator;
        typedef typename __base::const_iterator const_iterator;


    protected:
        __base tree_;

    public:
        /**
         * Default constructor, creates an empty multimap.
         */
        multimap();

        /**
         * Constructor that initializes the multimap using an initializer list.
         * @param items - Initializer list of key-value pairs to initialize the multimap.
         */
        multimap(std::initializer_list<std::pair<const key_type, value_type>> const& items);

        /**
         * Copy constructor, creates a new multimap by copying another multimap.
         * @param m - The multimap to copy from.
         */
        multimap(const multimap& m);

        /**
         * Move constructor, creates a new multimap by transferring ownership from another multimap.
         * @param m - The multimap to move from.
         */
        multimap(multimap&& m);

        /**
         * Destructor, clears the contents of the multimap.
         */
        ~multimap();

        /**
         * Move assignment operator, assigns the contents of another multimap to this multimap.
         * @param m - The multimap to assign from.
         * @return Reference to the updated multimap.
         */
        multimap& operator=(multimap&& m);

        // Element access

        /**
         * Access specified element with bounds checking.
         * @param key - The key of the element to access.
         * @return Reference to the value associated with the key.
         */
        reference at(const key_type& key);

        // Iterators

        /**
         * Returns an iterator to the beginning of the multimap.
         * @return Iterator to the first element.
         */
        iterator begin();

        /**
         * Returns an iterator to the end of the multimap.
         * @return Iterator to one past the last element.
         */
        iterator end();

         /**
         * Returns an const iterator to the beginning of the multimap.
         * @return Const Iterator to the first element.
         */
        const_iterator begin() const;

        /**
         * Returns an const iterator to the end of the multimap.
         * @return Const Iterator to one past the last element.
         */
        const_iterator end() const;

        // Capacity

        /**
         * Checks whether the container is empty.
         * @return True if the multimap is empty, false otherwise.
         */
        bool empty() const;

        /**
         * Returns the number of elements in the multimap.
         * @return Number of elements.
         */
        size_type size() const;

        /**
         * Returns the maximum possible number of elements.
         * @return Maximum number of elements the multimap can hold.
         */
        size_type max_size() const;

        // Modifiers

        /**
         * Clears the contents of the multimap.
         */
        void clear();

        /**
         * Inserts a key-value pair into the multimap.
         * @param value - The key-value pair to insert.
         * @return Pair of iterator and boolean indicating success.
         */
        std::pair<iterator, bool> insert(const_reference);

        /**
         * Inserts a value by key into the multimap.
         * @param key - The key for the new element.
         * @param obj - The value to associate with the key.
         * @return Pair of iterator and boolean indicating success.
         */
        std::pair<iterator, bool> insert(const key_type&, const mapped_type&);

        /**
         * Erases the element at the specified position.
         * @param pos - Iterator to the element to erase.
         */
        void erase(iterator pos);

        /**
         * Swaps the contents of this multimap with another multimap.
         * @param other - The multimap to swap contents with.
         */
        void swap(multimap& other);

        /**
         * Splices nodes from another container into this multimap.
         * @param other - The multimap to merge nodes from.
         */
        void merge(multimap& other);

        // Lookup

        /**
         * Checks if there is an element with a key equivalent to the given key in the multimap.
         * @param key - The key to search for.
         * @return True if the key exists, false otherwise.
         */
        bool contains(const key_type& key) const;
    };  
}

#include "multimap.tpp"