#pragma once

#include <memory>
#include <initializer_list>

namespace s21{
    template <typename _T, class _Allocator = std::allocator<_T>>
    class queue{
    public:
        using alloc_type = _Allocator;
        using value_type = typename alloc_type::value_type;
        using reference = typename alloc_type::reference;
        using const_reference = typename alloc_type::const_reference;
        using pointer = typename alloc_type::pointer;
        using size_type = typename alloc_type::size_type;

    protected:
        alloc_type alloc_;
        pointer head_ = nullptr;
        pointer tail_ = nullptr;
        size_type size_ = 0;
    
    public:
        queue(){}
        queue(std::initializer_list<_T> &__il){

        }
        queue(const queue &__q){

        }
        queue(queue &&__q){

        }
        ~queue(){

        }

        const_reference back(){

        }
        const_reference front(){

        }

        bool empty(){

        }

        size_type size(){

        }

        void push(const_reference __ref){

        }

        void pop(){

        }

        void swap(queue &__q){

        }

    private:
        pointer _create_ref(value_type &__v = value_type()){
            
        }
    };
    
}