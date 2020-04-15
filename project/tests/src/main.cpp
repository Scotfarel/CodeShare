//
// Created by ivan on 4/15/20.
//
#include "gmock/gmock.h"
#include "gtest/gtest.h"
using namespace std;

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

