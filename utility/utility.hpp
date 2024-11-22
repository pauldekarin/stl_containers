#pragma once

#include <iostream>
#include <type_traits>
#include <string>

template <typename _T, typename = void>
struct has_allocator : std::false_type{};

template <typename _T>
struct has_allocator<_T, std::void_t <typename _T::allocator_type>> : std::true_type {};

template<typename _Container>
typename std::enable_if<
    has_allocator<_Container>::value && 
    !std::is_same<_Container, const std::string>::value, 
    std::ostream&
>::type
operator<<(std::ostream &os,  _Container &__seq) {
    os << "| ";
    for (auto it = __seq.begin(); it != __seq.end(); ++it) {
        os << *it << " | ";
    }
    return os << "\n";
}


template <typename _T1, typename _T2>
std::ostream& operator<<(std::ostream &os, const std::pair<_T1, _T2> &__p){
    return os << __p.first << " " << __p.second << "\n";
}

template <typename _LContainer, typename _RContainer>
bool __cmp(const _LContainer &__lhs, const _RContainer &__rhs){
    static_assert(
        std::is_same<typename _LContainer::value_type, typename _RContainer::value_type>::value,
        "__cmp must have same value_type"
    );
    
    typename _LContainer::const_iterator it = __lhs.begin();
    typename _RContainer::const_iterator jt = __rhs.begin();
    while(it != __lhs.end() && jt != __rhs.end()){
        if(*it != *jt){
            return false;
        }
        it++;
        jt++;
    }

    return it == __lhs.end() && jt == __rhs.end();
}
