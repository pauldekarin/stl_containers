#include "../tests.hpp"

TEST(Set_Find, Common){
    s21::set<int> __s({1,2,3,4,5});

    ASSERT_TRUE(__s.contains(1));
    ASSERT_FALSE(__s.contains(0));

    s21::set<int>::iterator __res = __s.find(4);
    ASSERT_EQ(*__res, 4);

    __res = __s.find(100);
    ASSERT_TRUE(__res == __s.end());

    ASSERT_EQ(__s.count(2), 1);
    ASSERT_EQ(__s.count(105), 0);
}

TEST(Set_LowerBound, Common){
    std::function<bool(std::size_t)> __lb_test = [](std::size_t __test_id){
        std::set<int> s;
        s21::set<int> __s;

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

TEST(Set_UpperBound, Common){
    std::function<bool(std::size_t)> __ub_test = [](std::size_t __test_id){
        std::set<int> s;
        s21::set<int> __s;

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

TEST(Set_MaxSize, Common){
    s21::set<float> __s;
    std::set<float> s;
    ASSERT_EQ(s.max_size(), __s.max_size());
}

TEST(Set_Size, Common){
    std::function<bool(std::size_t)> __sz_test = [](std::size_t __test_id){
        s21::set<int> __s;
        std::set<int> s;

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

TEST(Set_Swap, Common){
    std::function<bool(std::size_t)> __swap_test = [](std::size_t __test_id){
        std::set<int> s;
        s21::set<int> __s;

        __fill(__s, s);

        s21::set<int> __r;
        std::set<int> r;

        __fill(__r, r);

        s.swap(r);
        __s.swap(__r);

        if(!__cmp(__s,s) && !__cmp(__r,r)){
            std::cout << "\033[33m" << "__test_id = " << __test_id  <<"\033[0m\n" << "s21: " << __s << "std: " << s << std::endl;
            return false;
        }

        return true;
    };

    ASSERT_TRUE(__loop_test(__swap_test));
}

TEST(Set_Merge, Common){
    std::function<bool(std::size_t)> __merge_test = [](std::size_t __test_id){
        std::set<int> s;
        s21::set<int> __s;

        __fill(__s, s);

        s21::set<int> __r;
        std::set<int> r;

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

TEST(Set_Insert, Common){
    std::function<bool(std::size_t)> __insert_test = [](std::size_t __test_id){
        std::set<int> s;
        s21::set<int> __s;
        __fill(s, __s);

        if(!__cmp(__s, s)){
            std::cout << "\033[33m" << "__test_id = " << __test_id  <<"\033[0m\n" << "s21: " << __s << "std: " << s << std::endl;
            return false;
        }

        return true;
    };

    ASSERT_TRUE(__loop_test(__insert_test));
}

TEST(Set_Clear, Common){
    std::set<int> s;
    s21::set<int> __s;

    __fill(__s, s);

    __s.clear();
    s.clear();

    ASSERT_TRUE(__cmp(__s,s));
}

TEST(Set_Move, Common){
    std::set<int> s;
    std::set<int> r;

    s21::set<int> __s;
    s21::set<int> __r;

    __fill(__s, s);
    __fill(__r, r);

    s = std::move(r);
    __s = std::move(__r);

    ASSERT_TRUE(__cmp(__s,s) && __cmp(__r,r));
}

TEST(Set_Iterators, Common){
    std::function<bool(std::size_t)> __fn = [](std::size_t __test_id){
        s21::set<int> __s;
        std::set<int> s;

        __fill(__s,s);
        
        return std::equal(__s.rbegin(), __s.rend(), s.rbegin());
    };

    ASSERT_TRUE(__loop_test(__fn));
}

TEST(Set_Erase, Iterator){
    std::function<bool(std::size_t)> __erase_by_iterator = [](std::size_t __test_id){
        std::set<int> s;
        s21::set<int> __s;

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


TEST(Set_Erase, Reference){
    std::function<bool(std::size_t)> __erase_by_iterator = [](std::size_t __test_id){
        std::set<int> s;
        s21::set<int> __s;

        __fill(__s, s);

        if(__s.size() >= 2){
            int __ref = std::rand() % 100;
            s.erase(__ref);
            __s.erase(__ref);

            s.erase(*std::prev(s.end()));
            __s.erase(*std::prev(__s.end()));
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

TEST(Set_Erase, Iterators){
    std::function<bool(std::size_t)> __erase_by_iterators = [](std::size_t __test_id){
        std::set<int> s;
        s21::set<int> __s;

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