#include "../s21_containers_tests.hpp"

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    std::set<int> v;
    v.insert(10);
    v.insert(8);
    std::cout << *v.rbegin() << std::endl;
    return RUN_ALL_TESTS();
}