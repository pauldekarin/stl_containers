#include "../tests.hpp"

TEST_F(ListTester, Insert_Common){
    __il.insert(__il.begin(), 1);
    __il.insert(__il.end(), 2);
    s21::list<int>::iterator it = __il.insert(__il.begin(), 3);
    __il.insert(std::next(++it), 4);
    
    std::list<int> l;

    l.insert(l.begin(), 1);
    l.insert(l.end(), 2);
    std::list<int>::iterator jt = l.insert(l.begin(), 3);
    l.insert(std::next(++jt), 4);
    
    ASSERT_EQ(__cmp(l, __il), true);
}

TEST_F(ListTester, InsertMany){
    __il.insert_many(__il.begin(), 1,2,3,4);
    auto it = __il.insert_many(__il.begin(), 4,2,3,4);
    __il.insert_many(it, 100,200);
    
    std::list<int> l({4,2,3,100,200,4,1,2,3,4});

    ASSERT_TRUE(__cmp(__il, l));
}


TEST_F(ListTester, InsertManyBack){
    __il.insert_many_back(1,2,3,4);
    __il.insert_many_back(4,3,2,1);
    
    std::list<int> l({1,2,3,4,4,3,2,1});

    ASSERT_TRUE(__cmp(__il, l));
}

TEST_F(ListTester, InsertManyFront){
    __il.insert_many_front(1,2,3,4);
    __il.insert_many_front(100,200);
    
    std::list<int> l({100,200,1,2,3,4});
    std::cout << __il << std::endl;

    ASSERT_TRUE(__cmp(__il, l));
}

TEST_F(ListTester, Clear){
    __il.insert(__il.begin(),1);
    __il.insert(__il.begin(),2);
    __il.insert(__il.begin(),3);
    __il.clear();

    ASSERT_TRUE(__il.size() == 0);
}

TEST_F(ListTester, Size_Empty){
    ASSERT_TRUE(__il.size() == 0);
}

TEST_F(ListTester, Size_Increments){
    __il.insert(__il.begin(),1);
    __il.insert(__il.begin(),2);
    __il.insert(__il.begin(),3);

    ASSERT_TRUE(__il.size() ==  3);
}

TEST_F(ListTester, Erase){
    __il = s21::list<int>({1,2,3,4});
    s21::list<int>::iterator it = __il.begin();
    std::advance(it, 2);
    __il.erase(it); 

    std::list<int> l({1,2,3,4});
    std::list<int>::iterator jt = l.begin();
    std::advance(jt, 2);
    l.erase(jt);

    ASSERT_EQ(__cmp(__il, l), true);
}

TEST_F(ListTester, PushBack_Filled){
    __il = s21::list<int>({1,2,3});
    __il.push_back(4);

    std::list<int> l({1,2,3});
    l.push_back(4);

    ASSERT_EQ(__cmp(__il, l), true);
}

TEST_F(ListTester, PushBack_Empty){
    __il.push_back(1);

    std::list<int> l;
    l.push_back(1);

    ASSERT_EQ(__cmp(__il, l), true);
}

TEST_F(ListTester, PopBack){
    __il = s21::list<int>({1,2,3,4});
    __il.pop_back();

    std::list<int> l({1,2,3,4});
    l.pop_back();

    ASSERT_EQ(__cmp(__il ,l), true);
}

TEST_F(ListTester, Swap){
    __il = s21::list<int>({1,2,3,4});

    s21::list<int> __sl({4,3,2,1});

    __il.swap(__sl);

    std::list<int> l1({1,2,3,4});
    std::list<int> l2({4,3,2,1});

    l1.swap(l2);

    ASSERT_EQ(__cmp(__il, l1), true);
    ASSERT_EQ(__cmp(__sl, l2), true);
}

TEST_F(ListTester, Merge_Common){
    __il = s21::list<int>({1,3,5,7});
    s21::list<int> __sl({2,4,6,8,10,12});

    __il.merge(__sl);

    std::list<int> l1({1,3,5,7});
    std::list<int> l2({2,4,6,8,10,12});

    l1.merge(l2);

    ASSERT_EQ(__cmp(__il, l1), true);
    ASSERT_EQ(__cmp(__sl, l2), true);
}

TEST_F(ListTester, Splice_Begin){
    __il = s21::list<int>({1,2,3,4,5,6});
    s21::list<int> __sl({10,11,12});

    __il.splice(__il.begin(), __sl);

    std::list<int> l1({1,2,3,4,5,6});
    std::list<int> l2({10,11,12});

    l1.splice(l1.begin(), l2);

    ASSERT_EQ(__cmp(__il, l1), true);
    ASSERT_EQ(__cmp(__sl, l2), true);
}

TEST_F(ListTester, Splice_Middle){
    __il = s21::list<int>({1,2,3,4,5,6});
    s21::list<int> __sl({10,11,12});
    
    s21::list<int>::const_iterator it = __il.begin();
    std::advance(it, 2);

    __il.splice(it, __sl);

    std::list<int> l1({1,2,3,4,5,6});
    std::list<int> l2({10,11,12});

    std::list<int>::const_iterator jt = l1.begin();
    std::advance(jt, 2);

    l1.splice(jt, l2);

    ASSERT_EQ(__cmp(__il, l1), true);
    ASSERT_EQ(__cmp(__sl, l2), true);
}

TEST_F(ListTester, Splice_End){
    __il = s21::list<int>({1,2,3,4,5,6});
    s21::list<int> __sl({10,11,12});

    __il.splice(__il.end(), __sl);

    std::list<int> l1({1,2,3,4,5,6});
    std::list<int> l2({10,11,12});
    l1.splice(l1.end(), l2);

    ASSERT_EQ(__cmp(__il, l1), true);
    ASSERT_EQ(__cmp(__sl, l2), true);
}

TEST_F(ListTester, Reverse){
    __il = s21::list<int>({1,2,3,4,5,6});
    __il.reverse();

    std::list<int> l({1,2,3,4,5,6});
    l.reverse();

    ASSERT_EQ(__cmp(__il,l), true);
}

TEST_F(ListTester, Unique){
    std::list<int> l({1, 2, 12, 23, 3, 2, 51, 1, 2, 2});
    l.unique();

    __il = s21::list<int>({1, 2, 12, 23, 3, 2, 51, 1, 2, 2});
    __il.unique();

    ASSERT_EQ(__cmp(l, __il), true);
}

TEST_F(ListTester, Unique_Same){
    std::list<int> l({1,1,1,1,1,1});
    l.unique();

    __il = s21::list<int>({1,1,1,1,1,1});
    __il.unique();

    ASSERT_EQ(__cmp(l, __il), true);
}

TEST_F(ListTester, Sort_Common){
    __il = s21::list<int>({3,2,1,0,4,5,3,3,3,3,3});
    __il.sort();
    
    std::list<int> l({3,2,1,0,4,5,3,3,3,3,3});
    l.sort();

    ASSERT_EQ(__cmp(__il, l), true);
}

TEST_F(ListTester, Front){
    ASSERT_THROW(__il.front(), std::out_of_range);
    ASSERT_THROW(__il.back(), std::out_of_range);

    __il.push_front(44);

    ASSERT_EQ(44, __il.front());
    ASSERT_EQ(44, __il.back());

    __il.push_front(22);

    ASSERT_EQ(22, __il.front());
    ASSERT_EQ(44, __il.back());
}

TEST_F(ListTester, OperatorCopyMove){
    s21::list<int> __src({1,2,3,4});
    __il = std::move(__src);

    std::list<int> l1;
    std::list<int> l2({1,2,3,4});

    l1 = std::move(l2);

    ASSERT_EQ(__cmp(__il, l1), true);
    ASSERT_EQ(__cmp(__src, l2), true);
}