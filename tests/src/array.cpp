#include "../tests.hpp"

TEST(Array_Constructor, Default){
    s21::array<int, 4> a({1,2,3,4});
    s21::array<int, 4> b(a);

    ASSERT_TRUE(__cmp(a,b));

    
}

TEST(Array_Constructor, CopyMove){
}

TEST(Array_Iterator, Default){
    s21::array<int, 5> a;
    a.begin();
}


TEST(Array_MoveAssignmentAndConstructor, Default){
    s21::array<int, 5> a1({1,2,3,4,5});
    s21::array<int, 5> a2(std::move(a1));
    std::array<int, 5> a({1,2,3,4,5});


    ASSERT_TRUE(__cmp(a1, a));
    ASSERT_TRUE(__cmp(a2, a));

    s21::array<int, 5> a3;
    a3 = std::move(a1);

    ASSERT_TRUE(__cmp(a3, a));
}

TEST(Array_At, Default){
    s21::array<int, 10> arr({0,1,2,3,4,5,6,7,8,9});

    for(s21::array<int, 10>::size_type i = 0; i < arr.size() ; i++){
        ASSERT_EQ(static_cast<int>(i), arr.at(i));
    }

    for(s21::array<int, 10>::size_type i = 0; i < arr.size() ; i++){
        ASSERT_EQ(static_cast<int>(i), arr[i]);
    }
}

TEST(Array_FrontBack, Default){
    s21::array<int, 2> arr({1,2});

    ASSERT_EQ(arr.front(), 1);
    ASSERT_EQ(arr.back(), 2);

}

TEST(Array_Empty, Default){
    s21::array<int, 0> emp{};
    s21::array<int, 1> arr({1});

    ASSERT_TRUE(emp.empty());
    ASSERT_FALSE(arr.empty());
}

TEST(Array_Size, Default){
    s21::array<int, 2> arr({1,2});
    std::array<int, 2> a({1,2});

    ASSERT_TRUE(arr.size() == 2);
    ASSERT_TRUE(arr.max_size() == a.max_size());
}

TEST(Array_Swap, Default){
    s21::array<int, 3> __a({1,2,3});
    s21::array<int, 3> __b({4,5,6});

    std::array<int, 3> a({1,2,3});
    std::array<int, 3> b({4,5,6});

    ASSERT_TRUE(__cmp(__a,a));
    ASSERT_TRUE(__cmp(__b, b));

    __a.swap(__b);
    a.swap(b);

    ASSERT_TRUE(__cmp(__a,a));
    ASSERT_TRUE(__cmp(__b, b));
}