#include "../tests.hpp"

TEST(Map_Constructor, Default){
    s21::map<int, int> __m{};
    std::map<int, int> m{};

    ASSERT_TRUE(__cmp(__m,m));
}

TEST(Map_CopyConstructor, Default){
    s21::map<int, int> __m({{1,2 }, {3,4}});
    s21::map<int, int> __c(__m);

    ASSERT_TRUE(__cmp(__m, __c));
}

TEST(Map_CopyMoveConstructor, Default){
    s21::map<int, int> __m({{1,2}, {3,4}});
    s21::map<int, int> __c(std::move(__m));
    std::map<int, int> m({{1,2},{3,4}});

    ASSERT_TRUE(__m.empty());
    ASSERT_TRUE(__cmp(__c, m));
}

TEST(Map_MaxSize, Default){
    s21::map<int, int> __m({{1,2}, {3,4}});
    std::map<int, int> m({{1,2},{3,4}});

    ASSERT_EQ(__m.max_size(), m.max_size());
}

TEST(Map_Clear, Default){
    s21::map<int, int> __m({{1,2}, {3,4}});
    std::map<int, int> m({{1,2},{3,4}});

    ASSERT_TRUE(__cmp(__m, m));

    __m.clear();
    m.clear();

    ASSERT_TRUE(__cmp(__m, m));
}

TEST(Map_InsertOrAssign, Default){
    s21::map<int, int> __m{};
    std::map<int, int> m{};

    ASSERT_TRUE(__cmp(__m, m));

    __m.insert_or_assign(1, 2);
    m.insert_or_assign(1,2);

    ASSERT_TRUE(__cmp(__m, m));

    __m.insert_or_assign(1, 3);
    m.insert_or_assign(1,3);

    ASSERT_TRUE(__cmp(__m, m));
}


TEST(Map_Erase, Default){
    s21::map<int, int> __m({{1,2},{3,4},{5,6}});
    std::map<int,int> m({{1,2},{3,4},{5,6}});   


    ASSERT_TRUE(__cmp(__m, m));

    __m.erase(std::next(__m.begin()));
    m.erase(std::next(m.begin()));

    ASSERT_TRUE(__cmp(__m, m));

    __m.erase(__m.begin());
    m.erase(m.begin());

    ASSERT_TRUE(__cmp(__m, m));

    __m.erase(__m.begin());
    m.erase(m.begin());

    ASSERT_TRUE(__cmp(__m, m));
}

TEST(Map_Swap, Default){
    s21::map<int, int> __m({{1,2},{3,4}});
    s21::map<int, int> __n({{5,6},{7,8}});

    s21::map<int, int> m({{1,2},{3,4}});
    s21::map<int, int> n({{5,6},{7,8}});

    ASSERT_TRUE(__cmp(__m,m));
    ASSERT_TRUE(__cmp(__n,n));

    __m.swap(__n);
    m.swap(n);

    ASSERT_TRUE(__cmp(__m,m));
    ASSERT_TRUE(__cmp(__n,n));
}


TEST(Map_Merge, Default){
    s21::map<int, int> __m({{1,2},{3,4}});
    s21::map<int, int> __n({{1,2},{7,8}});

    s21::map<int, int> m({{1,2},{3,4}});
    s21::map<int, int> n({{1,2},{7,8}});

    ASSERT_TRUE(__cmp(__m,m));
    ASSERT_TRUE(__cmp(__n,n));

    __m.merge(__n);
    m.merge(n);

    ASSERT_TRUE(__cmp(__m,m));
    ASSERT_TRUE(__cmp(__n,n));
}

TEST(Map_AssignMoveOperator, Default){
    s21::map<int, int> __m({{1,2}, {3,4}});
    s21::map<int, int> __c;
    __c = std::move(__m);
    std::map<int, int> m({{1,2},{3,4}});

    ASSERT_TRUE(__m.empty());
    ASSERT_TRUE(__cmp(__c, m));
}

TEST(Map_Find, Default){
    s21::map<int,int> __m({
        {1,2}
    });

    auto it = __m.contains(1);

    (void)it;
}
TEST(Map_InsertMany, Common){
    s21::map<int,int> __m;
    __m.insert_many(std::make_pair(1,2));
    std::cout << __m;
}