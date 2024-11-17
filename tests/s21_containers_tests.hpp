#pragma once

#include "../s21_containers.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>


class SetTester: public ::testing::Test{
public:
    void SetUp(){

    }

    void TearDown(){

    };
};

class ListTester: public ::testing::Test{
public:

    s21::list<int> __il;

    void SetUp(){

    }

    void TearDown(){

    };
};

class DequeTester: public ::testing::Test{
public:
    s21::deque<int> __d;

    void SetUp(){

    }
    
    void TearDown(){

    }
};



class MapTester: public ::testing::Test{
public:
    s21::map<int, int> __m;

    void SetUp(){

    }

    void TearDown(){

    }
};


class VectorTester: public ::testing::Test{
public:
    s21::vector<int> __v;

    void SetUp(){

    }

    void TearDown(){

    }
};