#include "../tests.hpp"


TEST(Vector_PushBack, Common){
    std::function<bool(std::size_t)> __push_test = [](std::size_t __test_id){
        s21::vector<int> __v;
        std::vector<int> v;
        for(std::size_t __i = 0; __i <= std::rand() % 1000; __i++){
            int __x = std::rand();
            __v.push_back(__x);
            v.push_back(__x);
        }
        return __cmp(__v,v);
    };
    ASSERT_TRUE(__loop_test(__push_test));
}


TEST(Vector_Size, Common){
    std::function<bool(std::size_t)> __push_test = [](std::size_t __test_id){
        s21::vector<int> __v;
        std::vector<int> v;
        for(std::size_t __i = 0; __i <= std::rand() % 1000; __i++){
            int __x = std::rand();
            __v.push_back(__x);
            v.push_back(__x);
        }
        return v.size() == __v.size();
    };
    ASSERT_TRUE(__loop_test(__push_test));
}

TEST(Vector_InsertMany, Common){
    s21::vector<int> __v({1,2,3});
    s21::vector<int>::const_iterator it =  __v.begin();
    auto f = __v.insert_many(it, 10);
    std::cout << *f << std::endl;
}

TEST(Vector_InsertManyBack, Common){
    s21::vector<int> __v({1,2,3});

    __v.insert_many_back(40,"123");
    std::cout << __v << std::endl;
}


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
    ASSERT_THROW(__v.back(), std::out_of_range);
    ASSERT_THROW(__v.front(), std::out_of_range);
    ASSERT_THROW(__v[0], std::out_of_range);
    ASSERT_THROW(__v.at(0), std::out_of_range);
    ASSERT_EQ(__v.data(), nullptr);
    
    __v.insert(__v.end(), 1);

    std::vector<int> v({1});

    ASSERT_EQ(__v.back(), v.back());
    ASSERT_EQ(__v.front(), v.front());
    ASSERT_EQ(__v.at(0), v.at(0));
    ASSERT_EQ(__v[0], v[0]);
    ASSERT_TRUE(__v.data() != nullptr);

    __v.insert(__v.begin(), 2);

    v.insert(v.begin(), 2);

    ASSERT_EQ(__v.back(), v.back());
    ASSERT_EQ(__v.front(), v.front());
    ASSERT_EQ(__v.at(0), v.at(0));
    ASSERT_EQ(__v[0], v[0]);
    ASSERT_EQ(__v.at(1), v.at(1));
    ASSERT_EQ(__v[1], v[1]);
}

TEST_F(VectorTester, ShrinkToFit){
    __v.shrink_to_fit();
    ASSERT_EQ(__v.size(), __v.capacity());

    __v.reserve(10);

    ASSERT_FALSE(__v.size() == __v.capacity());

    __v.shrink_to_fit();

    ASSERT_EQ(__v.size(), __v.capacity());

    __v.insert(__v.begin(), 1);
    __v.insert(__v.begin(), 1);
    __v.insert(__v.begin(), 1);
    __v.insert(__v.begin(), 1);
    __v.insert(__v.begin(), 1);

    ASSERT_FALSE(__v.size() == __v.capacity());

    __v.shrink_to_fit();

    ASSERT_TRUE(__v.size() == __v.capacity());

    __v.clear();

    ASSERT_FALSE(__v.size() == __v.capacity());
    
    __v.shrink_to_fit();

    ASSERT_TRUE(__v.size() == __v.capacity());
}

TEST_F(VectorTester, Swap){
    s21::vector<int> __l({1,2,3,4});

    std::vector<int> v;
    std::vector<int> l({1,2,3,4});


    __v.swap(__l);
    v.swap(l);

    ASSERT_TRUE(__cmp(__v, v));
    ASSERT_TRUE(__cmp(__l, l));
}

TEST_F(VectorTester, PushPopBack){
    ASSERT_THROW(__v.pop_back(), std::out_of_range);

    std::vector<int> v;

    __v.push_back(1);
    __v.push_back(2);
    __v.push_back(3);

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    ASSERT_TRUE(__cmp(__v,v));

    __v.pop_back();
    v.pop_back();

    ASSERT_TRUE(__cmp(__v, v));

    __v.pop_back();
    __v.pop_back();
    v.pop_back();
    v.pop_back();

    ASSERT_TRUE(__cmp(__v, v));

    ASSERT_THROW(__v.pop_back(), std::out_of_range);
}

TEST_F(VectorTester, ReverseIterator){
    __v = s21::vector<int>({1,2,3,4});

    ASSERT_EQ(*__v.rbegin(), 4);
    ASSERT_EQ(*std::prev(__v.rend()), 1);
}

TEST_F(VectorTester, MaxSize){
    std::vector<int> v;
    ASSERT_EQ(__v.max_size(), v.max_size());
}