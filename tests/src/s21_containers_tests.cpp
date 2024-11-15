#include "../s21_containers_tests.hpp"
#include <array>

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    
    return RUN_ALL_TESTS();
}