#include "../tests.hpp"



TEST(Tree, Constructor){

}

TEST(Tree, ReplaceNodes){
    
}

TEST(Tree, Erase){
    s21::__tree<int> __tr;
    __tr.insert(0);
    __tr.insert(4);
    __tr.insert(-10);

    __tr.erase(std::next(__tr.begin(), 2));
    __tr.erase(std::next(__tr.begin(), 1));
    __tr.erase(std::next(__tr.begin(), 0));
}

TEST(Tree, LowerBound){
  
}