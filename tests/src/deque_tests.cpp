#include "../s21_containers_tests.hpp"

TEST_F(DequeTester, PushFront){
    std::deque<int> d;
    
    __d.push_front(1);
    __d.push_front(1);
    __d.push_front(1);
    __d.push_front(1);
    __d.push_front(1);
    __d.push_front(1);
    __d.push_front(1);
    auto it = __d.begin();
    for(auto it = __d.begin(); it != __d.end(); it++){
        std::cout << *it << std::endl;
    }
    // std::cout << *it << std::endl;
}