#pragma once

#include <iostream>

template<typename _T, template <typename, typename> class  _SeqContainer, class _Alloc = std::allocator<_T> >
std::ostream &operator<<(std::ostream &os, const _SeqContainer<_T, _Alloc> &__seq){
    for(typename _SeqContainer<_T, _Alloc>::const_iterator it = __seq.begin(); it != __seq.end(); it++){
        os << *it << " | ";
    }
    return os << "\n";
}

template < typename _T, class _Allocator = std::allocator<_T>, template <typename, typename> class _LSeqContainer, template <typename, typename> class _RSeqContainer >
bool __cmp(const _LSeqContainer<_T, _Allocator> &__lhs, const _RSeqContainer<_T, _Allocator> &__rhs){
    typename _LSeqContainer<_T, _Allocator>::const_iterator it = __lhs.begin();
    typename _RSeqContainer<_T, _Allocator>::const_iterator jt = __rhs.begin();

    while(it != __lhs.end() && jt != __rhs.end()){
        if(*it != *jt){
            return false;
        }
        it++;
        jt++;
    }

    return it == __lhs.end() && jt == __rhs.end();
}
