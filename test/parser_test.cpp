//
// Created by Anti on 2022/11/26.
//
#include "antidb/parser.h"
#include "gtest/gtest.h"
#include "antidb/statement.h"
#include "vector"
#include "iostream"

namespace antidb {
    /**
 * get_token测试
 */
    TEST(PARSER_TEST, DISABLED_PARSE) {
        using std::cout;
        using std::endl;
        std::vector<std::string> tokens;
        antidb::Parser parse_instance;
        std::string sql("insert what");
        antidb::SQL_type sqlType;
        EXPECT_EQ(parse_instance.parse_sql(sql, sqlType), true);
        EXPECT_EQ(sqlType, antidb::INSERT);

        sql = "  delete";
        EXPECT_EQ(parse_instance.parse_sql(sql, sqlType), true);
        EXPECT_EQ(sqlType, antidb::DELETE);
        sql = "  create   ";
        EXPECT_EQ(parse_instance.parse_sql(sql, sqlType), true);
        EXPECT_EQ(sqlType, antidb::CREATE);


        sql = "  select   ";
        EXPECT_EQ(parse_instance.parse_sql(sql, sqlType), true);
        EXPECT_EQ(sqlType, antidb::SELECT);

        sql = "  antio2   ";
        EXPECT_EQ(parse_instance.parse_sql(sql, sqlType), false);
    }

    TEST(PARSER_TEST, DISABLED_NO_SEM) {
        std::vector<std::string> tokens;
        antidb::Parser parse_instance;
        std::string sql(" insert;  ");
        antidb::SQL_type sqlType;
        EXPECT_EQ(parse_instance.parse_sql(sql, sqlType), true);
        EXPECT_EQ(sqlType, antidb::INSERT);
    }

    TEST(PARSER_TEST, DISABLED_TOKEN_v2) {
        std::vector<std::string> tokens;
        antidb::Parser parse_instance;
        std::string sql(" create table new_table(column int primary,email string ,anti int); ");
        antidb::SQL_type sqlType;
        antidb::Parser::get_token(sql, tokens);
//        for(const auto& token:tokens)
//        {
//            std::cout<<token<<std::endl;
//        }
    }

    TEST(PARSER_TEST, CREATE_TABLE) {
        std::string sql(" create table new_table (column int primary,email string ,anti int); ");
        auto stmt = Statement(sql);
        auto c_stmt = (Create_Statement *) antidb::Parser::parse_sql(stmt);
        EXPECT_EQ(1, 1);
    }

    TEST(PARSER_TEST, CREATE_TABLE_2) {
        std::string sql("create table anti_table(id int,age int,name string);");
        auto stmt = Statement(sql);
        auto c_stmt = (Create_Statement *) antidb::Parser::parse_sql(stmt);
        EXPECT_EQ(1, 1);
    }

    TEST(PARSER_TEST, DISABLED_DROP) {
        std::string sql("drop database antio2");
        auto stmt = Statement(sql);
        auto d_stmt = (Drop_Statement *) Parser::parse_sql(stmt);
        EXPECT_EQ(d_stmt->name_, "antio2");
        EXPECT_EQ(d_stmt->dropType_, DROP_DATABASE);
    }

    TEST(PARSER_TEST, DISABLED_DROP_TABLE) {
        std::string sql("drop table antio2");
        auto stmt = Statement(sql);
        auto d_stmt = (Drop_Statement *) Parser::parse_sql(stmt);
        EXPECT_EQ(d_stmt->name_, "antio2");
        EXPECT_EQ(d_stmt->dropType_, DROP_TABLE);
    }

    TEST(PARSER_TEST, DISABLED_INSERT_TABLE) {
        std::string sql("insert table antio2 values(1,\"antiO2\",814);");
        auto stmt = Statement(sql);
        auto i_stmt = (Insert_Statement *) antidb::Parser::parse_sql(stmt);
        EXPECT_EQ(i_stmt->value_str.size(), 3);
        EXPECT_EQ(i_stmt->table_name_, "antio2");
        for (const auto &value: i_stmt->value_str) {
            std::cout << value << std::endl;
        }

    }

    TEST(PARSER_TEST, DISABLED_SELECT) {

        {
            std::string sql("select * from anti_table where dwdwdwdwdwd;");
            auto stmt = Statement(sql);
            EXPECT_ANY_THROW((Select_Statement *) antidb::Parser::parse_sql(stmt));
        }
        {
            std::string sql("select * from anti_table;");
            auto stmt = Statement(sql);
            auto s_stmt = (Select_Statement *) antidb::Parser::parse_sql(stmt);
//            EXPECT_EQ(s_stmt->conditionType_,NO_CONDITION);
            EXPECT_EQ(s_stmt->table_name_, "anti_table");
            EXPECT_EQ(s_stmt->select_all_, true);
        }
        {
            std::string sql("select age from anti_table;");
            auto stmt = Statement(sql);
            auto s_stmt = (Select_Statement *) antidb::Parser::parse_sql(stmt);
//            EXPECT_EQ(s_stmt->conditionType_,NO_CONDITION);
            EXPECT_EQ(s_stmt->table_name_, "anti_table");
            EXPECT_EQ(s_stmt->select_all_, false);
            EXPECT_EQ(s_stmt->col_name_, "age");
        }
        {
            std::string sql("select age from anti_table where i > 3;");
            auto stmt = Statement(sql);
            auto s_stmt = (Select_Statement *) antidb::Parser::parse_sql(stmt);
//            EXPECT_EQ(s_stmt->conditionType_,GREATER);
            EXPECT_EQ(s_stmt->table_name_, "anti_table");
            EXPECT_EQ(s_stmt->select_all_, false);
            EXPECT_EQ(s_stmt->col_name_, "age");
//            EXPECT_EQ(s_stmt->compared_,"3");
//            EXPECT_EQ(s_stmt->condition_col_,"i");

        }
    }
}
