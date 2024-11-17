#include "../s21_containers_tests.hpp"


TEST_F(VectorTester, Constructor){
    s21::vector<int> __l({1,2,3,4});
    std::vector<int> l({1,2,3,4});

    ASSERT_EQ(__cmp(__l, l), true);

    s21::vector<int> __r(std::move(__l));
    std::vector<int> r(std::move(l));

    ASSERT_EQ(__cmp(__l,l), true);
    ASSERT_EQ(__cmp(__r,r), true);

    s21::vector<int> __e(4);
    std::vector<int> e(4);

    ASSERT_EQ(__cmp(__e, e), true);
}

TEST_F(VectorTester, Size){
    ASSERT_EQ(__v.size(), 0);
    __v = s21::vector<int>({1,2,3,4});
    ASSERT_EQ(__v.size(), 4);
    __v.erase(__v.begin());
    ASSERT_EQ(__v.size(), 3);
    __v.erase(__v.begin());
    __v.erase(__v.begin());
    __v.erase(__v.begin());
    ASSERT_EQ(__v.size(), 0);
}

TEST_F(VectorTester, Empty){
    ASSERT_EQ(__v.empty(), true);
    __v.insert(__v.begin(), 40);
    ASSERT_EQ(__v.empty(), false);
    __v.erase(__v.begin());
    ASSERT_EQ(__v.empty(), true);
}

TEST_F(VectorTester, Reserve){
    __v.reserve(10);
    ASSERT_EQ(__v.capacity(), 10);
    ASSERT_EQ(__v.size(), 0);
    __v.reserve(1);
    ASSERT_EQ(__v.capacity(), 10);
    ASSERT_EQ(__v.size(), 0);
    __v.reserve(20);
    ASSERT_EQ(__v.capacity(), 20);
    ASSERT_EQ(__v.size(), 0);
}

TEST_F(VectorTester, Insert){
    std::vector<int> v;

    __v.insert(__v.begin(), 1);
    v.insert(v.begin(), 1);

    ASSERT_EQ(__cmp(__v,v), true);

    __v.insert(__v.begin(), 2);
    v.insert(v.begin(), 2);
    
    ASSERT_EQ(__cmp(__v,v), true);
    
     __v.insert(__v.end(), 2);
    v.insert(v.end(), 2);

    ASSERT_EQ(__cmp(__v,v), true);

    __v.insert(std::next(__v.begin(), 1), 3);
    v.insert(std::next(v.begin(), 1), 3);

    ASSERT_EQ(__cmp(__v,v), true);
}

TEST_F(VectorTester, Erase){
    __v = s21::vector<int>({1,2,3,4,5});
    std::vector<int> v({1,2,3,4,5});
    
    __v.erase(std::next(__v.begin(), 2));
    v.erase(std::next(v.begin(), 2));

    ASSERT_EQ(__cmp(__v, v), true);

    __v.erase(std::prev(__v.end()));
    v.erase(std::prev(v.end()));

    ASSERT_EQ(__cmp(__v, v), true);

    __v.erase(__v.begin());
    v.erase(v.begin());

    ASSERT_EQ(__cmp(__v,v),true);
}

TEST_F(VectorTester, Accessors){
    std::vector<int> v;
    
}

