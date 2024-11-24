#include "../tests.hpp"


TEST_F(DequeTester, Erase){
    __d = s21::deque<int>({1,2,3,4,5,6,7,8});
    __d.erase(std::next(__d.begin(), 2));
    
    std::deque<int> d({1,2,3,4,5,6,7,8});
    d.erase(std::next(d.begin(), 2));

    ASSERT_TRUE(__cmp(__d, d));
}

TEST_F(DequeTester, Iterators){
    __d = s21::deque<int>({1,2,3,4});

    s21::deque<int>::const_iterator __it = __d.begin();
    s21::deque<int>::reverse_iterator __rit = __d.rbegin();
    s21::deque<int>::reverse_iterator __rjt = __d.rend();

    std::deque<int> d({1,2,3,4});

    std::deque<int>::const_iterator it = d.begin();
    std::deque<int>::reverse_iterator rit = d.rbegin();
    std::deque<int>::reverse_iterator rjt = d.rend();

    ASSERT_EQ(*it, *__it);
    ASSERT_EQ(*rit, *__rit);
}

TEST_F(DequeTester, Insert){
    __d.insert(__d.begin(), 1);

    std::deque<int> d;
    
    d.insert(d.begin(), 1);

    ASSERT_TRUE(__cmp(d, __d));

    __d.insert(__d.begin(), 2);

    d.insert(d.begin(), 2);

    ASSERT_TRUE(__cmp(d, __d));

    __d.insert(__d.end(), 3);

    d.insert(d.end(), 3);
    
    ASSERT_TRUE(__cmp(d, __d));

    __d.insert(std::next(__d.begin(), 2), 4);

    d.insert(std::next(d.begin(), 2), 4);

    ASSERT_TRUE(__cmp(d, __d));

    __d.insert(std::next(__d.begin(), 3), 5, 5);

    d.insert(std::next(d.begin(), 3), 5, 5);


    ASSERT_TRUE(__cmp(d, __d));

    int array[] = {6,7,8,9};

    __d.insert(std::next(__d.begin(),2), array, array + 4);

    d.insert(std::next(d.begin(),2), array, array + 4);

    ASSERT_TRUE(__cmp(d, __d));
}

TEST_F(DequeTester, PushFront){
  
}

TEST_F(DequeTester, ShrinkToFit){

    for(std::size_t i = 0; i < 64; i++){
        __d.push_front(i);
    }

    for(std::size_t i = 0; i < 64; i++){
        __d.push_back(i);
    }

    for(std::size_t i = 0;  i < 30; i++){
        __d.pop_back();
    }

    for(std::size_t i = 0;  i < 30; i++){
        __d.pop_front();
    }


    __d.shrink_to_fit();
}