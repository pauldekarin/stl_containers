#include "../tests.hpp"

TEST(Array_Constructor, Default){
    s21::array<int, 4> a;
}

TEST(Array_Constructor, CopyMove){
}

TEST(Array_Iterator, Default){
    s21::array<int, 5> a;
    a.begin();
}

TEST(Array_Front, EmptyArray){
    s21::array<int, 0> a;
}

TEST(Array_MoveAssignment, Default){
    s21::array<int, 5> a1({1,2,3,4,5});
    s21::array<int, 5> a2(std::move(a1));

    for(auto t : a1){
        std::cout << t << std::endl;
    }
}