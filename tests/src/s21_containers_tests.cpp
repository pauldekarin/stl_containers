#include "../s21_containers_tests.hpp"

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    s21::set<int> v;
    v.insert(10);
    auto it = v.find(10);
    std::cout << *it << std::endl;
    return RUN_ALL_TESTS();
}