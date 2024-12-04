#include "../tests.hpp"



TEST(Map_Constructor, Default){
    s21::map<int, int> __m{};
    std::map<int, int> m{};

    ASSERT_TRUE(__cmp(__m,m));
}

TEST(Map_Find, Default){
    s21::map<int,int> __m({
        {1,2}
    });

    auto it = __m.contains(1);
}
TEST(Map_InsertMany, Common){
    s21::map<int,int> __m;
    __m.insert_many(std::make_pair(1,2));
    std::cout << __m;
}