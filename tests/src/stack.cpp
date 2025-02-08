#include "../tests.hpp"
#include <stack>

template <typename _T>
bool __cmp_stack(s21::stack<_T> &lhs, const std::stack<_T> &rhs){
    if(lhs.size() != rhs.size()){
        return false;
    }

    s21::stack<_T> lhs_copy(lhs);
    std::stack<_T> rhs_copy(rhs);

    while (!lhs_copy.empty())
    {
        if(lhs_copy.top() != rhs_copy.top()){
            return false;
        }

        lhs_copy.pop();
        rhs_copy.pop();
    }
    

    return true;
}

TEST(Stack_Constructor, Default){
    s21::stack<int> q1({1,2,3});
    s21::stack<int> q2(q1);
    std::stack<int> q({1,2,3});

    ASSERT_TRUE(__cmp_stack(q1, q));
    ASSERT_TRUE(__cmp_stack(q2, q));

    s21::stack<int> q3(std::move(q1));

    ASSERT_TRUE(q1.empty());
    ASSERT_TRUE(__cmp_stack(q3, q));

    q3 = std::move(q2);

    ASSERT_TRUE(q2.empty());
    ASSERT_TRUE(__cmp_stack(q3,q));
}

TEST(Stack_Top, Default){
    s21::stack<int> q({1,2,3});

    ASSERT_EQ(q.top(), 3);
}

TEST(Stack_Empty, Default){
    s21::stack<int> q;

    ASSERT_TRUE(q.empty());

    q.insert_many_back(1);

    ASSERT_FALSE(q.empty());
}

TEST(Stack_Size, Default){
    s21::stack<int> q;

    ASSERT_TRUE(q.size() == 0);

    q.insert_many_back(1,2);

    ASSERT_TRUE(q.size() == 2);
}

TEST(Stack_Insert, Default){
    s21::stack<int> q;
    std::stack<int> sq;

    ASSERT_TRUE(__cmp_stack(q,sq));

    q.push(1);
    sq.push(1);

    ASSERT_TRUE(__cmp_stack(q,sq));

    q.push(2);
    sq.push(2);

    ASSERT_TRUE(__cmp_stack(q,sq));

    q.insert_many_back(3,4);
    sq.push(3);
    sq.push(4);

    ASSERT_TRUE(__cmp_stack(q,sq));
}

TEST(Stack_PopSwap, Default){
    s21::stack<int> q1({1,2});
    s21::stack<int> q2({3,4});

    std::stack<int> sq1({1,2});
    std::stack<int> sq2({3,4});

    ASSERT_TRUE(__cmp_stack(q1, sq1));
    ASSERT_TRUE(__cmp_stack(q2, sq2));

    q1.swap(q2);
    sq1.swap(sq2);

    ASSERT_TRUE(__cmp_stack(q1, sq1));  
    ASSERT_TRUE(__cmp_stack(q2, sq2));


    q1.pop();
    sq1.pop();

    ASSERT_TRUE(__cmp_stack(q1, sq1));  
}