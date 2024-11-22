#include "../s21_containers_tests.hpp"


template <typename _T, class _Allocator = std::allocator<_T>, class _Compare = std::less<_T>,
          template <typename, typename, typename> class  _LContainer,
          template <typename, typename, typename> class _RContainer>
bool __cmp(
    _LContainer<_T, _Compare, _Allocator> &__lhs,
    _RContainer<_T, _Compare, _Allocator> &__rhs
)
{
    typename _LContainer<_T, _Compare, _Allocator>::iterator it = __lhs.begin();
    typename _RContainer<_T, _Compare, _Allocator>::iterator jt = __rhs.begin();

    while(it != __lhs.end() && jt != __rhs.end()){
        if(*it != *jt){
            return false;
        }
        it++; jt++;
    }

    return it == __lhs.end() && jt == __rhs.end();
}

template <typename _LContainer, typename _RContainer>
bool __cmp(
    _LContainer &__lhs,
    _RContainer &__rhs
){
    static_assert(
        std::is_same<typename _LContainer::value_type, typename _RContainer::value_type>::value, "Containers must have same types"
    );

    typename _LContainer::iterator it = __lhs.begin();
    typename _RContainer::iterator jt = __rhs.begin();

    while(it != __lhs.end() && jt != __rhs.end()){
        if(*it != *jt){
            return false;
        }
        it++; jt++;
    }

    return it == __lhs.end() && jt == __rhs.end();
}


template <typename _T, class _Allocator = std::allocator<_T>, class _Compare = std::less<_T>,
          template <typename, typename, typename> class  _LContainer,
          template <typename, typename, typename> class _RContainer>
void __fill(
    _LContainer<_T, _Compare, _Allocator> &__lhs,
    _RContainer<_T, _Compare, _Allocator> &__rhs
){
    static bool _ = false;
    if(!_){
        std::srand(std::time(nullptr));
        _=!_;
    }

    std::size_t __fill_size = 2;
    for(std::size_t i = 0; i < __fill_size; i++){
        _T __x = std::rand() % 100000;

        while(__lhs.find(__x) != __lhs.end()){
            __x = std::rand() % 100000;
        }

        __lhs.insert(__x);
        __rhs.insert(__x);
    }
}


template <typename _T, class _Allocator = std::allocator<_T>, class _Compare = std::less<_T>,
          template <typename, typename, typename> class  _LContainer,
          template <typename, typename, typename> class _RContainer>
void __cut(
    _LContainer<_T, _Compare, _Allocator> &__lhs,
    _RContainer<_T, _Compare, _Allocator> &__rhs
){
    int __size = std::rand() % __rhs.size();

    for(int __i = 0; __i < __size; __i++){
        int __pos = std::rand() % (static_cast<int>(__rhs.size()) - 1);
        std::cout << "__pos = " << __pos << std::endl;
        __lhs.erase(std::next(__lhs.begin(), __pos));
        __rhs.erase(std::next(__rhs.begin(), __pos));
    }
}




TEST(Tree, Constructor){

}

TEST(Tree, ReplaceNodes){
   
    std::size_t __tests = 100;

    for(std::size_t __test_id = 1; __test_id <= __tests; __test_id++){
        s21::__tree<int> __t;
        std::set<int> s;

        __fill(__t, s);

        std::vector<int> v(__t.begin(), __t.end());
        
        std::size_t __l_pos = std::rand() % v.size();
        std::size_t __r_pos = std::rand() % v.size();
        while(__r_pos == __l_pos) __r_pos = std::rand() % v.size();
        s21::__tree<int> __t_copy(__t); 
        __t.replace(std::next(__t.begin(), __l_pos), std::next(__t.begin(), __r_pos));
        std::swap(v[__l_pos], v[__r_pos]);

        // std::cout << "#############\n";
        if(!__cmp(__t, v)){
            std::cerr << "aren't equal\n";
            std::cout << "| TREE BEFORE |\n";
            __t_copy.display();
            std::cout << __t_copy << std::endl;
            std::cout << "\n| TREE AFTER |\n";
            __t.display();
            std::cout << __t << std::endl;

            std::cout << "\n\n| VECTOR |\n" << v << "\n| L_POS = " << __l_pos << " R_POS = " << __r_pos << " |\n";
            ASSERT_TRUE(false); 
        }else{
            // std::cout << "\n| TREE BEFORE |\n" << __t_copy << "\n\n| TREE AFTER |\n" << __t << "\n\n| VECTOR |\n" << v << "\n| L_POS = " << __l_pos << " R_POS = " << __r_pos <<  " ROOT = " << __t_copy.root() << "|\n\n";

        }
    }
}

TEST(Tree, Erase){
    std::size_t __max_tests = 1;

    for(std::size_t __test_id = 1;  __test_id <= __max_tests; __test_id++){
        std::cout << "TEST_ID = " << __test_id << std::endl;
        s21::__tree<int> __t;
        std::set<int> s;    


        __fill(__t, s);
        
        try{
            s21::__tree<int> __tc(__t);
            std::set<int> sc(s);
            __cut(__t, s);

            if(!__cmp(__t, s)){
                std::cout << "[BEFORE]\n";
                __tc.display();
                std::cout << __tc << std::endl;

                std::cout << "[AFTER]\n";
                __t.display();
                std::cout << __t << std::endl;
                
                std::cerr << "\n|VECTOR|\n" << s << "\n#######\n";
                ASSERT_TRUE(false);
            }
        }catch(std::exception &e){
            std::cerr << "[TEST# " << __test_id << "] Segmentation fault\n\n######\n" << __t << "\n#######\n";
            ASSERT_TRUE(false);
        }
        
    }
}