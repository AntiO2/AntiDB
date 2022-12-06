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

    TEST(EXCUTION, DISABLED_SWITCH_DATABASE) {
        /**
         * 这里测试是会有副作用的，记得删除新建的文件夹
         */
//        std::string db_name;
//        EXPECT_THROW(UseExecutor::UseDataBase("anti_db", db_name), error_command);
//        EXPECT_EQ(CreateExecutor::CreateDataBase("anti_db"), true);
//        EXPECT_EQ(CreateExecutor::CreateDataBase("anti_db"), false);
//        UseExecutor::UseDataBase("anti_db", db_name);
//        EXPECT_EQ(db_name, "anti_db");
    }

    TEST(CREATE_EXCUTION, DISABLED_CREATE_DATABASE_2) {
        EXPECT_EQ(CreateExecutor::CreateDataBase("AntiO2"), true);
        EXPECT_ANY_THROW(CreateExecutor::CreateDataBase("AntiO2"););
        auto db = UseExecutor::UseDataBase("AntiO2");
        EXPECT_EQ(db->getDbName(), "AntiO2");
    }

    TEST(CREATE_DROP, DISABLED_CD) {
        EXPECT_EQ(CreateExecutor::CreateDataBase("AntiO2"), true);
        auto db = UseExecutor::UseDataBase("AntiO2");
        std::string sql = "create table anti_table(id int,age int,name string);";
        auto stmt = Statement(sql);
        auto c_stmt = (Create_Statement *) Parser::parse_sql(stmt);
        CreateExecutor::CreateTable(*c_stmt, *db);
        DropExecutor::DropTable("anti_table", &db);
        db = nullptr;
        DropExecutor::DropDatabase("AntiO2");
    }

    TEST(INSERT, DISABLED_SELECT_AND_INSERT) {
        CreateExecutor::CreateDataBase("AntiO2");
        auto db = UseExecutor::UseDataBase("AntiO2");
        /**
         * 创建表
         */
        std::string sql = "create table antio2(id int,age int,name string);";
        auto stmt = Statement(sql);
        auto c_stmt = (Create_Statement *) Parser::parse_sql(stmt);
        CreateExecutor::CreateTable(*c_stmt, *db);

        std::string sql2("insert table antio2 values(1,2,\"AntiO2\");");
        auto stmt2 = Statement(sql2);
        auto i_stmt = (Insert_Statement *) antidb::Parser::parse_sql(stmt2);
        EXPECT_EQ(i_stmt->value_str.size(), 3);
        EXPECT_EQ(i_stmt->table_name_, "antio2");
        for (const auto &value: i_stmt->value_str) {
            std::cout << value << std::endl;
        }
        for (int i = 0; i <= 3; i++)
            InsertExecutor::InsertByStmt(i_stmt, &db);
        auto tuple = SelectExecutor::ReadTuple(db->getTable("antio2"), 0);
        std::vector<Value> vs;
        db.get()->getTable("antio2")->Parse_tuple(vs, tuple);
        for (auto v: vs) {
            std::cout << v.GetInt() << std::endl;
        }

    }

    TEST(INSERT, INSERT_PRIMARY) {
        CreateExecutor::CreateDataBase("AntiO2");
        auto db = UseExecutor::UseDataBase("AntiO2");
        /**
         * 创建表
         */
        std::string sql = "create table antio2(id int primary,age int,name string);";
        auto stmt = Statement(sql);
        auto c_stmt = (Create_Statement *) Parser::parse_sql(stmt);
        auto table = CreateExecutor::CreateTable(*c_stmt, *db);
        ASSERT_EQ(table->schema_.getKeyId(), 0);
        ASSERT_EQ(table->schema_.Has_Primary(), true);

        for (int i = 0; i < 3; i++) {
            std::string sql2 = "insert table antio2 values(";
            sql2 += std::to_string(i);
            sql2 += ",2,\"AntiO2\");";
            auto stmt2 = Statement(sql2);
            auto i_stmt = (Insert_Statement *) antidb::Parser::parse_sql(stmt2);
            EXPECT_EQ(i_stmt->value_str.size(), 3);
            EXPECT_EQ(i_stmt->table_name_, "antio2");
            InsertExecutor::InsertByStmt(i_stmt, &db);
        }
    }
}

