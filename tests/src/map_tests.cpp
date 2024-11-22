#include "../s21_containers_tests.hpp"



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