#pragma once

#include "../s21_containers.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <functional>
#include <ctime>
#include <type_traits>
#include <limits>
#include <sstream>
#include <string>



template <typename _T, typename = void>
struct is_iterable : std::false_type {};

template <typename _T>
struct is_iterable<_T, std::void_t < decltype(std::declval<_T>().begin()), decltype(std::declval<_T>().end()) >> : std::true_type {};

bool __loop_test(std::function<bool(std::size_t)> &__fn, std::size_t __tests_count = 100);

template  
<typename _LContainer, 
typename _RContainer, 
typename = typename std::enable_if
    <std::is_same< typename _LContainer::value_type, 
                    typename _RContainer::value_type >::value &&
    is_iterable<_LContainer>::value && 
    is_iterable<_RContainer>::value >::type >
void __display_difference(const _LContainer &__lhs, const _RContainer &__rhs){
    typename _LContainer::const_iterator it = __lhs.begin();
    typename _RContainer::const_iterator jt = __rhs.begin();

    std::ostringstream is;
    std::ostringstream js;

    while(it != __lhs.end() && jt != __rhs.end()){
        std::string __color = *it == *jt  ? "\033[32m" : "\033[31m";
        is << __color << *it << " | " << "\033[0m";
        js << __color << *jt << " | " << "\033[0m";

        it++; jt++;
    }
    for(;it != __lhs.end();it++) is << "\033[31m" << *it << " | " << "\033[0m";
    for(;jt != __rhs.end();jt++) is << "\033[31m" << *jt << " | " << "\033[0m";
    
    std::cout << "L: " << is.str() << "\nR: " << js.str() << std::endl;
}

template <typename _LContainer, typename _RContainer, typename value_type = typename _LContainer::value_type>
typename std::enable_if<is_iterable<_LContainer>::value && is_iterable<_RContainer>::value && std::is_same< value_type, typename _RContainer::value_type  >::value, void>::type
__fill(_LContainer &__lhs, _RContainer &__rhs, std::size_t __max_size = 500, value_type __max_value = std::numeric_limits<value_type>::max()){
    std::size_t __size = __max_size;
    for(
        std::size_t __i = 0;
        __i < __size;
        __i++
    ){
        value_type __r = static_cast<value_type>(std::rand() % 100);

        __lhs.insert(__r);
        __rhs.insert(__r);
    }
}

template <
    typename _LContainer, 
    typename _RContainer, 
    typename = typename std::enable_if<
        is_iterable<_LContainer>::value &&
        is_iterable<_RContainer>::value
    >::type>
bool
__cmp(
    _LContainer &__lhs,
    _RContainer &__rhs
){
    static_assert(
        std::is_same<typename _LContainer::value_type, typename _RContainer::value_type>::value, "Containers must have same types"
    );

    typename _LContainer::iterator it = __lhs.begin();
    typename _RContainer::iterator jt = __rhs.begin();

    while(it != __lhs.end() && jt != __rhs.end()){
        if(*it != *jt){
            return false;
        }
        it++; jt++;
    }

    return it == __lhs.end() && jt == __rhs.end();
}

template <typename _Container, typename value_type = typename _Container::value_type>
typename std::enable_if< std::is_integral<value_type>::value && is_iterable<_Container>::value && !std::is_same<std::string, _Container>::value, std::ostream& >::type
operator<<(std::ostream &os, const _Container &__c){
    os << "[ ";
    for(
        typename _Container::const_iterator __it = __c.begin();
        __it != __c.end();
        __it++
    ){
        os << *__it << (std::next(__it) != __c.end() ? " | " : "");
    }
    return os << " ]\n";
}

class StackTester: public ::testing::Test{
public:
    s21::stack<int> __s;
    
    void SetUp(){

    }

    void TearDown(){

    }
};

class SetTester: public ::testing::Test{
public:
    void SetUp(){

    }

    void TearDown(){

    };
};

class ListTester: public ::testing::Test{
public:

    s21::list<int> __il;

    void SetUp(){

    }

    void TearDown(){

    };
};

class DequeTester: public ::testing::Test{
public:
    s21::deque<int> __d;

    void SetUp(){

    }
    
    void TearDown(){

    }
};



class MapTester: public ::testing::Test{
public:
    s21::map<int, int> __m;

    void SetUp(){

    }

    void TearDown(){

    }
};


class VectorTester: public ::testing::Test{
public:
    s21::vector<int> __v;

    void SetUp(){

    }

    void TearDown(){

    }
};