#include "../tests.hpp"

TEST(Multiset_Count, Common){
    std::function<bool(std::size_t)> __count_test = []([[maybe_unused]] std::size_t __test_id){
        std::multiset<int> s;
        s21::multiset<int> __s;

        __fill(__s, s, 5000, 3);
        int __x = std::rand() % 4;
        return s.count(__x) == __s.count(__x);
    };

    ASSERT_TRUE(__loop_test(__count_test));
}

TEST(Multiset_InsertMany, Common){
    s21::multiset<int> __s;
    __s.insert_many(1,1,1,1);
}

TEST(Multiset_LowerBound, Common){
    std::function<bool(std::size_t)> __lb_test = []([[maybe_unused]] std::size_t __test_id){
        std::multiset<int> s;
        s21::multiset<int> __s;

        __fill(__s, s);
        int __x = __s.empty() ? std::rand() : *std::next(__s.begin(), std::rand() % __s.size() )  + (std::rand() % 3 - 2);

        auto __it = __s.lower_bound(__x);
        auto it = s.lower_bound(__x);

        if(__it == __s.end()){
            return it == s.end();
        }else if(it == s.end()){
            return __it == __s.end();
        }else{
            return *__it == *it;
        }
    };

    ASSERT_TRUE(__loop_test(__lb_test));
}

TEST(Multiset_UpperBound, Common){
    std::function<bool(std::size_t)> __ub_test = []([[maybe_unused]] std::size_t __test_id){
        std::multiset<int> s;
        s21::multiset<int> __s;

        __fill(__s, s);
        int __x = __s.empty() ? std::rand() : *std::next(__s.begin(), std::rand() % __s.size() )  + (std::rand() % 3 - 2);

        auto __it = __s.upper_bound(__x);
        auto it = s.upper_bound(__x);

        if(__it == __s.end()){
            return it == s.end();
        }else if(it == s.end()){
            return __it == __s.end();
        }else{
            return *__it == *it;
        }
    };

    ASSERT_TRUE(__loop_test(__ub_test));
}

TEST(Multiset_MaxSize, Common){
    s21::multiset<float> __s;
    std::multiset<float> s;
    ASSERT_EQ(s.max_size(), __s.max_size());
}

TEST(Multiset_Size, Common){
    std::function<bool(std::size_t)> __sz_test = []([[maybe_unused]] std::size_t __test_id){
        s21::multiset<int> __s;
        std::multiset<int> s;

        __fill(__s, s);

        if(__s.size() &&  std::rand() % 2 == 0){
            std::size_t __l_pos = std::rand() % __s.size();
            std::size_t __r_pos = std::rand() % ( __s.size() - __l_pos ) + __l_pos;
            s.erase(std::next(s.begin(), __l_pos), std::next(s.begin(), __r_pos));
            __s.erase(std::next(__s.begin(), __l_pos), std::next(__s.begin(), __r_pos));
        }

        return __s.size() == s.size();
    };

    ASSERT_TRUE(__loop_test(__sz_test));
}

TEST(Multiset_Swap, Common){
    std::function<bool(std::size_t)> __swap_test = []([[maybe_unused]] std::size_t __test_id){
        std::multiset<int> s;
        s21::multiset<int> __s;

        __fill(__s, s);

        s21::multiset<int> __r;
        std::multiset<int> r;

        __fill(__r, r);

        s.swap(r);
        __s.swap(__r);

        if(!__cmp(__s,s) && !__cmp(__r,r)){
            __display_difference(__s, s);
            return false;
        }

        return true;
    };

    ASSERT_TRUE(__loop_test(__swap_test));
}

TEST(Multiset_Merge, Common){
    std::function<bool(std::size_t)> __merge_test = [](std::size_t __test_id){
        std::multiset<int> s;
        s21::multiset<int> __s;

        __fill(__s, s);

        s21::multiset<int> __r;
        std::multiset<int> r;

        __fill(__r, r);

        s.merge(r);
        __s.merge(__r);

        if(!__cmp(__s,s) && !__cmp(__r,r)){
            std::cout << "\033[33m" << "__test_id = " << __test_id << "\n";
            __display_difference(__s, s);
            __display_difference(__r, r);
            return false;
        }

        return true;
    };

    ASSERT_TRUE(__loop_test(__merge_test));
}

TEST(Multiset_Insert, Common){
    std::function<bool(std::size_t)> __insert_test = [](std::size_t __test_id){
        std::multiset<int> s;
        s21::multiset<int> __s;
        __fill(s, __s);

        if(!__cmp(__s, s)){
            std::cout << "\033[33m" << "__test_id = " << __test_id  <<"\033[0m\n" << "s21: " << __s << "std: " << s << std::endl;
            return false;
        }

        return true;
    };

    ASSERT_TRUE(__loop_test(__insert_test));
}

TEST(Multiset_Clear, Common){
    std::multiset<int> s;
    s21::multiset<int> __s;

    __fill(__s, s);

    __s.clear();
    s.clear();

    ASSERT_TRUE(__cmp(__s,s));
}

TEST(Multiset_Move, Common){
    std::multiset<int> s;
    std::multiset<int> r;

    s21::multiset<int> __s;
    s21::multiset<int> __r;

    __fill(__s, s);
    __fill(__r, r);

    s = std::move(r);
    __s = std::move(__r);

    ASSERT_TRUE(__cmp(__s,s) && __cmp(__r,r));
}

TEST(Multiset_Iterators, Common){
    std::function<bool(std::size_t)> __fn = []([[maybe_unused]] std::size_t __test_id){
        s21::multiset<int> __s;
        std::multiset<int> s;

        __fill(__s,s);
        
        return std::equal(__s.rbegin(), __s.rend(), s.rbegin());
    };

    ASSERT_TRUE(__loop_test(__fn));

    s21::multiset<int> s({1,2,3});

    ASSERT_TRUE(*s.begin() == 1);
    ASSERT_TRUE(*std::prev(s.end()) == 3);
}

TEST(Multiset_FindContains, Default){
    s21::multiset<int> s({1,2,3});
    
    ASSERT_TRUE(std::next(s.begin()) == s.find(2));
    ASSERT_TRUE(s.end() == s.find(4));
    ASSERT_TRUE(*s.find(1) == 1);

    ASSERT_TRUE(s.contains(3));
    ASSERT_FALSE(s.contains(10));
}

TEST(Multiset_Iterators, Default){
    s21::multiset<int> s({1,2,3});

    s21::multiset<int>::const_iterator it = s.begin();
    s21::multiset<int>::const_iterator jt = std::prev(s.end());

    ASSERT_TRUE(*it == 1);
    ASSERT_TRUE(*jt == 3);
}

TEST(Multiset_Erase, Iterator){
    std::function<bool(std::size_t)> __erase_by_iterator = [](std::size_t __test_id){
        std::multiset<int> s;
        s21::multiset<int> __s;

        __fill(__s, s);

        if(__s.size() != 0){
            std::size_t __pos = std::rand() % __s.size();
            s.erase(std::next(s.begin(), __pos));
            __s.erase(std::next(__s.begin(), __pos));
        }

        if(!__cmp(__s, s)){
            std::cout << "\033[33m" << "__test_id = " << __test_id << "\n";
            __display_difference(__s, s);
            return false;
        }

        return true;
    };


    ASSERT_TRUE(__loop_test(__erase_by_iterator));
}


TEST(Multiset_Erase, Reference){
    std::function<bool(std::size_t)> __erase_by_iterator = [](std::size_t __test_id){
        std::multiset<int> s;
        s21::multiset<int> __s;

        __fill(__s, s);

        if(__s.size()){
            int __ref = *std::next(__s.begin(), std::rand() % __s.size());
            s.erase(__ref);
            __s.erase(__ref);
        }   

        if(!__cmp(__s, s)){
            std::cout << "\033[33m" << "__test_id = " << __test_id << "\n";
            __display_difference(__s, s);
            return false;
        }

        return true;
    };


    ASSERT_TRUE(__loop_test(__erase_by_iterator));
}

TEST(Multiset_Erase, Iterators){
    std::function<bool(std::size_t)> __erase_by_iterators = [](std::size_t __test_id){
        std::multiset<int> s;
        s21::multiset<int> __s;

        __fill(__s, s);

        if(__s.size() != 0){
            std::size_t __l_pos = std::rand() % __s.size();
            std::size_t __r_pos = std::rand() % ( __s.size() - __l_pos ) + __l_pos;
            s.erase(std::next(s.begin(), __l_pos), std::next(s.begin(), __r_pos));
            __s.erase(std::next(__s.begin(), __l_pos), std::next(__s.begin(), __r_pos));
        }

        if(!__cmp(__s, s)){
            std::cout << "\033[33m" << "__test_id = " << __test_id << "\n";
            __display_difference(__s, s);
            return false;
        }

        return true;
    };


    ASSERT_TRUE(__loop_test(__erase_by_iterators));
}

TEST(Multiset_Constructor, Default){
    s21::multiset<int> s1({1,2,3});
    s21::multiset<int> s2(s1);
    std::multiset<int> s({1,2,3});

    ASSERT_TRUE(__cmp(s2,s));
    ASSERT_TRUE(__cmp(s1,s));

    s21::multiset<int> s3(std::move(s1));

    ASSERT_TRUE(s1.empty());
    ASSERT_TRUE(__cmp(s3,s));

    s3 = std::move(s2);

    ASSERT_TRUE(s2.empty());
    ASSERT_TRUE(__cmp(s3,s));
}

