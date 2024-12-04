#include "../tests.hpp"

TEST(Multimap_Constructor, Default){

}

TEST(Multimap_Insert, Default){
    std::multimap<int,int> m;
    m.insert({1,2});
    m.insert({1,3});
    m.insert({1,4});

    s21::multimap<int,int> __m;
    __m.insert(1,2);
    __m.insert(1,3);
    __m.insert(1,4);
    __m.insert(1,4);
    __m.insert(1,4);
    for(auto it : __m){
        std::cout << it.first << " " << it.second << std::endl;
    }
}