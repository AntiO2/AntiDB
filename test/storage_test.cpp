//
// Created by Anti on 2022/12/1.
//
#include "iostream"
#include <cstdio>
#include "gtest/gtest.h"
#include "antidb/tuple.h"
#include "antidb/value.h"
#include "antidb/config.h"
#include "string"

namespace antidb {
    using std::cout;
    using std::endl;
    TEST(STORAGE_TEST, VALUE) {
        Value v1 = Value(INT, 1);
        char data[MAX_STRING_SIZE];
        v1.GetValue(data);
        EXPECT_EQ(v1.GetSize(), 4);
        EXPECT_EQ(data[0], 1);
        char str[] = "AntiO2";
        Value v2 = Value(STRING, str, sizeof(str));
        EXPECT_EQ(v2.GetSize(), MAX_STRING_SIZE);
        v2.GetValue(data);
        std::string str_ = data;
        EXPECT_EQ(str_, "AntiO2");

    }
}