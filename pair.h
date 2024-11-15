#pragma once

#include <utility>
#include <functional>


namespace s21{
    template<typename _T1, typename _T2>
    class pair{
    public:
        _T1 first;
        _T2 second;
        pair():first(_T1{}), second(_T2{}){}
        pair(_T1 __f, _T2 __s):first(__f), second(__s){}
        pair(_T1 &__f, _T2 &__s):first(__f), second(__s){}
        pair(const pair &__p):first(__p.first), second(__p.second){}
        pair(pair &&__p):first(std::move(__p.first)), second(std::move(__p.second)){}
        ~pair(){}

        pair& operator->(){
            return &(*this);
        }

        bool operator<(pair const &_oth){
            return this->first < _oth.first;
        }
    };
}


namespace std {
    template<typename _T1, typename _T2>
    struct less<s21::pair<_T1, _T2>> {
        bool operator()(const s21::pair<_T1, _T2>& lhs, const s21::pair<_T1, _T2>& rhs) const {
            return lhs.first < rhs.first;  // Compare based on the `first` element
        }
    };
}