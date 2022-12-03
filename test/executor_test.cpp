//
// Created by Anti on 2022/11/30.
//
#include "antidb/executor.h"
#include "gtest/gtest.h"
#include "antidb/statement.h"
#include "antidb/parser.h"
#include "antidb/exception.h"
#include "vector"
#include "iostream"
#include "string"

namespace antidb {
    TEST(EXCUTION, DISABLED_CREATE_DATABASE) {
        Statement statement_("Create database anti_database");
        auto ptr = Parser::parse_sql(statement_);
        auto create = (Create_Statement *) ptr;
        EXPECT_EQ(CreateExecutor::CreateDataBase(create->name_), true);
    }

    TEST(EXCUTION, SWITCH_DATABASE) {
        /**
         * 这里测试是会有副作用的，记得删除新建的文件夹
         */
        std::string db_name;
        EXPECT_THROW(UseExecutor::UseDataBase("anti_db", db_name), error_command);
        EXPECT_EQ(CreateExecutor::CreateDataBase("anti_db"), true);
        EXPECT_EQ(CreateExecutor::CreateDataBase("anti_db"), false);
        UseExecutor::UseDataBase("anti_db", db_name);
        EXPECT_EQ(db_name, "anti_db");
    }

}

