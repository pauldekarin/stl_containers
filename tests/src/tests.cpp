#include "../tests.hpp"


bool __loop_test(std::function<bool(std::size_t)> &__fn, std::size_t __tests_count){
    for(
        std::size_t __test_id = 1;
        __test_id <= __tests_count;
        __test_id++
    ){
        bool __res = __fn(__test_id);
        
        if(!__res){
            return false;
        }
    }

    return true;
}

int main(int argc, char **argv){
    std::srand(std::time(nullptr));
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}