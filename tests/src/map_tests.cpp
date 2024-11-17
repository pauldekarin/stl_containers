#include "../s21_containers_tests.hpp"


template <typename _T1, typename _T2>
std::ostream &operator<<(std::ostream &os, const std::pair<_T1, _T2> __p){
    return os << __p.first << " - " << __p.second << std::endl;
}
template< \
    typename _K, typename _V, class _Compare = std::less< _K >, \
    class _Allocator = std::allocator< std::pair<_K, _V> >, \
    template <typename,typename,typename,typename> class _LContainer, \
    template <typename, typename, typename, typename> class _RContainer> 
bool __cmp(_LContainer<_K, _V, _Compare, _Allocator> const &lhs, _RContainer<_K, _V, _Compare, _Allocator> const &rhs){
    auto it = lhs.begin();
    auto jt = rhs.begin();

    while(it != lhs.end() && jt != rhs.end()){
        if(*it != *jt){
            return false;
        }
        it++;
        jt++;
    }
    
    return it == lhs.end() && jt == rhs.end();
}

template< typename _K, typename _V, template<typename,typename, typename, typename> class _Container, class _Compare = std::less<std::pair<_K,_V>>, class _Allocator = std::allocator<std::pair<_K,_V> > >
std::ostream& operator<<(std::ostream &os, _Container<_K, _V, _Compare, _Allocator> &__ct){
    for(typename _Container<_K, _V, _Compare, _Allocator>::iterator it = __ct.begin(); it != __ct.end(); it++){
        os << it->first << " " << it->second << std::endl;
    }
    return os;
}

TEST_F(MapTester, Insert){
    __m.insert({1,2});
    __m.insert({2,1});
    __m.insert({3,1});
    __m.insert({0,1});
    __m.insert({-1,1});
    
    std::map<int,int> m;
    m.insert({1,2});
    m.insert({2,1});
    m.insert({3,1});
    m.insert({0,1});
    m.insert({-1,1});

    ASSERT_EQ(__cmp(__m, m), true);
}

TEST_F(MapTester, ConstructorCopy){
    s21::map<int,int> l1({ {1,4}, {4,5}, {4,4}, {4,4}, {-1, 100}, {0,50} });
    std::map<int, int> l2({ {1,4}, {4,5}, {4,4}, {4,4}, {-1, 100}, {0,50} });

    ASSERT_EQ(__cmp(l1, l2), true);
}

TEST_F(MapTester, Contains){
    __m = s21::map<int,int>({ {1,1}, {4,4} });
    ASSERT_EQ(__m.contains(4), true);
    ASSERT_EQ(__m.contains(1), true);
    ASSERT_EQ(__m.contains(2), false);
}

TEST_F(MapTester, Erase){
    __m = s21::map<int,int>({
        {1,1}, {4,4}, {0,0}, {23,9}, {-1,1}, {-1, 1}, {-1 ,2}
    });

    std::map<int,int> m({
        {1,1}, {4,4}, {0,0}, {23,9}, {-1,1}, {-1, 1}, {-1 ,2}
    });

    m.erase(std::next(m.begin(), 2));
    __m.erase(std::next(__m.begin(), 2));


    ASSERT_EQ(__cmp(m, __m), true);

    m.erase(std::prev(m.end()));
    __m.erase(std::prev(__m.end()));

    ASSERT_EQ(__cmp(m, __m), true);

    m.erase(m.begin());
    __m.erase(__m.begin());

    ASSERT_EQ(__cmp(m, __m), true);

    ASSERT_THROW(__m.erase(__m.end()), std::invalid_argument);
}

TEST_F(MapTester, InsertOrAssign){
    auto it = __m.insert_or_assign(1,1);

    std::map<int,int> m;
    m.insert_or_assign(1,1);

    ASSERT_EQ(__cmp(m, __m), true);
    ASSERT_EQ(__m.begin(), it.first);

    __m.insert_or_assign(1,4);

    m.insert_or_assign(1,4);

    ASSERT_EQ(__cmp(m, __m), true);
    ASSERT_EQ(__m.begin(), it.first);

}

TEST_F(MapTester, Swap){
    s21::map<int,int> __l({
        {1,1},{1,1},{1,1}
    });

    std::map<int,int> m;
    std::map<int,int> l({
        {1,1},{1,1},{1,1}
    });

    m.swap(l);

    __m.swap(__l);


    ASSERT_EQ(__cmp(m, __m), true);
    ASSERT_EQ(__cmp(l, __l), true);
    ASSERT_EQ(__m.size(), 1);
}

TEST_F(MapTester, Merge){
    s21::map<int,int> __l({
        {1,1},{4,3}
    });

    __m.merge(__l);
    
    std::map<int,int> m;
    
    std::map<int,int> l({
        {1,1},{4,3}
    });

    m.merge(l);

    ASSERT_EQ(__cmp(m, __m), true);
    ASSERT_EQ(__cmp(l, __l), true);

    __l = s21::map<int,int>({
        {1,15}, {5,3}
    });

    l = std::map<int,int>({
        {1,15}, {5,3}
    });

    m.merge(l);

    __m.merge(__l);

    ASSERT_EQ(__cmp(m, __m), true);
    ASSERT_EQ(__cmp(l, __l), true);

}

TEST_F(MapTester, At){
    ASSERT_THROW(__m.at(1), std::out_of_range);


    std::map<int,int> m({
        {1,1},{2,4},{3,9}
    });

    __m = s21::map<int,int>({
        {1,1},{2,4},{3,9}
    });

    ASSERT_EQ(__cmp(__m, m), true);
    ASSERT_EQ(__m.at(1), m.at(1));
    ASSERT_EQ(__m.at(2), m.at(2));
    ASSERT_EQ(__m.at(3), m.at(3));
}

TEST_F(MapTester, Operator){
    __m[133] = 331;
    __m[331] = 133;
    __m[999];

    std::map<int,int> m;

    m[133] = 331;
    m[331] = 133;
    m[999];

    ASSERT_EQ(__cmp(m, __m), true);
}

TEST_F(MapTester, Clear){
    __m = s21::map<int,int>({{1,1}});
    __m.clear();

    std::cout << __m;
}