//
// Created by Anti on 2022/11/30.
//
#include "antidb/executor.h"
#include "gtest/gtest.h"
#include "antidb/statement.h"
#include "antidb/parser.h"
#include "vector"
#include "iostream"
#include "string"
namespace antidb{
    TEST(EXCUTION,CREATE_DATABASE)
    {
        Statement statement_("Create database anti_database");
        auto ptr=Parser::parse_sql(statement_);
        auto create = (Create_Statement*)ptr;
        EXPECT_EQ(CreateExecutor::CreateDataBase(create->name_), true);
    }
}

