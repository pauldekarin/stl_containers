#include "../tests.hpp"
#include <queue>

template <typename _T>
bool __cmp_queue(s21::queue<_T> &lhs, const std::queue<_T> &rhs){
    if(lhs.size() != rhs.size()){
        return false;
    }

    s21::queue<_T> lhs_copy(lhs);
    std::queue<_T> rhs_copy(rhs);

    while (!lhs_copy.empty())
    {
        if(lhs_copy.front() != rhs_copy.front()){
            return false;
        }

        lhs_copy.pop();
        rhs_copy.pop();
    }
    

    return true;
}

TEST(Queue_Constructor, Default){
    s21::queue<int> q1({1,2,3});
    s21::queue<int> q2(q1);
    std::queue<int> q({1,2,3});

    ASSERT_TRUE(__cmp_queue(q1, q));
    ASSERT_TRUE(__cmp_queue(q2, q));

    s21::queue<int> q3(std::move(q1));

    ASSERT_TRUE(q1.empty());
    ASSERT_TRUE(__cmp_queue(q3, q));

    q3 = std::move(q2);

    ASSERT_TRUE(q2.empty());
    ASSERT_TRUE(__cmp_queue(q3,q));
}

TEST(Queue_FrontBack, Default){
    s21::queue<int> q({1,2,3});

    ASSERT_EQ(q.front(), 1);
    ASSERT_EQ(q.back(), 3);
}

TEST(Queue_Empty, Default){
    s21::queue<int> q;

    ASSERT_TRUE(q.empty());

    q.insert_many_back(1);

    ASSERT_FALSE(q.empty());
}

TEST(Queue_Size, Default){
    s21::queue<int> q;

    ASSERT_TRUE(q.size() == 0);

    q.insert_many_back(1,2);

    ASSERT_TRUE(q.size() == 2);
}

TEST(Queue_Insert, Default){
    s21::queue<int> q;
    std::queue<int> sq;

    ASSERT_TRUE(__cmp_queue(q,sq));

    q.push(1);
    sq.push(1);

    ASSERT_TRUE(__cmp_queue(q,sq));

    q.push(2);
    sq.push(2);

    ASSERT_TRUE(__cmp_queue(q,sq));

    q.insert_many_back(3,4);
    sq.push(3);
    sq.push(4);

    ASSERT_TRUE(__cmp_queue(q,sq));
}

TEST(Queue_PopSwap, Default){
    s21::queue<int> q1({1,2});
    s21::queue<int> q2({3,4});

    std::queue<int> sq1({1,2});
    std::queue<int> sq2({3,4});

    ASSERT_TRUE(__cmp_queue(q1, sq1));
    ASSERT_TRUE(__cmp_queue(q2, sq2));

    q1.swap(q2);
    sq1.swap(sq2);

    ASSERT_TRUE(__cmp_queue(q1, sq1));  
    ASSERT_TRUE(__cmp_queue(q2, sq2));


    q1.pop();
    sq1.pop();

    ASSERT_TRUE(__cmp_queue(q1, sq1));  
}