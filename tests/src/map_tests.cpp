#include "../s21_containers_tests.hpp"

TEST_F(MapTester, Insert){
    std::pair<const int,int> p(1,2);
    std::map<int,int> m;
    auto it = m.end();
    std::cout << it->first << std::endl;
    __m.insert(p);
    __m.insert({4,1});
}