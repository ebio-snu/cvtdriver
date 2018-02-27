/*
 Copyright © 2018 ebio lab. SNU. All Rights Reserved.

 @file test_level_0.cpp
 @date 2018-02-27, JoonYong
 @author Kim, JoonYong <tombraid@snu.ac.kr>

 This file is for unit tests of a driver.
 refer from: https://github.com/ebio-snu/cvtdriver
*/

#include "cvtdriver.h"
#include <gtest/gtest.h>

namespace {

class CvtDriverTest : public ::testing::Test {
protected:
    CvtDriverTest() {
    }

    virtual ~CvtDriverTest() {
    }

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

};

TEST_F(CvtDriverTest, LOAD) {
    EXPECT_EQ(0, 0);
}

TEST_F(CvtDriverTest, DoesXyz) {
}

}  // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

