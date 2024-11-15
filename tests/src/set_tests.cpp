// #include "../s21_containers_tests.hpp"

// /**
//  * size_type s21::set<Key,Compare,Allocator>::size
//  */
// TEST_F(SetTester, Size_Empty){
//     s21::set<int> s;
//     ASSERT_EQ(s.size(), 0);
// }

// TEST_F(SetTester, Size_NotIncreasingSameValuesInserting){
//     s21::set<int> s;
//     s.insert(1);
//     s.insert(1);
//     s.insert(2);
//     s.insert(2);
//     ASSERT_EQ(s.size(), 2);
// }

// /**
//  * s21::set<Key, Compare, Allocaotr>::erase
//  */

// TEST_F(SetTester, Erase){
//     s21::set<int> s;
//     s.insert(1);
//     s.erase(s.begin());
//     ASSERT_EQ(s.size(), 0);
// }

// /**
//  * iterator s21::set<Key, Compare, Allocator>::lower_bound
//  */
// TEST_F(SetTester, LowerBound_LessComparator){
//     s21::set<int> s({40,10,-2,-4,-1,0});
//     ASSERT_EQ(*s.lower_bound(2), 10);
// }

// TEST_F(SetTester, LowerBound_GreaterComparator){
//     s21::set<int, std::greater<int>> s({1,41,512,-4,421,0});
//     ASSERT_EQ(*s.lower_bound(-1), -4);
// }

// TEST_F(SetTester, LowerBound_Empty){
//     s21::set<int> s;
//     s.insert(10);
//     ASSERT_EQ(s.lower_bound(20).get(), nullptr);
// }

// /**
//  * iterator s21::set<Key, Compare, Allocator>::upper_bound
//  */

// TEST_F(SetTester, UpperBound_Common){
//     s21::set<int> s({1,2,4,5});
//     ASSERT_EQ(*s.upper_bound(3), 4);
// }

// /**
//  * reverse_iterator
//  */
// TEST_F(SetTester, Rbegin_value){
//     s21::set<int> s;
//     s.insert(40);
//     s.insert(8);
//     ASSERT_EQ(*s.rbegin(), 40);
// }

// TEST_F(SetTester, Rbegin_increment){
// }

// /**
//  * size_type s21::set<Key, Compare, Allocator>::count
//  */
// TEST_F(SetTester, Count_Common){
//     s21::set<int> s({1,1,1});
//     ASSERT_EQ(s.count(1), 1);
// }   